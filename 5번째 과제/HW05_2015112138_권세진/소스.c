#include "hash.h"
#include "heap.h"
#include <stdio.h>
#include <string.h>


void InsertHashToHeap(HTABLE* hash,HEAP* heap) {
	for (int i = 0; i < hash->maxSize; i++) {
		HNODE* temp = &((HNODE*)hash->hTable)[i];
		if (temp->dataPtr != NULL) {
			//collision ���͵� �߰��������
			while (temp->next != NULL) { // ���϶� while �ߴ�
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

	int maxSize; // �ΰ��� ���� ������ ũ�Ⱑ ���� ���� �������� �񱳸� ���� ���̹Ƿ� ���� ���� ũ�⸦ ����
	if (data1 == NULL || data2 == NULL) 
		return;

	HNODE* Big_data1[10];
	HNODE* Big_data2[10];

	int i = 0;// big_data�� �迭��ġ,��ġ�ϴ� ������ ������ ����
	int i2 = 0; // ���� �󵵼� �� Ƚ��, �� 10���ؾߵ�
	printf("------------------------------------------------------------\n");
	while (i2 <10 && temp_data1 != NULL && temp_data1 != NULL) {
		if (temp_data1->freq == temp_data2->freq) {
			Big_data1[i] = temp_data1;
			Big_data2[i] = temp_data2;
			printf("%s , %s => ���� Ƚ�� %d������ �����ϴ�.\n", Big_data1[i]->dataPtr, Big_data2[i]->dataPtr, Big_data1[i]->freq);
			i++;
			
		}

		//������ ���� ū ���� ����
		temp_data1 = DeleteHeap(data1);
		temp_data2 = DeleteHeap(data2);
		//

		i2++;
	}
	printf("------------------------------------------------------------\n");
	printf("�󵵼� ���� 10�� �� %d �� ��ġ => ���絵 :%d �ۼ�Ʈ \n", i, i * 10);
}


void main() {
	//ù��° �ؽ�Ʈ ���� �콬�� ���� ->���� ����
	printf("file1 ------------------------------------\n");
	HTABLE* hash = _CreateHash('S',50);


	FILE* ex1;
	errno_t err = fopen_s(&ex1, "ex1.txt", "r");
	

	KeywordToHash(ex1,hash);
	_PrintHash(hash);
	printf("\n���� %d\n", hash->NodeNumber);

	HEAP* heap = CreateHeap(hash->NodeNumber); // �ؽ��� ��� ����ŭ ���� ũ�⸦ ����, ���� �޸� ȿ��������
	InsertHashToHeap(hash, heap);
	PrintHeap(heap);

	

	//�ι�° �ؽ�Ʈ ���� �콬�� ���� ->���� ����
	//\\

	printf("\n\n");
	printf("file2 ------------------------------------\n");

	HTABLE* hash2 = _CreateHash('S', 50);
	FILE* ex2;
	errno_t err2 = fopen_s(&ex2, "ex2.txt", "r");

	KeywordToHash(ex2, hash2);
	_PrintHash(hash2);
	printf("\n���� %d\n", hash2->NodeNumber);

	HEAP* heap2 = CreateHeap(hash2->NodeNumber); // �ؽ��� ��� ����ŭ ���� ũ�⸦ ����, ���� �޸� ȿ��������
	InsertHashToHeap(hash2, heap2);
	PrintHeap(heap2);

	printf("���絵 �˻縦 �ǽ��Ͻðڽ��ϱ�? (y/n) ");
	if (getchar() == 'y') {
		getchar();

		Similarity(heap, heap2);

	}
	else {
		getchar();

		
	}
	//�ؽ� 2�� free
	FreeHash(hash);
	FreeHeap(heap);
	FreeHash(hash2);
	FreeHeap(heap2);
	printf("free �Ϸ�, ���α׷��� �����մϴ�.\n");
	getchar();
}
