#pragma once
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

pthread_t go(void*(*function)(void*), void *args){
	pthread_t t;
	pthread_create(&t, NULL, function, args);
	return t;
}
