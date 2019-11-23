#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"multitest.h"
#include<pthread.h>
#include<unistd.h>	

typedef struct Arguments{
	int start;
	int end;
	int target;
	int targetIndex;
}Arguments;

int *list;	//made this global so my splitSearch function has access to it
int initialize = 0;

void * splitSearch(void *args){
	Arguments *arguments = (Arguments*)args;
	int result = -1;
	int i;
	for(i=arguments->start; i < arguments->end; i++){
		if(list[i] == arguments->target){
			arguments->targetIndex = i;
			break;
		}
	}
	pthread_exit((void*)arguments);
}
//This function will act as main function
int findTarget_thread(int target, int size, int threadNum, int split,int *array){
	int totalSize = size;	
	if(initialize == 0){
		printf("Using threads!\n");
		initialize = 1;
	}
	pthread_t threads[threadNum];
	list = array;
	void *status;

	int i;
	int start;
	int end = 0;
	for(i=0; i < threadNum; i++){
		if(size - split >= 0){
			size = size - split;
			start = end;
			end = start + split;
		}else{
			start = end;
			end = start + size;
		}
		Arguments *args = (Arguments*)malloc(sizeof(Arguments));
		args->start = start;
		args->end = end;
		args->target = target;
		args->targetIndex = -1;
		pthread_create(&threads[i], NULL, splitSearch, (void*)args);
	}
	int result = -1;
	for(i=0; i < threadNum; i++){
		pthread_join(threads[i], (void**)&status);
		Arguments *arguments = (Arguments*)status;
		if(arguments->targetIndex != -1){
			result = arguments->targetIndex;
		}
		free(arguments);
	}
	return result;
}
