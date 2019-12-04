#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Stack.h"
#include "Queue.h"
#include "calculator.h"

void main() {
	QueueHead* postfix = CreateQueue();
	char input[InputSize];

	printf("2015112138 권세진 / 계산기 ------------------------------\n");
	char aa;
	printf("계산기를 실행하시겠습니까?(y/n)");
	while (aa = getchar()) {
		getchar();
		if (aa == 'y') {
			printf("수식을 입력하세요 ( '='기호 제외, 소수점미포함, 각 피연산자의 최대 길이는 9자리까지 지원 )\n");
			gets_s(input, InputSize);
			GetPostfix(postfix, input);
			printf("= "); PrintQueue(postfix); printf(" (postfix)\n");
			printf("= %.1f\n", Calculate(postfix));
		}
		else {
			break;
		}
		printf("계속하시겠습니까?(y/n)");
	}
	DeleteQueue(postfix);
	printf("프로그램이 종료되었습니다.");
	getchar();
}