#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>

#define BUF_SZ 10

int main(void){
    int sock[2];//套接字对
    int cpid,i;
    static char buf[BUF_SZ];//消息的临时缓冲区

    if(socketpair(PF_UNIX,SOCK_STREAM,0,sock)<0){
        perror("Generation error");
        exit(1);
    }

    switch (cpid=(int)fork())
    {
    case -1:
        perror("Bad fork");
        exit(2);
    case 0:
        //子进程
        close(sock[1]);
        for(i=0;i<10;i+=2){
            sleep(1);
            sprintf(buf,"c: %d\n",i);
            write(sock[0],buf,sizeof(buf));
            read(sock[0],buf,BUF_SZ);
            printf("c-> %s",buf);//打印来自父进程的消息
        }
        close(sock[0]);
        break;
    default:
        close(sock[0]);
        for(i=1;i<10;i+=2){
            sleep(1);
            read(sock[1],buf,BUF_SZ);
            printf("p-> %s",buf);////打印来自子进程的消息
            sprintf(buf,"p: %d\n",i);
            write(sock[1],buf,sizeof(buf));
        }
        close(sock[1]);
        break;
    }
    return 0;
}