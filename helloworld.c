#include <pthread.h>
#include <stdio.h>
#define number_of_threads 5

void* printHelloWorld ( void* threadID ) {

    long tid ;
    int i ; 
    
    tid     = (long) threadID ;
    for ( i = 0 ; i < 20 ; i ++ ) {
        sleep ( 1 ) ;
        printf ( " Hello World ! pthread ID is %ld \n" , tid ) ;
    }
    
    pthread_exit ( NULL ) ;

} 

void* printHelloWorld2 ( void* threadID ) {

    long tid ;
    int i ;
    
    tid     = (long) threadID ;
    for ( i = 0 ; i < 20 ; i ++ ) {
        sleep ( 1 ) ;
        printf ( " Suck my balls, world ! pthread ID is %ld \n" , tid ) ;
    }
    
    pthread_exit ( NULL ) ;

} 


int main ( int argc, char* argv[] ) {

    pthread_t threads[number_of_threads] ;

    int rc ;
    long t = 0 ;

    rc = pthread_create ( &threads[1] , NULL , printHelloWorld , (void *) 1 ) ;
    rc = pthread_create ( &threads[2] , NULL , printHelloWorld2 , (void *) 2 ) ;

    
    pthread_exit ( NULL ) ; 

}
