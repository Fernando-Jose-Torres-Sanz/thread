#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* fun(void *arg){
    //获取调用线程的tid
    pthread_t tid=pthread_self();
    while(1){
        printf("======新线程=====  %s %lu \n",arg,tid);
        sleep(1);
    }
    return NULL;
}

int main(){
    char* bu="houxinggang";
    //ret用来接收pthread_create的返回值
    int ret;
    //tid 是用来接受线程的标识符
    pthread_t tid;
    pthread_t mtid;
    mtid=pthread_self();
    ret=pthread_create(&tid,NULL,fun,(void*)bu);
    if(ret!=0){
        printf("线程创建失败\n");
        return -1;
    }
    //退出创建线程
    pthread_cancel(tid);
    pthread_exit(NULL);
    while(1){
        printf("======主线程=====              %lu \n",mtid);
        sleep(1);
    }
    return 0;
}
