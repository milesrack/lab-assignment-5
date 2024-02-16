#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int listLength = 0;
	node* cur = head;
	while (cur != NULL){
		cur = cur->next;
		listLength++;
	}
	return listLength;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	int index = 0;
	node* cur = head;
	char *string = (char *) malloc(sizeof(char) * (length(head) + 1));
	
	if (string == NULL){
		printf("malloc() failed!");
		exit(EXIT_FAILURE);
	}

	while (cur != NULL){
		string[index++] = cur->letter;
		cur = cur->next;
	}
	string[index] = '\0';
	return string;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	if (*pHead == NULL){
		*pHead = (node *) malloc(sizeof(node));
		(*pHead)->letter = c;
		(*pHead)->next = NULL;
	}
	else{
		node *cur = *pHead;
		while (cur->next != NULL){
			cur = cur->next;
		}
		cur->next = (node *) malloc(sizeof(node));
		cur->next->letter = c;
		cur->next->next = NULL;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node *cur = *pHead;
	node *last = NULL;
	while (cur != NULL){
		last = cur;
		cur = cur->next;
		free(last);
	}
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}