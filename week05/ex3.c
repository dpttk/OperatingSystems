# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include <pthread.h> 

bool is_prime ( int n) {
    if (n <= 1) return false;

    int i = 2;

    for (; i * i <= n; i++) {
        if (n % i == 0)
        return false ;
    }
    return true ;
}



int primes_count (int a, int b)
{
    int ret = 0;
    for (int i = a; i < b; i++)
        if ( is_prime (i) != 0)
            ret ++;
    return ret ;
}


typedef struct prime_request
{
    int a, b;
} prime_request;

void * prime_counter (void *arg)
{
    prime_request req = *(struct prime_request *)arg ;
    int * count = (int * )malloc(sizeof(int));
    *count = primes_count(req.a, req.b);

    return (( void *) count );
} 


int main (int argc, char ** args){

    int n = atoi(args[1]);
    int m = atoi(args[2]);

    pthread_t threads[m];
    struct prime_request * requests[m];
    for (int i = 0; i < m; i++){
        requests[i] = (struct prime_request *)malloc(sizeof(struct prime_request));
        requests[i]->a = n/m * (i);
        requests[i]->b = n/m * (i+1);
        pthread_create(&threads[i],NULL ,&prime_counter,requests[i]);
    }
    
    int res = 0;
    for (int i = 0; i < m; i++){
        int* temp;
        pthread_join(threads[i], (void **) &temp);
        res += *temp;
        free(temp); 
        free(requests[i]);
    } 

    printf("%d", res);

}