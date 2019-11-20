  
#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef _multitest_h_	//if header is not defined
#define _multitest_h_	//then it will run this line and define it


#ifdef thread
#define findTarget(target, size, childrenNum, split, list) findTarget_thread( target, size, childrenNum, spilt, list)
void* splitSearch(void *);
int findTarget_thread(int, int, int, int, int*);
#endif

#ifdef proc
#define findTarget(target, size, childrenNum, split, list) findTarget_proc(target, size, childrenNum, split, list)
int findTarget_proc(int, int, int, int, int*);
#endif

#endif
