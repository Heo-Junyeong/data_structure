#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MAX_SIZE 100

typedef struct phone
{
	int id;
	char number[30];
}phone_t;

typedef int data_t;

typedef struct array
{
	data_t data[ARRAY_MAX_SIZE];
	size_t size;
}array_t;

int array_append(array_t* arr, data_t data)
{
	if (arr->size == ARRAY_MAX_SIZE) return -1;      // full stack
	arr->data[arr->size++] = data;
}

int array_delete(array_t* arr)
{
	if (arr->size == 0) return -1;      // zero stack
	arr->size--;
}

void array_init(array_t* arr)
{
	for (int i = 0; i < ARRAY_MAX_SIZE; i++) arr->data[i] = 0;
	arr->size = 0;
}

int main(void)
{
	array_t arr;

	array_init(&arr);
	array_append(&arr, 10);
	array_append(&arr, 20);
	array_append(&arr, 30);

	printf("%d %d %d\n", arr.data[0], arr.data[1], arr.data[2]);
}