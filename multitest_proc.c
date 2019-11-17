#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"multitest.h"
#include<pthread.h>
#include<unistd.h>
#include <ulimit.h>


int findTarget_proc(int target, int size, int *list){
	
	int procsNum = size/10;
	int split = size/procsNum;
	pid_t child[procsNum];
	int i;
	int count = 0; //where each child[k] will start looping
	int k = 0;
	for(i = 0; i < procsNum; i++){
		
		if((child[i] = fork()) ==  < 0){

			printf("Child %d, fork failed", i);

		}else if((child[i] = fork()) == 0){
			for(k = count; k<split+count; k++){
				if(list[k] == target){
					exit(k);
				}
			}
			exit(-1);
		}
		count+=split;
	}
	
	int status = 0;
	int answer;
	for(i = 0; i<procsNum; i++){

		waitpid((child[procsNum], &status,0); //waits for all children
		
		status = WEXITSTATUS(status); //returns the value of each child;
		if(status != -1){
			answer = status; //holds index of where target was found
		}
	}

	return answer;


}
