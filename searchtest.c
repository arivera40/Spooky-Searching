#include<stdlib.h>
#include<stddef.h>
#include<stdio.h>
#include<time.h>
#include <pthread.h>
#include"multitest.h"
#include<math.h>

typedef struct Test{
	int size;
	int targetIndex;
	int target;
	int workers;
	int time;
}Test;

int first = 0;
int randomize(int size){
	if(first == 0){
		first = 1;
		srand(time(NULL));
	}
	return 1 + (rand() % size);
}

int main(int argc, char* argv){
	int *list = (int*)malloc(sizeof(int) * 20000);	//declaration for list of values (size sucesptible to change)
	int i;
	int j = 0;
	Test tests[80];
	int totalTime;
	struct timeval start;
	struct timeval end;
	for(i=0; i < 20000; i++){
		list[i] = i+1;
	}

	int random;
	int split = 0;
	int size = 0;
	int target = randomize(250);	//Chooses random number to search for as target
	int targetIndex = -1;		//Keeps track of target's index in order to swap for next test
	while(size < 20000){	//20,000 / 250 = 80 iterations
		size += 250;
		tests[j].size = size;
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
		tests[j].workers = size / 25;
		split = size/tests[j].workers;

		gettimeofday(&start, 0);
		targetIndex = findTarget(target, size, tests[j].workers, split, list);
		tests[j].targetIndex = targetIndex;
		gettimeofday(&end, 0);
		tests[j].time = ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
		totalTime += tests[j].time;
		tests[j].target = target;
		j++;
	}
	float standardDeviation = 0;
	int max = 0;
	int min = 100000;
	for(i=0; i < 80; i++){
		printf("Array of size %d takes %d milliseconds to locate target\n", tests[i].size, tests[i].time);
		printf("Number of workers: %d\nIndex of target (%d) is found in: %d\n\n", tests[i].workers, tests[i].target, tests[i].targetIndex);
		standardDeviation += pow((tests[i].time - (totalTime/80)), 2);
		if(tests[i].time > max) max = tests[i].time;
		if(tests[i].time < min) min = tests[i].time;
	}
	printf("Average time to locate target: %d milliseconds\nStandard deviation: %.6f milliseconds\n", totalTime/80, sqrt(standardDeviation/80));
	printf("Min: %d milliseconds, Max: %d milliseconds\n", min, max);
	return 0;
}
