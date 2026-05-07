//운영체제알아오는예문
#include <stdio.h>

// 리눅스
#ifdef __linux__
#define OS "Linux"
// 여기에 리눅스 전용 코드 추가
#include <unistd.h>  // 예: sleep 함수 사용
#define SLEEP_FUNCTION sleep

// 윈도우
#elif defined(_WIN32) || defined(_WIN64)
#define OS "Windows"
// 여기에 윈도우 전용 코드 추가
#include <windows.h>  // 예: Sleep 함수 사용
#define SLEEP_FUNCTION Sleep

// 맥 OS
#elif __APPLE__
#define OS "Mac OS X"
// 여기에 맥 OS 전용 코드 추가
#include <unistd.h>  // 예: sleep 함수 사용
#define SLEEP_FUNCTION sleep

// 그 외의 운영체제
#else
#define OS "Other"
#define SLEEP_FUNCTION(...)  // 다른 운영체제에서는 더미 함수로 정의
#endif

int main() {
    SLEEP_FUNCTION(10);
    printf("Operating System: %s\n", OS);

    // 운영체제에 따른 특정한 동작
    // 예제: OS에 따라 다른 sleep 함수 사용
    

    return 0;
}
