#pragma once
#define DataSize 10 // 스텍의 데이터 사이즈

typedef struct StackNode {
	char data[DataSize];
	struct StackNode* nextNode;
}StackNode;

typedef struct Head {
	int count;
	int topISP;
	struct StackNode* top;
}Head;

Head* CreateStack();
int PushStack(Head* stack, char value[DataSize]);
void PrintStack(Head* stack);
int PopStack(Head* stack, char data_return[DataSize]);
void ClearStack(Head* stack);
void DeleteStack(Head* stack);