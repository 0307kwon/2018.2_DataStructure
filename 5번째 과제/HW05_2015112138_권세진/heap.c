#include "heap.h"
#include "hash.h"
#include <stdio.h>
#include <math.h>

int _SimilarityTEST(void* input, void* data2) {//���絵 �˻翡 �� ���Լ� input�� ��� insert�� ��, input�� ũ�� 1 , ������ 0���� , ������ -1����
	if (((HNODE*)input)->freq > ((HNODE*)data2)->freq) {
		return 1;
	}
	else if(((HNODE*)input)->freq == ((HNODE*)data2)->freq){
		return 0;
	}
	else {
		return -1;
	}
}

HEAP* CreateHeap(int maxSize) {		
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	if (!heap)
		return NULL;

	heap->last = -1;
	heap->maxSize = (int)pow(2, ceil(log2(maxSize)))-1; // complete tree�� ��������Ѻκ�
	heap->size = 0;
	heap->heapAry = (void**)calloc(heap->maxSize, sizeof(void*));
	heap->compare = _SimilarityTEST;
	if (!heap->heapAry) {
		free(heap);
		return NULL;
	}
	return heap;
}



void _ReheapUP(HEAP* heap, int index) { // index = reheapUP�� ����� �迭 ��ġ
	int root = floor((index - 1) / 2);
	int test = heap->compare(((void**)heap->heapAry)[index], ((void**)heap->heapAry)[root]);
	void* temp;

	//index�� root�� �Ǹ� ������ ����
	if (index == 0) {
		return;
	}
	if (test == 1) { // ��ǲ�� ũ�� parent�� �ٲ������
		temp = ((void**)heap->heapAry)[root]; // ��Ʈ �ӽ�����
		((void**)heap->heapAry)[root] = ((void**)heap->heapAry)[index];
		((void**)heap->heapAry)[index] = temp;
		_ReheapUP(heap, root); // recursive(����Լ�)
		return; // recursive �Լ��� ������ 1�� ��ȯ( reheapUP�� ���� )
	}
	else { // ��ǲ�� �۰ų� ������ �״�� ��
		return;
	}
}


int InsertHeap(HEAP* heap,void* dataPtr) {
	((void**)heap->heapAry)[++heap->last] = dataPtr;
	_ReheapUP(heap, heap->last); // reheapUP�� ����
	heap->size++;
}

void _ReheapDOWN(HEAP* heap, int index) { // reheapDown
	int childL = 2 * index + 1;
	int childR = 2 * index + 2;
	void** heapAry = ((void**)heap->heapAry);
	int test;
	void* temp;

	if (heap->last < childL) {//�ڽ� ��尡 ������ ������ ����
		return;
	}
	//�ڽ� ��尡 �ϳ����� ������ �Ǵ� ( ������ ���ʺ��� ä������ complete tree�� index�� ������ üũ )
	if (heap->last == childL) { //�ڽ� ��尡 �ϳ��� ��� -> ũ��� �� �ڽ��� ũ�� �ٲٰ� ������ �״�� ����
		test = heap->compare(heapAry[childL], heapAry[index]);
		if (test == 1) { // childL�� ũ��
			temp = heapAry[childL];
			heapAry[childL] = heapAry[index];
			heapAry[index] = temp;
			//�ڽĳ�尡 �ϳ��� �� �̻� �׹��� �ڼ��� �����Ƿ�
			return;
		}
		else {// ������ �״�� ����
			return;
		}
	}
	else if (heap->last >= childR) {//�ڽ� ��尡 ���� ��� -> �ڽ� ���� �ڽź��� ��ū���� �ٲ۴�. �Ѵ� ������ �״�� ����
		if (heap->compare(heapAry[childL], heapAry[index]) <= 0 && heap->compare(heapAry[childR], heapAry[index]) <= 0) { // �Ѵ��۰ų��������
			return;
		}
		else {
			test = heap->compare(heapAry[childL], heapAry[childR]);
			if (test == 1) { // childL�� �� ũ�� childL�̶� �ٲ�
				temp = heapAry[childL];
				heapAry[childL] = heapAry[index];
				heapAry[index] = temp;

				_ReheapDOWN(heap, childL); // ����Լ�
				return;
			}
			else if (test == -1) {// childR�� �� ũ�� childR�̶� �ٲ�
				temp = heapAry[childR];
				heapAry[childR] = heapAry[index];
				heapAry[index] = temp;

				_ReheapDOWN(heap, childR); // ����Լ�
				return;
			}
			else { // �Ѵ� ���� ��� �׳� �����̶� �ٲ���(���� �ٲٵ� �������)
				temp = heapAry[childL];
				heapAry[childL] = heapAry[index];
				heapAry[index] = temp;

				_ReheapDOWN(heap, childL); // ����Լ�
				return;
			}
		}
	}
}


void* DeleteHeap(HEAP* heap) { // out�Ȱ��� �ּҸ� ��ȯ
	if (heap->size == 0){
		printf("���̻� ���� �����Ͱ� �����ϴ�.\n");
		return NULL;
	}

	void* BigData = ((void**)heap->heapAry)[0]; // out�� ���� ū���� �ּ�

	((void**)heap->heapAry)[0] = ((void**)heap->heapAry)[heap->last--]; // ������ ��带 root�� ����
	heap->size--;
	_ReheapDOWN(heap,0); // reheapDOWN�� ����

	return BigData;
}



void PrintHeap(HEAP* heap) {
	printf("heap : ����Ƚ�� (depth)");
	for (int i = 0; i < heap->size; i++) {
		if (floor(log2(i)) != floor(log2(i + 1))) {
			printf("\n");
		}
		printf(" %d (%.0f) ", ((HNODE*)((void**)heap->heapAry)[i])->freq, floor(log2(i+1)));
	}
	printf("\n");
}

void FreeHeap(HEAP* heap) {
	free(heap->heapAry);
}