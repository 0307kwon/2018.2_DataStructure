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
		return 0;//더이상 큐에 아무것도 없습니다.
	}
}

void PrintQueue(QueueHead* head) {
	QueueNode* temp = head->head;
	if (temp != NULL) { // 쌓여있는 스텍이 존재하는지 확인
		for (int i = 0; i < head->count; i++) {
			printf("%s", temp->data);
			temp = temp->next;
		}
	}
}

void ClearQueue(QueueHead* head) { // queue를 초기화 하는 함수 (안에있는 모든 queue를 지움
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

void DeleteQueue(QueueHead* head) { // queue를 아예삭제
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
