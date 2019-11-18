void push(int *arr, int index, int value, int *size, int *capacity);
typedef struct 
{
     int size = 0;
     int capacity = INITIAL_CAPACITY;
     int* arr = malloc(INITIAL_CAPACITY * sizeof(int));
} vector;
void push(int *arr, int index, int value, int *size, int *capacity)
{
     if(*size > *capacity){
          void *ignore = realloc(arr, sizeof(arr) * 2);
          *capacity = sizeof(arr) * 2;
     }
     arr[index] = value;
     *size = *size + 1;
}