#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"multitest.h"
#include<pthread.h>
#include<unistd.h>	

//This function will act as main function
int findTarget_thread(int target, int size, int *list){
	int threadNum = size / 100;
	int split = size / threadNum;
	void *status;
	pthread_t threads[threadNum];
	int *exitStatus = (int*)malloc(sizeof(int) * threadNum);

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
		pthread_create(&threads[i], NULL, splitSearch, start, end, target, list);
	}
	for(i=0; i < threadNum; i++){
		pthread_join(thread[i], &status);
		int *result = (int*)status;
		exitStatus[i] = *result;
		if(*exitStatus[i] != -1){
			return *exitStatus[i];
		}
	}
	return -1;
}

void * splitSearch(int start, int end, int target, int *list){
	int *theStatus;
	int result = -1;
	int i;
	for(i=start, i < end; i++){
		if(list[i] == target){
			result = i;
			break;
		}
	}
	theStatus = &result;
	pthread_exit((void*)theStatus);
	return (void*)theStatus;
}
