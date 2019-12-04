#include "hash.h"
#include "heap.h"
#include <stdio.h>
#include <string.h>


void InsertHashToHeap(HTABLE* hash,HEAP* heap) {
	for (int i = 0; i < hash->maxSize; i++) {
		HNODE* temp = &((HNODE*)hash->hTable)[i];
		if (temp->dataPtr != NULL) {
			//collision 난것도 추가해줘야함
			while (temp->next != NULL) { // 널일때 while 중단
				InsertHeap(heap, temp);
				temp = temp->next;
			}
			InsertHeap(heap, temp);
		}
	}
}

void Similarity(HEAP* data1,HEAP* data2 ) {
	HNODE* temp_data1 = DeleteHeap(data1);
	HNODE* temp_data2 = DeleteHeap(data2);

	int maxSize; // 두개의 힙중 데이터 크기가 작은 힙을 기준으로 비교를 끝낼 것이므로 작은 힙의 크기를 저장
	if (data1 == NULL || data2 == NULL) 
		return;

	HNODE* Big_data1[10];
	HNODE* Big_data2[10];

	int i = 0;// big_data의 배열위치,일치하는 갯수로 쓸수도 있음
	int i2 = 0; // 상위 빈도수 비교 횟수, 총 10번해야됨
	printf("------------------------------------------------------------\n");
	while (i2 <10 && temp_data1 != NULL && temp_data1 != NULL) {
		if (temp_data1->freq == temp_data2->freq) {
			Big_data1[i] = temp_data1;
			Big_data2[i] = temp_data2;
			printf("%s , %s => 사용된 횟수 %d번으로 같습니다.\n", Big_data1[i]->dataPtr, Big_data2[i]->dataPtr, Big_data1[i]->freq);
			i++;
			
		}

		//힙에서 다음 큰 값을 빼냄
		temp_data1 = DeleteHeap(data1);
		temp_data2 = DeleteHeap(data2);
		//

		i2++;
	}
	printf("------------------------------------------------------------\n");
	printf("빈도수 상위 10개 중 %d 개 일치 => 유사도 :%d 퍼센트 \n", i, i * 10);
}


void main() {
	//첫번째 텍스트 파일 헤쉬에 저장 ->힙에 담음
	printf("file1 ------------------------------------\n");
	HTABLE* hash = _CreateHash('S',50);


	FILE* ex1;
	errno_t err = fopen_s(&ex1, "ex1.txt", "r");
	

	KeywordToHash(ex1,hash);
	_PrintHash(hash);
	printf("\n노드수 %d\n", hash->NodeNumber);

	HEAP* heap = CreateHeap(hash->NodeNumber); // 해쉬의 노드 수만큼 힙의 크기를 만듦, 힙의 메모리 효율을위해
	InsertHashToHeap(hash, heap);
	PrintHeap(heap);

	

	//두번째 텍스트 파일 헤쉬에 저장 ->힙에 담음
	//\\

	printf("\n\n");
	printf("file2 ------------------------------------\n");

	HTABLE* hash2 = _CreateHash('S', 50);
	FILE* ex2;
	errno_t err2 = fopen_s(&ex2, "ex2.txt", "r");

	KeywordToHash(ex2, hash2);
	_PrintHash(hash2);
	printf("\n노드수 %d\n", hash2->NodeNumber);

	HEAP* heap2 = CreateHeap(hash2->NodeNumber); // 해쉬의 노드 수만큼 힙의 크기를 만듦, 힙의 메모리 효율을위해
	InsertHashToHeap(hash2, heap2);
	PrintHeap(heap2);

	printf("유사도 검사를 실시하시겠습니까? (y/n) ");
	if (getchar() == 'y') {
		getchar();

		Similarity(heap, heap2);

	}
	else {
		getchar();

		
	}
	//해쉬 2개 free
	FreeHash(hash);
	FreeHeap(heap);
	FreeHash(hash2);
	FreeHeap(heap2);
	printf("free 완료, 프로그램을 종료합니다.\n");
	getchar();
}
