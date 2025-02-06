# Wish me best luck

## Race Condition
當多個tasks 想要同時存取共享變數時，輸出結果會因執行順序而不同，導致錯誤。
舉例來說：taskA與B的內容是將counter加1

```
int counter=0;

void taskA(){
    counter++;
}

void taskB(){
    counter++;
}

int main(){
    taskA();
    taskB();
    printf("%d", counter);
}
```


我們預期的輸出結果會是2，但若A, B同時將counter load 進來的話則輸出會是1
這就是Race condition