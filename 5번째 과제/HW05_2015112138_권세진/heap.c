#include "heap.h"
#include "hash.h"
#include <stdio.h>
#include <math.h>

int _SimilarityTEST(void* input, void* data2) {//유사도 검사에 쓸 비교함수 input이 방금 insert한 값, input이 크면 1 , 같으면 0리턴 , 작으면 -1리턴
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
	heap->maxSize = (int)pow(2, ceil(log2(maxSize)))-1; // complete tree를 만들기위한부분
	heap->size = 0;
	heap->heapAry = (void**)calloc(heap->maxSize, sizeof(void*));
	heap->compare = _SimilarityTEST;
	if (!heap->heapAry) {
		free(heap);
		return NULL;
	}
	return heap;
}



void _ReheapUP(HEAP* heap, int index) { // index = reheapUP할 노드의 배열 위치
	int root = floor((index - 1) / 2);
	int test = heap->compare(((void**)heap->heapAry)[index], ((void**)heap->heapAry)[root]);
	void* temp;

	//index가 root가 되면 무조건 리턴
	if (index == 0) {
		return;
	}
	if (test == 1) { // 인풋이 크면 parent랑 바꿔줘야함
		temp = ((void**)heap->heapAry)[root]; // 루트 임시저장
		((void**)heap->heapAry)[root] = ((void**)heap->heapAry)[index];
		((void**)heap->heapAry)[index] = temp;
		_ReheapUP(heap, root); // recursive(재귀함수)
		return; // recursive 함수가 끝나면 1이 반환( reheapUP이 성공 )
	}
	else { // 인풋이 작거나 같으면 그대로 둠
		return;
	}
}


int InsertHeap(HEAP* heap,void* dataPtr) {
	((void**)heap->heapAry)[++heap->last] = dataPtr;
	_ReheapUP(heap, heap->last); // reheapUP을 진행
	heap->size++;
}

void _ReheapDOWN(HEAP* heap, int index) { // reheapDown
	int childL = 2 * index + 1;
	int childR = 2 * index + 2;
	void** heapAry = ((void**)heap->heapAry);
	int test;
	void* temp;

	if (heap->last < childL) {//자식 노드가 없으면 무조건 리턴
		return;
	}
	//자식 노드가 하나인지 둘인지 판단 ( 무조건 왼쪽부터 채워지는 complete tree라서 index가 작은것 체크 )
	if (heap->last == childL) { //자식 노드가 하나일 경우 -> 크기비교 후 자식이 크면 바꾸고 작으면 그대로 리턴
		test = heap->compare(heapAry[childL], heapAry[index]);
		if (test == 1) { // childL가 크면
			temp = heapAry[childL];
			heapAry[childL] = heapAry[index];
			heapAry[index] = temp;
			//자식노드가 하나면 더 이상 그밑의 자손이 없으므로
			return;
		}
		else {// 작으면 그대로 리턴
			return;
		}
	}
	else if (heap->last >= childR) {//자식 노드가 둘일 경우 -> 자식 둘중 자신보다 더큰값과 바꾼다. 둘다 작으면 그대로 리턴
		if (heap->compare(heapAry[childL], heapAry[index]) <= 0 && heap->compare(heapAry[childR], heapAry[index]) <= 0) { // 둘다작거나같을경우
			return;
		}
		else {
			test = heap->compare(heapAry[childL], heapAry[childR]);
			if (test == 1) { // childL가 더 크면 childL이랑 바꿈
				temp = heapAry[childL];
				heapAry[childL] = heapAry[index];
				heapAry[index] = temp;

				_ReheapDOWN(heap, childL); // 재귀함수
				return;
			}
			else if (test == -1) {// childR가 더 크면 childR이랑 바꿈
				temp = heapAry[childR];
				heapAry[childR] = heapAry[index];
				heapAry[index] = temp;

				_ReheapDOWN(heap, childR); // 재귀함수
				return;
			}
			else { // 둘다 같을 경우 그냥 왼쪽이랑 바꿔줌(뭐랑 바꾸든 상관없음)
				temp = heapAry[childL];
				heapAry[childL] = heapAry[index];
				heapAry[index] = temp;

				_ReheapDOWN(heap, childL); // 재귀함수
				return;
			}
		}
	}
}


void* DeleteHeap(HEAP* heap) { // out된값의 주소를 반환
	if (heap->size == 0){
		printf("더이상 힙에 데이터가 없습니다.\n");
		return NULL;
	}

	void* BigData = ((void**)heap->heapAry)[0]; // out된 가장 큰값의 주소

	((void**)heap->heapAry)[0] = ((void**)heap->heapAry)[heap->last--]; // 마지막 노드를 root에 넣음
	heap->size--;
	_ReheapDOWN(heap,0); // reheapDOWN을 진행

	return BigData;
}



void PrintHeap(HEAP* heap) {
	printf("heap : 나온횟수 (depth)");
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