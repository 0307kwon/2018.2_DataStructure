#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Stack.h"


Head* CreateStack() {
	Head* head = (Head *)malloc(sizeof(Head));
	if (head == NULL) {
		return NULL;
	}
	head->count = 0;
	head->top = NULL;
	return head;
}

int PushStack(Head* stack, char value[DataSize]) {
	StackNode* newStack = (StackNode*)malloc(sizeof(StackNode));
	if (newStack == NULL) {
		return 0; // ���� �ڸ��� ������ 0�� ��ȯ
	}
	strcpy_s(newStack->data, DataSize, value, DataSize);
	stack->count++;
	if (stack->top == NULL) {
		stack->top = newStack;
		newStack->nextNode = NULL;
	}
	else {
		StackNode* temp = stack->top;
		stack->top = newStack;
		newStack->nextNode = temp;
	}
	return 1;
}



void PrintStack(Head* stack) {
	StackNode* temp = stack->top;
	if (temp != NULL) { // �׿��ִ� ������ �����ϴ��� Ȯ��
		for (int i = 0; i < stack->count; i++) {
			printf("%s->", temp->data);
			temp = temp->nextNode;
		}
	}
	printf("\n");
}

int PopStack(Head* stack,char data_return[DataSize]) {
	if (stack->count >= 1) {
		StackNode* temp = stack->top;
		stack->top = stack->top->nextNode;
		strcpy_s(data_return, DataSize, temp->data, DataSize);
		free(temp);
		stack->count--;
		return 1;
	}
	else {
		//������ ���̻� �����ϴ�.
		data_return = NULL; // ���ڿ��� NULL��ȯ
		return 0;
	}
}

void ClearStack(Head* stack) {// stack�� �ʱ�ȭ �ϴ� �Լ� (�ȿ��ִ� ��� stack�� ����
	StackNode* temp1 = stack->top;
	StackNode* temp2 = NULL;
	for (int i = 0; i < stack->count; i++) {
		temp2 = temp1->nextNode;
		free(temp1);
		temp1 = temp2;

	}
	stack->count = 0;
}

void DeleteStack(Head* stack) {// stack�� �ƿ� ����
	StackNode* temp1 = stack->top;
	StackNode* temp2 = NULL;
	for (int i = 0; i < stack->count; i++) {
		temp2 = temp1->nextNode;
		free(temp1);
		temp1 = temp2;

	}
	free(stack);
}