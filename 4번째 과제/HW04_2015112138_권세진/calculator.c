#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "Queue.h"
#include "Stack.h"
#include "calculator.h"



//우선순위를 판별하는 함수
int PushOrOut(Head* stack, char input) { // 1이면 push 0이면 out
	int isp = 0;
	char isp_c;
	if (stack->top != NULL) {
		isp_c = stack->top->data[0];
	}
	else {
		return 1;
	}
	switch (isp_c) {
	case '+':
		isp = 12;
		break;
	case '-':
		isp = 12;
		break;
	case '*':
		isp = 13;
		break;
	case '/':
		isp = 13;
		break;
	case '(':
		isp = 0;
		break;
	case ')':
		isp = 19;
		break;
	}

	int icp = 0;

	switch (input) {
	case '+':
		icp = 12;
		break;
	case '-':
		icp = 12;
		break;
	case '*':
		icp = 13;
		break;
	case '/':
		icp = 13;
		break;
	case '(':
		icp = 20;
		break;
	case ')':
		icp = 19;
		break;
	}

	if (icp <= isp) {
		return 0;//out
	}
	else {
		return 1;//push
	}

}


//postfix로 만들어주는 함수, 만들어서Queue에 넣습니다.

int GetPostfix(QueueHead* head, char data[InputSize]) {
	ClearQueue(head); // 큐 초기화

	Head* symbol = CreateStack();//기호를 담을 스텍생성

	int i = 0;
	int j = 0;
	char number[DataSize] = { "" };
	char temp[DataSize] = { "" };
	while (data[i] != NULL) {
		if (data[i] >= '0' && data[i] <= '9') { //숫자면
			number[j] = data[i];
			j++;
		}
		else { //기호면
			if (*number != NULL) { // 3*(1/2+1) 같이 *( 사이에서 *다음에 바로 (라는 기호를 만나니까 number에 아무것도 들어있지않아도 큐에 out하기때문에 이 if문을 써줘야함
				Enqueue(head, number);//지금까지 저장했던 숫자들을 큐에 out
				for (int ii = 0; ii < DataSize; ii++) {
					number[ii] = NULL;//임시저장숫자배열 초기화
				}
				j = 0;
			}

			if (data[i] == ')') { // '('를 만날때까지 전부 out
				*temp = NULL;
				PopStack(symbol, temp);
				while (temp[0] != '(' && temp != NULL) {
					Enqueue(head, temp);
					PopStack(symbol, temp);
				}
			}else {// )가 들어오지 않은 일반적인 경우

				//icp<=isp 가 아닐때까지 스텍에 있는 기호 out합니다.
				while(PushOrOut(symbol, data[i]) == 0) {
					//스텍에서 하나빼서 out
					*temp = NULL;
					PopStack(symbol, temp);
					Enqueue(head, temp);

				}
				//icp>isp면
				//방금 내가 받은 연산기호 push
				*temp = NULL;
				temp[0] = data[i];
				PushStack(symbol, temp);
			}
		}

		i++;
	}
	//수식입력이 끝나면 마지막에 입력된 숫자를 출력한 후, 스텍에 저장되어있는 나머지 연산기호 모두 out

	if (*number != NULL) { // 3*(1/2+1) 같이 *( 사이에서 *다음에 바로 (라는 기호를 만나니까 number에 아무것도 들어있지않아도 큐에 out하기때문에 이 if문을 써줘야함
		Enqueue(head, number);//지금까지 저장했던 숫자들을 큐에 out
	}
	while (symbol->count >= 1) {
		*temp = NULL;
		PopStack(symbol, temp);
		Enqueue(head, temp);
	}

	DeleteStack(symbol);
}

//postfix를 받아서 계산합니다.
double Calculate(QueueHead* head) { // postfix 들어있는 큐
	//피연산자 2개 저장
	double a;
	double b;
	char data[DataSize] = { "" };

	double arrayStack[DataSize];
	int top = -1; // 임시로 더블유형의 Array 스텍을 만듦

	while (head->count != 0) {
		Dequeue(head, data);
		if (data[0] >= '0' && data[0] <= '9') { // 숫자면
			arrayStack[++top] = atol(data);
		}
		else {
			
			b = arrayStack[top--];
			a = arrayStack[top--];

			switch (data[0]) {
			case '+':
				a = a + b;
				break;
			case '-':
				a = a - b;
				break;
			case '*':
				a = a * b;
				break;
			case '/':
				a = a / b;
				break;
			}
			
			arrayStack[++top] = a;
		}
	}
	return a;
}


