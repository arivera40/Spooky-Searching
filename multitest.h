#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef _multitest_h_	//if header is not defined
#define _multitest_h_	//then it will run this line and define it
#endif

#ifdef thread
#define findTarget( x ) findTarget_thread( x )
findTarget_thread(void *);
#endif

#ifdef proc
#define findTarget(x) findTarget_proc(x)
findTarget_proc(void *);
#endif
