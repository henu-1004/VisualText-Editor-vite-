#include<curses.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int x = 0, y = 0;//좌표값
typedef struct DNode {
    int strsize;
    char* str;
    struct DNode* up;
    struct DNode* down;
} node;


node* head = NULL; // 맨 위의 노드를 가리키는 포인터
node* curNode = NULL; // 현재 위치한 노드를 가리키는 포인터
//node* tail = NULL;//꼬리노드 필요한가

int value(int ch) {
    if (ch >= 32 && ch <= 126) {
        return 1;//ch가 문자면 1반환 letter에 1저장
    }
    else return 0;//아니면 0반환 letter에 0저장
}

//화살표이동함수
void curMove(int ch) {
    switch (ch) {
    case KEY_UP:
        curNode = curNode->up;
        y--;
        move(y, x);
        break;
    case KEY_DOWN:
        curNode = curNode->down;
        y++;
        move(y, x);
        break;
    case KEY_LEFT:
        x--;
        move(y, x);
        break;
    case KEY_RIGHT:
        x++;
        move(y, x);
        break;
    }
    refresh();
}

node* getN() {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->strsize = 0;
    newnode->str = NULL;
    newnode->up = NULL;
    newnode->down = NULL;
    return newnode;
}

void inputStr(node** tmp, int ch) {
    (*tmp)->strsize++;
    (*tmp)->str = (char*)realloc((*tmp)->str, ((*tmp)->strsize + 1) * sizeof(char));
    if ((*tmp)->str == NULL) {
        printf("Memory allocation failed");
        return;  // Exit with an error code
    }
    (*tmp)->str[(*tmp)->strsize - 1] = ch;
    (*tmp)->str[(*tmp)->strsize] = '\0';  // Null-terminate the string
    mvprintw(y, 0, "%s", (*tmp)->str);
    refresh();
    return;
}

void insertWant(node**tmp) {
    // 빈 리스트인 경우
    if (head == NULL) {
        head = (*tmp);
        //curNode = (*tmp);
        //tail = tmp;
        return;
    }
    node* cur = head;
    // 리스트의 맨 앞에 삽입
    if (y == 0) {
        (*tmp)->down = head;
        head->up = (*tmp);
        head = (*tmp);
        //curNode = (*tmp);
    }
    else{
        // 리스트 중간에 삽입
        for (int i = 1; i < y - 1; i++) {
            cur = cur->down;
        }
        if (cur == NULL) {
            printw("삽입할 위치가 리스트의 크기를 벗어났습니다.\n");
            refresh();
            return;
        }
        (*tmp)->down = cur->down;
        (*tmp)->up = cur;
        if (cur->down != NULL) {
            cur->down->up = (*tmp);
        }
        cur->down = (*tmp);
        //    if (tmp->down == NULL) {
        //        tail = tmp;
          //  }//맨끝노드면 테일업데이트
        curNode = (*tmp);
    
    }
    //삽입하고 출력하는라인
    cur = head;
    for (int i = y; cur->down != NULL; cur = cur->down, i++) {
        mvprintw(i, 0, "%s", cur->str);
        refresh();
    }

    return;
}

void freeNode() {
    node*cur = head;
    if (head == NULL) {
        return; //빈리스트라면 프리돼있는거
    }
    while (head!= NULL) {
        head = cur->down;
        free(cur);
        cur = head;
    }
    return;
}


int main() {
    initscr();  // curses 초기화
    cbreak();   // 키 버퍼링을 사용하지 않고 즉시 입력을 받음
    noecho();   // 입력한 문자를 화면에 표시하지 않음
    raw();      // 특수 문자 처리 모드 비활성화
    keypad(stdscr, TRUE); // 특수 키(화살표 등) 활성화
    int ch;
    int letter;
    int stop = 0;
    int strSize = 0;
    //그럼 와일로 ch를 계속받아야하나? 처음부터?
    printw("waiting");
    refresh();
    ch = getch();
    int firstRun = 1;
    letter = value(ch);
    while (1) {
        if (firstRun) {
            if (letter == 1 || ch == 13) { //글자거나 엔터면 화면 클리어함., 탭도생각하자.
                system("cls");
            }
            firstRun = 0;//한번실행됐고, 두번은안함.
        }
        if (head==NULL&&letter == 1) {//빈리스트고, 글자입력이들어오면 겟뉴노드
            curNode=getN();
            insertWant((&curNode));
            inputStr((&curNode), ch);
        }
        else if (letter == 1) {
            inputStr((&curNode), ch);
        }
        else if(letter == 0){
            //f2누르면 종료.
            if (ch == KEY_F(2)) {
                break;
            }
            //화살표면 화살표실행
            if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT) {
                curMove(ch);
            }
            //엔터
            if (ch == 13) { //엔터가 13으로입력되네, 운영체제마다 엔터입력값 찾아보자
                y++;
                move(y, 0);
                curNode=getN();
            }
        }
        ch = getch();
        letter = value(ch);
    }

    

    freeNode();
    endwin();
    return 0;
}
