#include<stdio.h>
#include<fcntl.h>
#include<semaphore.h>
#include<stdlib.h>

//function declaration
void error_handler(char* message);

 
int main(){
	int sval;
	//semaphore creation
        sem_t* semaphore;
 	semaphore = sem_open("/semaph",O_CREAT|O_RDWR,0666,1);
    
   	 if(semaphore == NULL)//SEM_FAILED == NULL
	{
		error_handler("semaphore failed");
	}
	else{
		printf("\n sem_open success");
	}
	int val =sem_getvalue(semaphore,&sval);
	if(val ==-1){
		error_handler("Error sem_getvalue failed");	
	}
}

//error handler function
void error_handler(char *message){
	perror(message);
	exit(EXIT_FAILURE);
}




