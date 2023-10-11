#define _REENTRANT
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#define MAX 5
#define TRAND(limit, n)                                     \
    {                                                       \
        struct timeval t;                                   \
        gettimeofday(&t, (void *)NULL);                     \
        (n) = rand_r((unsigned *)&t.tv_usec) % (limit) + 1; \
    }

void *say_it(void *);

int main(int argc, char *argv[])
{
    int i;
    pthread_t thread_id[MAX];
    int status, *p_status = &status;

    // 检查参数列表
    if (argc > MAX + 1)
    {
        fprintf(stderr, "%s arg1,arg2,... arg%d", *argv, MAX);
        exit(1);
    }

    printf("Displaying\n");

    // 创建线程
    for (i = 0; i < argc - 1; ++i)
    {
        if (pthread_create(&thread_id[i], NULL, say_it, (void *)argv[i + 1]) > 0)
        {
            fprintf(stderr, "pthread_create failure\n");
            exit(2);
        }
    }

    // 等待线程执行
    for (i = 0; i < argc - 1; ++i)
    {
        if (pthread_join(thread_id[i], (void **)p_status) > 0)
        {
            fprintf(stderr, "pthread_join failure\n");
            exit(3);
        }
        printf("\nThread %ld returns %d", thread_id[i], status);
    }

    printf("\nDone\n");
    exit(0);
}

// 回调函数
void *say_it(void *word)
{
    int i, numb;
    TRAND(MAX, numb);
    printf("\n%d %s", numb, (char *)word);
    // for (i = 0; i < numb; ++i)
    // {
    //     sleep(1);
    //     printf("%s", (char *)word);
    // }
    return (void *)NULL;
}