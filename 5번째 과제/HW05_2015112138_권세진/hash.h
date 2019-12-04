#define StringSize 20
#define LineSize 200
#include <stdio.h>

typedef struct Hnode {
	void* dataPtr;
	int freq; //�ҽ��ڵ忡�� ������Ƚ���� ���մϴ�.
	struct Hnode* next;// collision �������Դϴ�.
}HNODE;

typedef struct {
	HNODE* hTable;
	int (*ReturnHAddress)(void* data, int maxSize); // Hash�� �ּҸ� ��ȯ���ִ� �Լ� (����1 = ������, ����2 = ������ Ÿ��)
	int(*Compare)(void* data1, void* data2); // ������ �� �Լ�
	char dataType;
	int maxSize;
	int NodeNumber; // �ȿ� ����ִ� ����� �� ,heap���鶧 ���ϴ�.
}HTABLE;

int _AddressString(void* data,int max);//hash�� �ּҸ� ��ȯ���ִ� �Լ� (String ����) (����1 :������, ����2 : �콬 MAXsize)
int _CompareString(void* data1, void* data2); // ������ �� �Լ�
HTABLE* _CreateHash(char dataType, int maxSize); //�ؽ��� ����� �Լ�
int _InsertHash(HTABLE* hash, void* dataPtr); // �ؽ��� ���� �ִ� �Լ�
void* _MakeDataPtr(void* dataPtr, char dataType);//������ ����ϰ� �ּҰ� ��ȯ(�����Ͱ� ��������ʵ��� �ϴ°�)
void _PrintHash(HTABLE* hash); // �ؽ� ���� ���� ��� printf �ϴ� �Լ�
int KeywordToHash(FILE* ex1, HTABLE* hash); // �о�� ���Ͽ��� ��� Ű���带 �ؽ��� �����ϴ� �Լ�
void FreeHash(HTABLE* hash); // �ؽ��� free ��Ű�� �Լ�