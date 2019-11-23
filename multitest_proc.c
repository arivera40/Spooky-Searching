#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"multitest.h"
#include<pthread.h>
#include<unistd.h>
#include <ulimit.h>

int initialize = 0;
int findTarget_proc(int target, int size, int procsNum, int split, int *list){

	if(initialize == 0){
		printf("Using proccesses!\n");
		initialize = 1;
	}

	pid_t child[procsNum];
	int i;
	int count = 0; //where each child[k] will start looping
	int k = 0;
	for(i = 0; i < procsNum; i++){
		child[i] = fork();
		if(child[i] < 0){

		}else if(child[i] == 0){
			for(k = count; k<split+count; k++){
				if(list[k] == target){
					
					exit(k);
				}
			}
			exit(255);
		}
		count+=split;
	}
	
	int answer;
	int exit_status;
	for(i = 0; i<procsNum; i++){

		wait(&child[i]);	//waits for all children	
		exit_status = WEXITSTATUS(child[i]); //returns the value of each child;
		if(exit_status != 255){
			answer = exit_status; //holds index of where target was found			
		}
	}

	return answer;


}
