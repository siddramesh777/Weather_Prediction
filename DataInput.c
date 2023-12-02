
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "structure.h" // for structure declaration

//Function for error handling
void error_handler(char* message);

int main(int argc,char *argv[]) {

    //checking the count of the command line arguments	
    if(argc!=4){
    	fprintf(stderr,"Incorrect arguments count !! Enter temperature humidity and wind data\n");
	    exit(1);
    }
    else{
    
        size_t size = sizeof(WeatherData);
	//shared memory creation
        int shmid = shmget((key_t)2000, size, IPC_CREAT | 0666);
        
        //error handling 
   	if (shmid == -1) {
        	error_handler("Error Shmget Failed");
	}
	
	//attaching the structure to shared memory 
        WeatherData *shared_data = shmat(shmid, NULL, 0);

	//storing the user input in the shared memory
    	shared_data->temperature = atof(argv[1]);
   	shared_data->humidity = atof(argv[2]);
    	shared_data->wind = atof(argv[3]);

        //error handling
    	if (shmdt(shared_data) == -1) {
     	  	error_handler("Error Shmdt Failed ");
 	   }

    printf("Data sent to shared memory.\n");
    }
    return 0;
}

//error handler function
void error_handler(char* message){
	//prints the error message 
	perror(message);
	exit(EXIT_FAILURE);
}


