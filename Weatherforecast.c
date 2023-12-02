#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/shm.h>
#include "structure.h"//structure declaration

static char prediction[100];

//function declarations
void writeToFile(struct WeatherData *data);
void makePrediction(struct WeatherData *data);
void error_handler(char* message);

int main() {
    
    int sval;
    
    //open semaphore  Readwrite mode
    sem_t * semaphore;
    semaphore = sem_open("/semaph",O_RDWR);
	
    size_t size = sizeof(struct WeatherData);
    
    //shared memory access
    int shmid = shmget((key_t)2000, size, 0666);
    
    //error handling
    if (shmid == -1) {
        error_handler("error shared memory\n");
    }

    WeatherData *shared_data = shmat(shmid, NULL, 0);
    
	if(semaphore == NULL)//SEM_FAILED == NULL
	{
		error_handler("sem_open fail");
			
	}
	else{
		//semaphore wait and post method
		sem_wait(semaphore);
		
			//printing semaphore value 
			sem_getvalue(semaphore,&sval);
			printf("\n semaphore val =(%d)\n",sval);
			// Write received data and prediction result to file
			writeToFile(shared_data);
			
		sem_post(semaphore);
		
		//printing semaphore value
		sem_getvalue(semaphore,&sval);
		printf("\n semaphore val =(%d)\n",sval);
	}
    return 0;
}


//error handler function
void error_handler(char* message){
	perror(message);
	exit(EXIT_FAILURE);
}

	
//weather Prediction Function	
void makePrediction(struct WeatherData *data) {

    //data comparision 
    if ((data->temperature > 25.0 && data->temperature <=50.0) &&  data->humidity >0.0 && data->humidity <60.0 ) {
    	if(data->wind >0.0 && data->wind < 8.0){
		printf("Prediction: Sunny\n");
		strcpy(prediction,"Sunny \u2600");//prediction with unicode
		
        }else if(data->wind >=8.00){
        	printf("Prediction: Sunny and Windy\n");
		strcpy(prediction,"Sunny and Windy \u2600 \U0001F32A");//prediction with unicode	
	}
	else{
    	printf("!! Prediction Failed !!\n");
    	strcpy(prediction,"!! Prediction Failed !!");
   	 }
    } 
    else if ((data->temperature > 15.0 && data->temperature <=25.0 )&&  data->humidity >0.0 && data->humidity <60.0  ) {
       if(data->wind >0.0 && data->wind < 15.0){
		printf("Prediction: Rainy\n");
        	strcpy(prediction,"Rainy \u2614");//storing unicode with prediction
        	
        }else if(data->wind >=15.0){
        	printf("Prediction: Rainy and chance of storm\n");
       	         strcpy(prediction,"Rainy and chance of storm \u2614 \u2601\u26A1");//storing unicode
	}
	else{
    	printf("!! Prediction Failed !!\n");
    	strcpy(prediction,"!! Prediction Failed !!");
   	 }
	   
    } 
    else if((data->temperature > 15.0 && data->temperature <=25.0 ) && data->humidity >0.0 && data->humidity <60.0 ){
    	if(data->wind >0.0 && data->wind < 15.0){
		printf("Prediction: Cloudy\n");
       		 strcpy(prediction,"Cloudy \u2601"); //storing unicode with prediction
       		 
        }else if(data->wind >=15.0){
        	printf("Prediction: Cloudy and Windy\n");
       		 strcpy(prediction,"Cloudy and Windy \u2601 \U0001F32A"); //storing unicode with prediction
    
	} 
	else{
    	printf("!! Prediction Failed !!\n");
    	strcpy(prediction,"!! Prediction Failed !!");
   	 }
    }
     else if((data->temperature > 0.0 && data->temperature <= 15.0) &&  data->humidity >0.0 && data->humidity <60.0  ){
    	if(data->wind >0.0 && data->wind < 15.0){
		printf("Prediction: Winter\n");
       		 strcpy(prediction,"Winter \u2744");//storing unicode with prediction
       	
        }else if(data->wind >=15.0){
        	printf("Prediction: Winter and Windy\n");
       		 strcpy(prediction,"Winter and Windy \u2744\U0001F32A"); //storing prediction with unicode
	} 
	 else{
    	printf("!! Prediction Failed !!\n");
    	strcpy(prediction,"!! Prediction Failed !!");
   	 }
    }
    else{
    	printf("!! Prediction Failed !!\n");
    	strcpy(prediction,"!! Prediction Failed !!");
    }
  
}

//Function to write data to file
void writeToFile(struct WeatherData *data) {
    
    //creating file in append mode
    FILE *file = fopen("data.txt", "a");
    if (file == NULL) {
        error_handler("file open failure");
    }
  
    makePrediction(data);
    
    //writing data to file
    fprintf(file, "Timestamp: %s %s\n", __TIME__,__DATE__);
    fprintf(file, "Temperature: %.2f\n", data->temperature);
    fprintf(file, "Humidity: %.2f\n", data->humidity);
    fprintf(file, "Wind: %.2f\n", data->wind);
    fprintf(file, "Weather Prediction : %s",prediction);
    fclose(file);
}
