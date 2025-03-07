```
int count=0;

processA(){
    count++;
}
processB(){
    count++;
}
int main(){
    processA();
    processB();
}
```

### kernel space
kernel heap: store the PCB which contain all processs info
kernel stack: store the current state of process(i.e. CPU reg, return addr)

### user space

Heap  : malloc 
Stack : int, char
BSS   : static int a
Data  : global, static int a=1;
Text  : code

### step

1. processA read count value (0) in memory and load to CPU reg
2. contex switch ocurr, save all current CPU reg value to kernel stack and update pointer in PCB in kernel heap
3. processB read count value (0) in memory and load to CPU reg
