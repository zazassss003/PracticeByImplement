#include <stdio.h>
#include <stdint.h>
#define STATUS_REG (*(volatile uint32_t*) 0x40001000)

// #define STATUS_RGE
// volatile             告訴編譯器不用優化該變數：因為他可能因為外部因素隨時改變，所以每次讀取時都要從記憶體（暫存器）位置讀取一次
// utint32_t*           
// *(uint32_t*)


int main(){
    STATUS_REG = 0x1;

    uint32_t value = STATUS_REG;

    printf("%d", value);


}