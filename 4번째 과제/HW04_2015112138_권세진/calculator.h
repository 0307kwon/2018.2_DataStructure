#pragma once
#include "Queue.h"
#include "Stack.h"


#define InputSize 40 // �����Է¹��� ���ڿ��� ũ��

int PushOrOut(Head* stack, char input);
int GetPostfix(QueueHead* head, char data[InputSize]);
double Calculate(QueueHead* head);