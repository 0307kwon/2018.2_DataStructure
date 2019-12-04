#pragma once
#define DataSize 10 // 큐의 데이터 사이즈

//Queue
typedef struct QueueNode {
	char data[DataSize];
	struct QueueNode* next;
}QueueNode;

typedef struct QueueHead {
	int count;
	QueueNode* rear;
	QueueNode* head;
}QueueHead;

QueueHead* CreateQueue();

int Enqueue(QueueHead* head, char data[DataSize]);

int Dequeue(QueueHead* head, char data[DataSize]);

void PrintQueue(QueueHead* head);

void ClearQueue(QueueHead* head);

void DeleteQueue(QueueHead* head);

//
