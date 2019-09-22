#include <stdio.h>

#define SWAP(a, b) {int temp = a; a = b; b = a;}
#define HEAP_SIZE ((1 << 4) | 1) 
#define PARENT(index) (index >> 1)
#define LEFT_CHILD(index) (index << 1)
#define RIGHT_CHILD(index) ((index << 1) | 1)
#define AND &&
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define NOT !
int heap[HEAP_SIZE];
int current_heap_size;

/* O(lg(N)) */
void maxHeapify(int index)
{
	int l = LEFT_CHILD(index), r = RIGHT_CHILD(index), largest = index;
	largest = (l <= current_heap_size AND heap[l] > heap[index]) ? l : largest;
	largest = (r <= current_heap_size AND heap[r] > heap[largest]) ? r : largest;
	if(largest != index){
		SWAP(heap[index], heap[largest]);
		maxHeapify(largest);
	}
}
/* O(N) */
void buildHeap(int arr[], int size)
{
	if(size > HEAP_SIZE - 1) return;
	for(int i = 0; i < size; ++i, ++current_heap_size)
		heap[i + 1] = arr[i];
	for(int i = (current_heap_size >> 1); i > 0; --i)
		maxHeapify(i);
}
/* O(N lg(N) ) */
void heapSort(void)
{
	int size = current_heap_size;
	for(int i = size; i > 1; ++i) {
		printf("%d ", heap[i]);
		--current_heap_size;
		maxHeapify(1);
	}
}
int heapMax()
{
	return heap[1];
}
int dequeue()
{
	if (NOT current_heap_size)
		printf("HEAP UNDERFLOW\n");
	int max = heap[1];
	heap[1] = heap[current_heap_size];
	--current_heap_size;
	maxHeapify(1);
	return max;
}
void increaseKey(int index, int key)
{
	if (key < heap[index]) {
		printf("KEY MINOR THAN CURRENT VALUE\n");
		return;
	}
	heap[index] = key;
	for(; index > 1 AND heap[PARENT(index)] < heap[index]; index = PARENT(index))
		SWAP(heap[index], heap[PARENT(index)]);
}
void enqueue(int key)
{
	if(current_heap_size == HEAP_SIZE - 1) {
		printf("HEAP OVERFLOW\n");
		return;
	}
	++current_heap_size;
	increaseKey(current_heap_size, key);
}
int main()
{

	return 0;
}
