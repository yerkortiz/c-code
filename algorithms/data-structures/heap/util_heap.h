#ifdef UTIL_HEAP.H
#define SWAP(a, b) {int temp = a; a = b; b = a;}
#define HEAP_SIZE ((1 << 4) | 1)
#define PARENT(index) (index >> 1)
#define LEFT_CHILD(index) (index << 1)
#define RIGHT_CHILD(index) ((index << 1) | 1)
#define AND &&
#define HEAP_PROPERTY(parent, child, heap) (heap[child] > heap[parent])
#define CHILD_CHECK(child, size) (child <= size)
#endif UTIL_HEAP.H