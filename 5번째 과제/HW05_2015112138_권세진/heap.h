#define DATASIZE 20

typedef struct Heap {
	void** heapAry;
	int last; // delete�Ҷ� �� ��������� ��ġ
	int maxSize;
	int size;
	int (*compare)(void* input, void* data2); // ���Լ�, input�� ��� insert�� ��, input�� ũ�� 1 , �۰ų� ������ 0����
}HEAP;

HEAP* CreateHeap(int maxSize);
int InsertHeap(HEAP* heap, void* dataPtr);
void PrintHeap(HEAP* heap);
void* DeleteHeap(HEAP* heap); // out�Ȱ��� �ּҸ� ��ȯ
void FreeHeap(HEAP* heap);