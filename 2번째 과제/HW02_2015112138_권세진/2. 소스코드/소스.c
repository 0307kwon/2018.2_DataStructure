#include <stdio.h>
#include<malloc.h>
#include<string.h>
#include "header.h"



NODE* CreateNode(char* name[20], unsigned long sid) {
	NODE* nodePtr = (NODE*)malloc(sizeof(NODE));
	if (nodePtr == NULL) {
		printf("���� ������ �����մϴ�");
	}
	strcpy_s(nodePtr->name, 20, name, 20);
	nodePtr->sid = sid;
	nodePtr->link = NULL;
	printf("%s %d \n", name, sid);
	return nodePtr;
}

void Clear(NODE* head) { // Linked list�� �Ҵ�� ���� ��� free�մϴ�.
	NODE* temp = head;
	NODE* temp2 = NULL;
	int i = 1;
	while (1) {
		temp2 = temp->link; // ��带 free�ϱ����� ���� link�� �ּҸ� �ӽ������մϴ�.
		free(temp);

		if (temp2 != NULL) {
			temp = temp2;
			i++;
		}
		else {
			break;
		}
	}
	printf("Linked list free �Ϸ�\n", i);
}



NODE* FindNode_S(char* s[20]) { // ���ڿ� ���� ���� ���� ��带 ã���ϴ�. (���ڰ� �����϶�)
	NODE* node = head;
	while (node != NULL) {
		if (!strcmp(node->name, s)) { // ���� ���� ã����
			return node;
		}
		else {
			node = node->link;
		}
	}	
	return NULL; // ��ũ�� ���������� ��ã���� NULL�� ����

}

NODE* FindNode_N(unsigned long sid) {
	NODE* node = head;
	while (node != NULL) {
		if (node->sid == sid) {
			return node;
		}
		else {
			node = node->link;
		}
	}
	return NULL; // ��ũ�� ���������� ��ã���� NULL�� ����
}

void ChangeTo() { // input.txt�� �о �й� ->�̸� , �̸� -> �й� ���� �������ݴϴ�.
	FILE* file = NULL;
	errno_t err = fopen_s(&file, "input.txt", "rt");
	NODE* temp = NULL;
	char* string[20];
	while (!feof(file)) {
		fscanf_s(file, "%s", string, 20);
		if (IsString(string)) { // �̸��̸� �й����� �ٲ��ּ���
			temp = FindNode_S(string);
			if (temp != NULL) {
				printf("%d\n", temp->sid);
			}
			else {
				printf("���� �̸��Դϴ�.\n");
			}
		}
		else {//�й��̸� �̸����� �ٲ��ּ���
			temp = FindNode_N(atol(string));
			if (temp != NULL) {
				printf("%s\n", temp->name);
			}
			else {
				printf("���� �й��Դϴ�.\n");
			}
		}
	}
}


int IsString(char* s[20]) { // ���ڸ� 1, ���ڸ� 0 ��� 
	if ((char)s[0] >= '0' && (char)s[0] <= '9') {
		return 0;
	}
	else {
		return 1;
	}
}




void main() {
	char ch;
	int i; // �����̳� �ӽ÷� ���� ī������ �ʿ��Ҷ� ����մϴ�.
	int* x = (int*)malloc(sizeof(int));

	NODE* node = NULL; // ������ �� ����� �ּҸ� �����Ѵ�.
	NODE* temp = NULL; // Linked list �ӿ��� ��ġ �̵� ������ �Ѵ�.


	FILE* file = NULL;
	errno_t err = fopen_s(&file, "student.txt", "rt"); // student.txt ������ �н��ϴ�.

	i = 1; // ����Ʈ �ʱ�ȭ�� �ӽ÷� ���
		   //���Ͽ��� ���� �ӽ÷� ������ ������ ���մϴ�.
	char* temp_name[20];
	unsigned long temp_sid;
	//
	while (!feof(file)) {

		fscanf_s(file, "%d %s", &temp_sid, temp_name, 20);
		//linked list �ʱ�ȭ
		if (i == 1) {
			head = CreateNode(temp_name, temp_sid);
			node = head;//����� �ʱ� ���� head��ġ �ּҷ� ���Ѵ�.(��ũ�� ����)
		}
		else {
			temp = node; // ���� �����ġ �ӽ�����
			node = CreateNode(temp_name, temp_sid);
			//��ũ �����ϱ�
			temp->link = node; // ���� ����� ��ũ�� ���ο� ��� �ּҰ����� ����Ѵ�.
		}
		i++;
	}
	printf("input.txt�� ���� �Է°��� ��ȯ�Ͻðڽ��ϱ�?(y/n)");

	// input.txt �Է� �޾Ƽ� ������� Ŀ�ǵ� ���ο� ���
	scanf_s("%c", &ch); getchar();
	if (ch == 'y') {
		ChangeTo();
	}
	//

	Clear(head); // ��� Linked list�� �ʱ�ȭ ��ŵ�ϴ�.
	scanf_s("%c", &ch); getchar();
}

