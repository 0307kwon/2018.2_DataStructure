#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Stack.h"
#include "Queue.h"
#include "calculator.h"

void main() {
	QueueHead* postfix = CreateQueue();
	char input[InputSize];

	printf("2015112138 �Ǽ��� / ���� ------------------------------\n");
	char aa;
	printf("���⸦ �����Ͻðڽ��ϱ�?(y/n)");
	while (aa = getchar()) {
		getchar();
		if (aa == 'y') {
			printf("������ �Է��ϼ��� ( '='��ȣ ����, �Ҽ���������, �� �ǿ������� �ִ� ���̴� 9�ڸ����� ���� )\n");
			gets_s(input, InputSize);
			GetPostfix(postfix, input);
			printf("= "); PrintQueue(postfix); printf(" (postfix)\n");
			printf("= %.1f\n", Calculate(postfix));
		}
		else {
			break;
		}
		printf("����Ͻðڽ��ϱ�?(y/n)");
	}
	DeleteQueue(postfix);
	printf("���α׷��� ����Ǿ����ϴ�.");
	getchar();
}