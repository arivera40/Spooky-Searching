#include<stdlib.h>
#include<stddef.h>
#include<stdio.h>
#include<time.h>
#include <pthread.h>
#include"multitest.h"

//pthread_t threadID[2];
//pthread_mutex_t lock;

int randomize(int size){
	return 1 + (rand() % size);
}

int main(int argc, char* argv){
	int *list = (int*)malloc(sizeof(int) * 20000);	//declaration for list of values (size sucesptible to change)
	int i;
	for(i=0; i < 20000; i++){
		list[i] = i+1;
	}

	int random;
	//First 250 values randomized
	for(i=0; i < 250; i++){
		random = randomize(250);
		int temp = list[random];
		list[random] = list[i];
		list[i] = temp;
	}
	int target = randomize(250);	//Chooses random number to search for as target

/*	int error;
	if(pthread_mutex_init(&lock, NULL) != 0){
		printf("\n mutex init has failed\n");
		return 1;
	}
	int i;
	for(i=0; i < 2; i++){
		error = pthread_create(&(threadID[i]), NULL, &test_thread, &lock);
		if(error != 0){
			printf("\nThread can't be created: [%s]", strerror(error));
		}
	}
	pthread_join(threadID[0], NULL);
	pthread_join(threadID[1], NULL);
	pthread_mutex_destroy(&lock);	*/
}
