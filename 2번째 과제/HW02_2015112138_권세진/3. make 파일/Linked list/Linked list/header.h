typedef struct node {
	char* name[20];
	unsigned long sid;
	struct node* link;
}NODE;

NODE* head = NULL; // 나중에 헤더에 넣어주세요
