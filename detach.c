#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
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
    //将创建的线程分离出去
    pthread_detach(tid);
    void* retval;
    //此时就是一个主线程,
    int ree = pthread_join(tid,&retval);
    if(ree==EINVAL){
        printf("此线程不是一个joinable属性线程\n");
        return -1;
    }
    printf("线程退出原因: %s\n",(char*)retval);
    return 0;
}
