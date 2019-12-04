#pragma once
#include <stdio.h>
#include <time.h>
typedef struct ManNode {
	char name[20];
	int bullet;
	struct ManNode* next;
}ManNode;


typedef struct Head {
	int count;
	ManNode* head;
}Head;


int Random(int a) {// 1���� a����
	return rand() % a + 1;
}

Head* CreateHead() { // ��带 ����ϴ�.
	Head* head = (Head*)malloc(sizeof(Head));
	if (head == NULL) {
		return NULL;
	}
	head->count = 0;
	head->head = NULL;
	return head;
}

int InsertNode(Head* head, int distance, char name[20],int bullet) { // distance�� 0�̸� ������ ��忡 �߰���,distnace�� n�̸� ��ġ n�ڿ� �߰���,0��ȯ ����,1��ȯ ����
	ManNode* Fnode;
	ManNode* Nnode;

	//���ο� ��� �ʱ�ȭ
	ManNode* newNode = (ManNode*)malloc(sizeof(ManNode));
	if (newNode == NULL) {
		return 0;
	}
	strcpy_s(newNode->name,20,name,20);
	newNode->bullet = bullet;
	newNode->next = NULL;


	if (distance == 0 || distance == head->count) {
		//������ ��忡 �߰��Ҷ�
		if (head->head == NULL) {
			head->head = newNode;
			newNode->next = newNode; // ��������� ù��°�� ����
		}
		else {
			Fnode = head->head;
			for (int i = 0; i < head->count - 1; i++) {
				Fnode = Fnode->next;
			}// ������ ��带 ����Ŵ
			Nnode = Fnode->next;//������ ����� ������� ����Ŵ
			Fnode->next = newNode;
			newNode->next = Nnode; // ��������� ù��°�� ���� 
		}
	}
	else {
		//���̿� �߰��Ҷ�
		Fnode = head->head;
		for (int i = 0; i < distance - 1; i++) {
			Fnode = Fnode->next;
		}
		Nnode = Fnode->next;
		Fnode->next = newNode;
		newNode->next = Nnode;
	}
	head->count++;
	return 1;
}

void PrintALL(Head* head) {
	ManNode* temp = head->head;
	if (head->head != NULL) {
		for (int i = 0; i < 10; i++) {
			if (i == head->count - 1) {
				printf("%d��° ���ӿ��� %d��° �Ѿ��� �¾� %s(��)�� ����߽��ϴ�. \n----- ���ӳ� -----\n", i+1, temp->bullet, temp->name);
				temp = temp->next;
			}
			else {
				printf("%d��° ���ӿ��� %d��° �Ѿ��� �¾� %s(��)�� ����߽��ϴ�.\n", i+1, temp->bullet, temp->name);
				temp = temp->next;
			}
		}
	}
}

int DeleteMan(Head* head, int distance, char* returnS[20]) { // int�� ������ 1�̻��̿����մϴ�. ���� ���� 0,returnS�� ������ ��� �̸����Ϲ��� ��Ʈ��
	ManNode* Fnode = NULL;
	ManNode* Target = NULL;
	ManNode* Nnode = NULL;
	if (distance < 1) {
		return 0;
	}

	// ���� ù��° ��� ����� ���, ������ ���.

	//ù��°
	if (head->count != 1) {
		if (distance == 1 || distance % (head->count) == 1) {// ��üũ�� 8�ε� 9�ɸ��� 1�ɸ��°Ŷ� �Ȱ���

			Fnode = head->head;
			for (int i = 0; i < head->count - 1; i++) {
				Fnode = Fnode->next;
			}//������ ��� ����Ŵ
			Target = head->head;
			Nnode = Target->next;

			strcpy_s(returnS, 20, Target->name, 20);

			//�����ϰ� �ٽÿ���
			free(Target);
			head->head = Nnode;
			Fnode->next = Nnode;


		}
		else {
			Fnode = head->head;
			for (int i = 0; i < distance - 2; i++) {
				Fnode = Fnode->next;
			}// �Ÿ����� 1 �տ� �ִ� ��� �˻�
			Target = Fnode->next;
			Nnode = Target->next;

			strcpy_s(returnS, 20, Target->name, 20);

			free(Target);
			Fnode->next = Nnode;



		}
	}
	else {
		strcpy_s(returnS, 20, head->head->name, 20);
		head->head = NULL;
	}
	head->count--;
}

