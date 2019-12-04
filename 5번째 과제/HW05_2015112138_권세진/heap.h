#define DATASIZE 20

typedef struct Heap {
	void** heapAry;
	int last; // delete할때 쓸 마지막노드 위치
	int maxSize;
	int size;
	int (*compare)(void* input, void* data2); // 비교함수, input이 방금 insert한 값, input이 크면 1 , 작거나 같으면 0리턴
}HEAP;

HEAP* CreateHeap(int maxSize);
int InsertHeap(HEAP* heap, void* dataPtr);
void PrintHeap(HEAP* heap);
void* DeleteHeap(HEAP* heap); // out된값의 주소를 반환
void FreeHeap(HEAP* heap);