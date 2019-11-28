#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* thr_start(void* arg){
    char* buf="nihao";
    sleep(5);
    return buf;
}
int main(){

    pthread_t tid;
    int ret=pthread_create(&tid,NULL,thr_start,NULL);
    if(ret!=0){
        printf("创建线程失败\n");
        return -1;
    }
    void* retval;
    pthread_join(tid,&retval);
    printf("线程退出原因: %s\n",(char*)retval);
    return 0;
}
