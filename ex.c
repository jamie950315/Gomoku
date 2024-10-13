#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <string.h>  

void clear(int* *arr){
	
	free(*arr);

	*arr=calloc(5,sizeof(int));
	for(int i=0;i<5;++i){
		(*arr)[i]=5-i;
	}
	
}

int main(void){
	int* arr=(int*)calloc(5,sizeof(int));
	for(int i=0;i<5;++i){
		arr[i]=i;
	}
	for(int i=0;i<5;++i){
		printf("%d ",arr[i]);
	}
	printf("\n");

	clear(&arr);
	for(int i=0;i<5;++i){
		printf("%d ",arr[i]);
	}
	free(arr);
	
	return 0;


}