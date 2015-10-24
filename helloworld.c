#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct readThreadParams {
	pthread_t	readThread ;
	char 		data[256] ;
	int 		lineNum ;
	FILE* 		readFile ;
	FILE*		writeFile ;
};

void *bufferRead ( void* context ) {

	printf ( "buffer Read entered.\n" ) ;

	struct readThreadParams *readParams = context ;
	int lineCount 		= 0 ;
	// jump the specific line
	for ( lineCount = 0 ; lineCount < readParams->lineNum ; lineCount ++ ) 
		fgets( readParams->data , sizeof(readParams->data), readParams->readFile ) ;

	printf ( "jump reached.\n " ) ;

	// read line
	fgets( readParams->data , sizeof(readParams->data), readParams->readFile ) ;

	printf ( "read line.\n" ) ;

	// display line
	printf ( "%s\n" , readParams->data ) ;
	// write line
	fprintf ( readParams->writeFile, readParams->data ) ;
	// exit
	pthread_exit ( NULL ) ;
}

int main ( int argc, char* argv[] ) {

	char const* const readFileName 		= argv[1]; 
	char const* const writeFileName 	= argv[2]; 

    FILE* readFile[10] ; 
    FILE* writeFile[10]; 
	
	int i = 0 ;
	for ( i = 0 ; i < 10 ; i ++ ) {
		readFile[i] 		= fopen(readFileName, "r") ;
		writeFile[i] 		= fopen(writeFileName, "a") ;
	}

	// This is sequential reading 
	// char line[256];
    // while (fgets(line, sizeof(line), readFile)) {
    //     printf("%s", line); 
	// 	fprintf ( writeFile, line ) ;
    // }
	  
	// This is parelell reading and writing	
	long threadNum = 0 ;
	int threadCreated ;	
	
	struct readThreadParams threadParams[10] ; 
	for ( threadNum = 0 ; threadNum < 10 ; threadNum ++ ) {
		threadParams[threadNum].lineNum 	= threadNum ;
		threadParams[threadNum].readFile 	= readFile[threadNum] ;
		threadParams[threadNum].writeFile 	= writeFile[threadNum] ;
	}

	for ( threadNum = 0 ; threadNum < 10 ; threadNum ++ ) {
		printf ( " %lu threads segmentfault.\n", threadNum ) ;
		threadCreated = pthread_create ( &threadParams[threadNum].readThread, 
							NULL, bufferRead, &threadParams[threadNum] ) ;
		if ( threadCreated < 0 ) {
			printf ( " %lu threads failed to be created.\n", threadNum ) ;
		}
	}
	pthread_exit ( NULL ) ;

	for ( i = 0 ; i < 10 ; i ++ ) {
		fclose(readFile[i]);
		fclose(writeFile[i]);
	}

    return 0;

}

