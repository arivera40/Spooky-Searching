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
}Arguments;

int *list;	//made this global so my splitSearch function has access to it

void * splitSearch(void *args){
	Arguments *arguments = (Arguments*)args;
	int *theStatus;
	int result = -1;
	int i;
	for(i=arguments->start; i < arguments->end; i++){
		if(list[i] == arguments->target){
			result = i;
			break;
		}
	}
	theStatus = &result;
	free(arguments);
	pthread_exit((void*)theStatus);
	return (void*)theStatus;
}
//This function will act as main function
int findTarget_thread(int target, int size, int threadNum, int split,int *array){
	pthread_t threads[threadNum];
	list = array;
	void *status;
	int *exitStatus = (int*)malloc(sizeof(int) * threadNum);
	//Arguments *args = (Arguments *)malloc(sizeof(Arguments) * threadNum);

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
		pthread_create(&threads[i], NULL, splitSearch, (void*)args);
	}
	for(i=0; i < threadNum; i++){
		pthread_join(threads[i], &status);
		int *result = (int*)status;
		exitStatus[i] = *result;
		if(exitStatus[i] != -1){
			return exitStatus[i];
		}
	}
	return -1;
}
