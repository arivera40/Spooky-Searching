#include<stdlib.h>
#include<stddef.h>
#include<stdio.h>
#include<time.h>
#include <pthread.h>
#include"multitest.h"

int randomize(int size){
	return 1 + (rand() % size);
}

int main(int argc, char* argv){
	int *list = (int*)malloc(sizeof(int) * 20000);	//declaration for list of values (size sucesptible to change)
	int i;
	int j;
	int sizes[80];
	int workloadTimes[80];
	int totalTime;
	struct timeval start;
	struct timeval end;
	for(i=0; i < 20000; i++){
		list[i] = i+1;
	}

	int random;
	int size = 0;
	int childrenNum = 0;
	int split = 0;
	int target = randomize(250);	//Chooses random number to search for as target
	int targetIndex = -1;		//Keeps track of target's index in order to swap for next test
	while(size < 20000){	//20,000 / 250 = 80 iterations
		size += 250;
		sizes[j] = size;
		if(targetIndex != -1){
			random = randomize(size)-1;
			int swap = list[random];
			list[random] = list[targetIndex];
			list[targetIndex] = swap;
		}
		for(i=0; i < size; i++){
			random = randomize(size)-1;	//so includes index 0 to index 249
			int temp = list[random];
			list[random] = list[i];
			list[i] = temp;
		}
		childrenNum = size / 25;
		split = size/childrenNum;

		gettimeofday(&start, 0);
		targetIndex = findTarget(target, size, childrenNum, split, list);
		gettimeofday(&end, 0);
		workloadTimes[j] = ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
		totalTime += workloadTimes[j];
		j++;
	}
	for(i=0; i < 80; i++){
		printf("Array of size %d takes %d milliseconds to locate target\n", sizes[i], workloadTimes[i]);
	}
	printf("Average time to locate target: %d milliseconds\n", totalTime/80);
	return 0;
}
