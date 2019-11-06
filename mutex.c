#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t mutex;
int num=100;
void* yellow_cow(void* arg){
    int id=(int)arg;
    while(1){
        pthread_mutex_lock(&mutex);
        if(num>0){
            printf("抢到票了!!!-----票数: %d------黄牛id: %d\n",num,id);
            --num;
            usleep(10000);
        }
        else{
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);   
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    int i=0,ret;
    pthread_t tid[4];
    //互斥锁的初始化
    pthread_mutex_init(&mutex,NULL);
    for(i=0;i<4;i++){
        ret=pthread_create(&tid[i],NULL,yellow_cow,(void*)i);
        if(ret!=0){
            printf("线程创建失败!!\n");
            return -1;
        }
    }
    for(i=0;i<4;i++){
        pthread_join(tid[i],NULL);
    }
    //互斥锁的销毁
    pthread_mutex_destroy(&mutex);
    return 0;
}
