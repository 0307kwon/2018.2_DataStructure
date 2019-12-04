#pragma once
#include "Queue.h"
#include "Stack.h"


#define InputSize 40 // 수식입력받을 문자열의 크기

int PushOrOut(Head* stack, char input);
int GetPostfix(QueueHead* head, char data[InputSize]);
double Calculate(QueueHead* head);