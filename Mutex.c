#include<stdlib.h>


int counter=0; // 共享變數

void taskA(){
    counter++; // 修改共享變數
}

void taskB(){
    counter++;
}

int main(){
    taskA();
    taskB();

    printf("%d", counter);
}
/*

理想的輸出應該要是2，但若taskA與B同時load counter則輸出結果會是1
=>這就是race condition : 當多個tasks同時存取共享資源，最終結果取決於執行順序，會產生非預期的結果或錯誤

解決方法：Mutex lock
使用互斥鎖來確定只有一個task能進入臨界區間
也就是說當一個task要存取共享變數時需要先檢查是否有其他task已經存取該變數，如果有則等待，如果無則存取並上鎖

*/

typedef struct{
    int counter;
    TaskHandle_t waiting;
} MutexLock_t;

void takeLock(MutexLock_t *lock){

    taskENTER_CRITICAL(); // 強制禁止強制禁止task切換，但會影響os排程，因為無法切換
    while(lock->counter == 0){ //鎖已被取走
        lock->waiting = xTaskGetCurrentTaskHandle();
        taskEXIT_Critical();
        taskSuspend(NULL); // 等待
        taskENTER_Critical(); 
    }

    lock->counter = 0; // 取走鎖
    taskEXIT_Critical();
}

void giveLock(MutexLock_t *lock){
    taskENTER_CRITICAL();
    lock->counter = 1; // 釋放鎖

    if(lock->waiting != NULL){
        TaskResume(lock->waiting); // 若有task在等待，則喚醒
        lock->waiting = NULL;
    }
    taskEXIT_Critical();

}