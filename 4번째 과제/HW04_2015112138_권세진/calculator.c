#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "Queue.h"
#include "Stack.h"
#include "calculator.h"



//�켱������ �Ǻ��ϴ� �Լ�
int PushOrOut(Head* stack, char input) { // 1�̸� push 0�̸� out
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


//postfix�� ������ִ� �Լ�, ����Queue�� �ֽ��ϴ�.

int GetPostfix(QueueHead* head, char data[InputSize]) {
	ClearQueue(head); // ť �ʱ�ȭ

	Head* symbol = CreateStack();//��ȣ�� ���� ���ػ���

	int i = 0;
	int j = 0;
	char number[DataSize] = { "" };
	char temp[DataSize] = { "" };
	while (data[i] != NULL) {
		if (data[i] >= '0' && data[i] <= '9') { //���ڸ�
			number[j] = data[i];
			j++;
		}
		else { //��ȣ��
			if (*number != NULL) { // 3*(1/2+1) ���� *( ���̿��� *������ �ٷ� (��� ��ȣ�� �����ϱ� number�� �ƹ��͵� ��������ʾƵ� ť�� out�ϱ⶧���� �� if���� �������
				Enqueue(head, number);//���ݱ��� �����ߴ� ���ڵ��� ť�� out
				for (int ii = 0; ii < DataSize; ii++) {
					number[ii] = NULL;//�ӽ�������ڹ迭 �ʱ�ȭ
				}
				j = 0;
			}

			if (data[i] == ')') { // '('�� ���������� ���� out
				*temp = NULL;
				PopStack(symbol, temp);
				while (temp[0] != '(' && temp != NULL) {
					Enqueue(head, temp);
					PopStack(symbol, temp);
				}
			}else {// )�� ������ ���� �Ϲ����� ���

				//icp<=isp �� �ƴҶ����� ���ؿ� �ִ� ��ȣ out�մϴ�.
				while(PushOrOut(symbol, data[i]) == 0) {
					//���ؿ��� �ϳ����� out
					*temp = NULL;
					PopStack(symbol, temp);
					Enqueue(head, temp);

				}
				//icp>isp��
				//��� ���� ���� �����ȣ push
				*temp = NULL;
				temp[0] = data[i];
				PushStack(symbol, temp);
			}
		}

		i++;
	}
	//�����Է��� ������ �������� �Էµ� ���ڸ� ����� ��, ���ؿ� ����Ǿ��ִ� ������ �����ȣ ��� out

	if (*number != NULL) { // 3*(1/2+1) ���� *( ���̿��� *������ �ٷ� (��� ��ȣ�� �����ϱ� number�� �ƹ��͵� ��������ʾƵ� ť�� out�ϱ⶧���� �� if���� �������
		Enqueue(head, number);//���ݱ��� �����ߴ� ���ڵ��� ť�� out
	}
	while (symbol->count >= 1) {
		*temp = NULL;
		PopStack(symbol, temp);
		Enqueue(head, temp);
	}

	DeleteStack(symbol);
}

//postfix�� �޾Ƽ� ����մϴ�.
double Calculate(QueueHead* head) { // postfix ����ִ� ť
	//�ǿ����� 2�� ����
	double a;
	double b;
	char data[DataSize] = { "" };

	double arrayStack[DataSize];
	int top = -1; // �ӽ÷� ���������� Array ������ ����

	while (head->count != 0) {
		Dequeue(head, data);
		if (data[0] >= '0' && data[0] <= '9') { // ���ڸ�
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


