typedef struct node {
	char* name[20];
	unsigned long sid;
	struct node* link;
}NODE;

NODE* head = NULL; // ���߿� ����� �־��ּ���
