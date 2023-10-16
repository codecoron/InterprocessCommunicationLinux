

PARENT和CHILD的输出顺序依赖于内核的进程调度算法。每次的输出都可能不一样。
```c
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

void main(void){
    int i;
    static char buffer[10];
    if(fork()==0){
        strcpy(buffer,"CHILD\n");
    }
    else{
        strcpy(buffer,"PARENT\n");
    }

    for(i=0;i<5;i++){
        sleep(1);
        write(1,buffer,sizeof(buffer));
    }
}
```