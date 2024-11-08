# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>


bool is_prime ( int n){
    if (n <= 1) return false;

    int i = 2;

    for (; i * i <= n; i++) {
        if (n % i == 0)
        return false ;
    }
    return true ;
}


pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER ;

int k = 0;
int c = 0;

int n = 0;


int get_number_to_check ()
{
    pthread_mutex_lock(&global_lock);
    int ret = k;
    if (k != n)
        k++;
    pthread_mutex_unlock(&global_lock); 

    return ret ;
}

void increment_primes ()
{
    pthread_mutex_lock(&global_lock);
    c++;
    pthread_mutex_unlock(&global_lock); 

}



void * check_primes ( void * arg )
{
    while (1) {
        int temp = get_number_to_check();
        if(temp==n)
            break;
        if (is_prime(temp))
            increment_primes();
    }
}


int main (int argc, char ** args){

    n = atoi(args[1]);
    int m = atoi(args[2]);

    pthread_t threads[m];

    for (int i =0; i<m;i++){
        pthread_create(&threads[i],NULL ,&check_primes,NULL);
    }
    
    for (int i = 0; i < m; i++){
        pthread_join(threads[i], NULL);
    } 

    printf("%d", c);


}

