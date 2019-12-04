#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Queue.h"

//Queue
QueueHead* CreateQueue() {
	QueueHead* head = (QueueHead*)malloc(sizeof(QueueHead));
	if (head == NULL) {
		return NULL;
	}
	head->count = 0;
	head->head = NULL;
	head->rear = NULL;
	return head;
}

int Enqueue(QueueHead* head, char data[DataSize]) {
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode == NULL) {
		return NULL;
	}
	strcpy_s(newNode->data, DataSize, data, DataSize);
	newNode->next = NULL;

	if (head->head == NULL) {
		head->head = newNode;
		head->rear = head->head;
	}
	else {
		head->rear->next = newNode;
		head->rear = newNode;
	}

	head->count++;
	return 1;
}

int Dequeue(QueueHead* head, char data[DataSize]) {
	QueueNode* temp;

	if (head->count >= 1) {
		if (head->count == 1) {
			strcpy_s(data, DataSize, head->head->data, DataSize);
			free(head->head);
			head->head = NULL;
			head->rear = NULL;
		}
		else {
			strcpy_s(data, DataSize, head->head->data, DataSize);
			temp = head->head;
			head->head = head->head->next;
			free(temp);
		}
		head->count--;
		return 1;
	}
	else {
		return 0;//���̻� ť�� �ƹ��͵� �����ϴ�.
	}
}

void PrintQueue(QueueHead* head) {
	QueueNode* temp = head->head;
	if (temp != NULL) { // �׿��ִ� ������ �����ϴ��� Ȯ��
		for (int i = 0; i < head->count; i++) {
			printf("%s", temp->data);
			temp = temp->next;
		}
	}
}

void ClearQueue(QueueHead* head) { // queue�� �ʱ�ȭ �ϴ� �Լ� (�ȿ��ִ� ��� queue�� ����
	QueueNode* temp1 = head->head;
	QueueNode* temp2 = NULL;
	for (int i = 0; i < head->count; i++) {
		temp2 = temp1->next;
		free(temp1);
		temp1 = temp2;

	}
	temp1 = NULL;
	head->count = 0;
}

void DeleteQueue(QueueHead* head) { // queue�� �ƿ�����
	QueueNode* temp1 = head->head;
	QueueNode* temp2 = NULL;
	for (int i = 0; i < head->count; i++) {
		temp2 = temp1->next;
		free(temp1);
		temp1 = temp2;

	}
	free(head);
}


//
