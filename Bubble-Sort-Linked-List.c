#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <windows.h>
#pragma warning(disable:4996)
struct Item {
	int id;
	int num;
	struct Item* next;
	struct Item* prev;
};

int i = 1;  // id

struct Item* HEAD = NULL;
struct Item* tail = NULL;

int input = 0;

void replace(struct Item* curr) {
	struct Item* nextItem=curr->next;
	if (HEAD == NULL || HEAD->next == NULL) {
	// No List or just one node -- No Swap.
		printf("\033[0;31m Less than two nodes or List is empty - No Sort !! \n");
		printf("\033[0m \n");
		return;
	}
	else if(HEAD->next==tail){   // two nodes only in the list.
		if (HEAD->num > tail->num) {
			curr = HEAD;
			HEAD = tail;
			tail = curr;	
			HEAD->next = tail;
			tail->prev = HEAD;
			HEAD->prev = tail->next = NULL;
		}
	}
	else if (HEAD->next->next == tail) {   // 3 nodes.
		curr = HEAD->next;
		if (HEAD->num > curr->num) {     // HEAD and middle swap
			HEAD->next = curr->next;
			curr->next = HEAD;
			curr->prev = NULL;
			HEAD->prev = curr;
			HEAD = curr;
		}
		else if (curr->num>tail->num) {   // middle and tail swap
			tail->prev = HEAD;
			HEAD->next = tail;
			tail->next = curr;
			curr->prev = tail;
			curr->next = NULL;
			tail = curr;
		}
	}
	else {								//	4 nodes or more
		/*curr = HEAD;*/
		nextItem = curr->next;
		if (curr->num > nextItem->num) {     
			if (HEAD->num > HEAD->next->num) {
				/*curr = HEAD->next;*/
				curr->next = nextItem->next;
				nextItem->next->prev = curr;
				nextItem->next = curr;
				nextItem->prev = NULL;
				curr->prev = nextItem;
				HEAD = nextItem;
			}
			else {
				
				curr->prev->next = nextItem;
				nextItem->prev = curr->prev;
				curr->next = nextItem->next;
				nextItem->next->prev = curr;
				curr->prev = nextItem;
				nextItem->next = curr;
			}	
		}	
	}
}

void add(int num) {
	struct Item* currentItem;
	currentItem = (struct Item* )malloc(sizeof(struct Item));
	currentItem->id = i++;
	currentItem->num = num;
	currentItem->prev = NULL;
	if (HEAD == NULL)
	{
		HEAD = tail = currentItem;
		currentItem->next = NULL;
	}
	else
	{
		currentItem->next = HEAD;
		HEAD->prev = currentItem;
		HEAD = currentItem;
	}
}

void freeLinkedList()
{
	struct Item* currentItem = HEAD;
	struct Item* releaseItem = HEAD;
	while (currentItem != NULL)
	{
		releaseItem = currentItem;
		currentItem = currentItem->next;
		free(releaseItem);
	}
}

void printList() {
	struct Item* currentItem = HEAD;
	struct Item* printItem = HEAD;
	printf("********* Print List ***********\n");
	printf("\nHEAD-->");
	while (currentItem != NULL)
	{
		printItem = currentItem;
		printf("id%d(%d) -> ", printItem->id, printItem->num);
		currentItem = currentItem->next;
	}
	printf("NULL\n\n");
}


void save() {
	struct Item* currentItem = HEAD;
	FILE* f = fopen("LinkedList.bin", "w");

	while (currentItem != NULL) {
		fwrite(currentItem, sizeof(struct Item), 1, f);
		currentItem = currentItem->next;
	}
	fclose(f);
}

void Load() {
	struct Item* HEAD2 = NULL; //HEAD2
	struct Item* prevItem = NULL;
	struct Item* currentItem2;
	FILE* f = fopen("LinkedList.bin", "r");
	struct Item* readNode;
	readNode = (struct Item*)malloc(sizeof(struct Item*));
	while (fread(readNode, sizeof(struct Item), 1, f)) {
		{
			currentItem2 = malloc(sizeof(struct Item));

			if (HEAD2 == NULL)
			{
				HEAD2 = currentItem2;
			}
			else
			{
				prevItem->next = currentItem2;
			}
			currentItem2->num = readNode->num;
			currentItem2->next = NULL;
			prevItem = currentItem2;
		}
	}
}


void BubblesortList(void)
{
	struct Item* prevItem, * nextItem;
	struct Item* tempItem;
	int swapped = 1;
	while (swapped)
	{
		swapped = 0;  
		tempItem = HEAD;    
		while (tempItem->next != NULL)  
		{
			if (tempItem->num > tempItem->next->num)
			{
				prevItem = tempItem->prev;    
				nextItem = tempItem->next; 
				if (prevItem != NULL)
				{
					prevItem->next = nextItem;
				}
				else
				{
					HEAD = nextItem;
				}
				tempItem->next = nextItem->next;   
				if (nextItem ->next != NULL) 
				{
					nextItem->next->prev = tempItem;   
				}
				tempItem->prev = nextItem; 
				nextItem->next = tempItem;
				nextItem->prev = prevItem;   
				swapped = 1; 
			}
			else 
			{
				tempItem = tempItem->next;  
			}

		}
	}
}


void BuildAndSort() {
	int userResponse, i = 1;

	printf("Insert 10 numbers to add to the linked list please.\n");
	do
	{
		printf("number %d :\n", i);
		input = scanf("%d", &userResponse);
		add(userResponse);
		i++;
	} while (i <= 10);
	printf("\n\n****** The Linked List Before Sort ******\n");
	printList();
	BubblesortList();
	printf("\n\n****** The Linked List  After Sort ******\n");
	printList();
}


void RandomAndSort() {
	srand(time(NULL));
	long t1, t2;
	long timeDiff = 0;
	printf("  items  |   time (s) |    t1      |     t2    \n");
	printf("_________|____________|____________|___________\n");

	for (int i = 1;i <= 10000;i += 100) {
		for (int j = 1;j <= i;j++) {
			add(rand());
		}
		t1=time(NULL);
		BubblesortList();
		t2=time(NULL);
		timeDiff = t2 - t1;
		printf("    %-5d|%5d       |%ld  |%ld\n",i,timeDiff,t1,t2);
	}
}


int main()
{
	char op='\0';

	do
	{
		// Multichoice Main Menu of the program.
		printf("\n***** Bubble Sort System *******\n\n");
		printf("Choose an operation to do:\n");
		printf("1) Input N numbers from user build list and sort.\n");
		printf("2) Create lists from Random numbers & calculate times.\n");
		printf("E) Exit.\n");
		scanf(" %c", &op);
		switch (toupper(op)) {
		case '1':
			BuildAndSort();
			break;
		case '2':
			RandomAndSort();
			break;
		}
	}while (toupper(op) != 'E');
	
	freeLinkedList();
}