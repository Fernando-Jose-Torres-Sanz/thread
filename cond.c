#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
//定义条件变量  0表示没有面   1表示有面
int is_have_noodles=0;
pthread_cond_t foodie_cond;
pthread_cond_t cook_cond;
pthread_mutex_t mutex;
void* thr_foodie(void* arg){
    //加锁
    while(1){
        pthread_mutex_lock(&mutex);
        while(is_have_noodles==0){
            //让线程进行等待
            pthread_cond_wait(&foodie_cond,&mutex);
        }
        printf("吃面的人吃了一碗面\n");
        usleep(1000);
        is_have_noodles=0;
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cook_cond);
    }
    return NULL;
} 
void* thr_cook(void* arg){
    while(1){
        pthread_mutex_lock(&mutex);
        while(is_have_noodles==1){
            pthread_cond_wait(&cook_cond,&mutex);
        }
        printf("做面的人做了一碗面\n");
        usleep(1000);
        is_have_noodles=1;
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&foodie_cond);
    }
    return NULL;
} 
int main(){
    pthread_t etid[4],ctid[4];
    int ret,i;
    pthread_cond_init(&foodie_cond,NULL);
    pthread_cond_init(&cook_cond,NULL);
    pthread_mutex_init(&mutex,NULL);
    //创建吃面者线程
    for(i=0;i<4;i++){
        ret=pthread_create(&etid[i],NULL,thr_foodie,NULL);
        if(ret!=0){
            printf("创建线程失败!!\n");
            return -1;
        }
    }
    //创建做面者线程
    for(i=0;i<4;i++){
        ret=pthread_create(&ctid[i],NULL,thr_cook,NULL);
        if(ret!=0){
            printf("创建线程失败!!\n");
            return -1;
        }
    }
    for(i=0;i<4;i++){
        pthread_join(etid,NULL);
        pthread_join(ctid,NULL);
    }
    pthread_cond_destroy(&foodie_cond);
    pthread_cond_destroy(&cook_cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}
