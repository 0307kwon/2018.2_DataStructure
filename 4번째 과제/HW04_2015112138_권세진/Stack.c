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
		return 0; // 힙에 자리가 없으면 0을 반환
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
	if (temp != NULL) { // 쌓여있는 스텍이 존재하는지 확인
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
		//스텍이 더이상 없습니다.
		data_return = NULL; // 문자열도 NULL반환
		return 0;
	}
}

void ClearStack(Head* stack) {// stack를 초기화 하는 함수 (안에있는 모든 stack을 지움
	StackNode* temp1 = stack->top;
	StackNode* temp2 = NULL;
	for (int i = 0; i < stack->count; i++) {
		temp2 = temp1->nextNode;
		free(temp1);
		temp1 = temp2;

	}
	stack->count = 0;
}

void DeleteStack(Head* stack) {// stack을 아예 삭제
	StackNode* temp1 = stack->top;
	StackNode* temp2 = NULL;
	for (int i = 0; i < stack->count; i++) {
		temp2 = temp1->nextNode;
		free(temp1);
		temp1 = temp2;

	}
	free(stack);
}