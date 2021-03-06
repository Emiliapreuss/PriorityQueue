#include <stdio.h>
#include<string.h>

struct element {
    char value[50] ;
	struct element* next;
	struct element* previous;
	int priority;
};

struct queue {
	struct element* first;
	struct element* last;
};


void push(struct element* e, struct queue* q)
{
	e->priority = 0;
	e->next = NULL;
	//gdy kolejka jest pusta:
	if (q->first == NULL)
	{
		e->previous = NULL;
		q->first = q->last = e;

	}
	else //kolejka mia³a ju¿ inne wartoœci 
	{
		e->previous = q->last;
		q->last->next = e;
		q->last = e;
	}
}


char* pop(struct queue* q)
{
	if (q->first )
	{
		char e[50];
		strcpy_s( e, sizeof(e),q->last->value);
		struct element* tmp = q->last; 
		q->last = tmp->previous;
		if (q->last)
		{
			q->last->next = NULL;
					
		}
		else
		{
			q->first = NULL;
		}
		free(tmp);
		return e;
	}
	else return "Queue is empty";
}

void insert(struct element* newElement, int prior, struct queue* q)
{
	
	newElement->priority = prior;
	struct element* tmp = q->first;
	if (tmp == NULL) // pusta kolejka
	{

		newElement->previous = NULL;
		newElement->next = NULL;
		q->first = q->last = newElement;

	}
	else if (prior <= tmp->priority) // priorytet mniejszy od wierzcholka
	{
		newElement->previous = NULL;
		newElement->next = q->first;
		q->first = newElement;
	}
	else
	{
			while (tmp != NULL)
				if (tmp->priority == prior)
				{
					struct element* previousOne = tmp->previous;
					previousOne->next = newElement;
					tmp->previous = newElement;
					newElement->next = tmp;
					newElement->previous = previousOne;
					break;
				}
				else if (tmp->next == NULL)	
				{
							q->last->next = newElement;
							newElement->previous = q->last;
							q->last = newElement;
							q->last->next = NULL;
							break;
				}
				else
				{
					tmp = tmp->next;	
				}
	}

}

void delete_by_priority(int prior, struct queue* q)
{
	if (q->first!= NULL)
	{
		struct element* tmp = q->first; //iterator po kolejce
		
			while (tmp != NULL)
			{
				if (tmp->priority == prior) //pierwszy element o zadanym priorytecie
				{
					if (prior == q->last->priority)
					{   
						q->last = tmp->previous;
						if (q->last == NULL)//kolejka ma wszystkie el tego samego priorytetu
						{
							q->first == NULL; // kolejka bedzie pusta
						}
						else
						{
							q->last->next = NULL;
						}
						while (tmp!= NULL) //wszystkie elementy o zadanym priorytecie
						{
							struct element* todelete = tmp;
							tmp = tmp->next;
							free(todelete);
						}
						
					}
					else if (prior == q->first->priority)
					{
						while (tmp->priority == prior) //wszystkie elementy o zadanym priorytecie
						{
							struct element* todelete = tmp;
							tmp = tmp->next;
							free(todelete);
						}
						tmp->previous = NULL;
						q->first = tmp;
					}
					else
					{
						while (tmp->priority == prior) //wszystkie elementy o zadanym priorytecie
						{
							struct element* todelete = tmp;
							tmp->previous->next = tmp->next;
							tmp->next->previous = tmp->previous;
							tmp = tmp->next;
							free(todelete);
						}
					}
					
					break;
				}
				tmp = tmp->next;
			}
			printf("\n Elements with priority %i have been deleted\n", prior);
	}
}

void print(struct queue* q)
{
	struct element* tmp = q->first; //pierwszy element - first kolejki

	if (tmp == NULL) {
		printf("\nQueue is empty\n");
	}
	else {
		printf("\nQueue: \n");
		while (tmp != NULL) {
			printf("( %i ) , %s \n", tmp->priority, tmp->value);
			tmp = tmp->next;
		}
	}

}

struct queue merge(struct queue* q, struct queue* q1)
{
	struct queue w;
	w.first = NULL;
	w.last = NULL;
	struct element* it = q->first, * it1 = q1->first; //iteratory po kolejkach 
	struct element* el = NULL;
	int pr;
	
	while (it1 != NULL ) 
	{
		struct element* e = (struct element*) malloc(sizeof(struct element));
		strcpy_s(e->value, sizeof(e->value),it1->value);
		insert(e, it1->priority, &w);
		it1 = it1->next;
	}
	while (it != NULL)
	{
		struct element* e = (struct element*) malloc(sizeof(struct element));
		strcpy_s(e->value, sizeof(e->value), it->value);
		insert(e, it->priority, &w);
		it = it->next;
	}
	return w;
}
void setfree(struct queue* que)
{
	struct element* todelete = que->first;
	if (que->first)
	{
		que->first = que->first->next;
		free(todelete);
	}
}

int main()
{
	struct queue q;
	q.first = NULL;
	q.last = NULL;
	struct element* e1 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e1->value, sizeof(e1->value), "Jan Nowak");
	struct element* e2 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e2->value, sizeof(e2->value) , "Jan K");
	struct element* e3 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e3->value , sizeof(e3->value), "Julian K");
	push(e1, &q);
	push(e2, &q);
	push(e3, &q);
	print(&q);

	char write[50] ;
	strcpy_s(write, sizeof(write), pop(&q));
	printf("\n%s has been deleted\n", write);
	print(&q);
	
	struct element* e4 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e4->value, sizeof(e4->value), "Kuba Nowak");
	insert(e4, 1, &q);
	print(&q);

	delete_by_priority(0, &q);
	print(&q);

	struct element* e5 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e5->value, sizeof(e5->value),"Sebastian A");
	struct element* e6 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e6->value, sizeof(e6->value),  "Klaudia K");


	struct queue q1;
	q1.first = NULL;
	q1.last = NULL;
	insert(e5, 1, &q1);
	insert(e6, 2,&q1);
	print(&q1);
	delete_by_priority(1, &q1);
	print(&q1);

	strcpy_s(write, sizeof(write), pop(&q1));
	printf("\n %s has been deleted\n", write);
	print(&q1);
	struct element* e7 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e7->value, sizeof(e7->value), "Jola Adamczyk");
	struct element* e8 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e8->value , sizeof(e8->value), "Zyta Jowisz");
	insert(e7, 1, &q1);
	insert(e8, 0, &q1);
	printf("\n To merge:\n");
	print(&q1);
	print(&q);
	struct queue q2;
	q2 = merge(&q, &q1);
	printf("\nMerged:\n");
	print(&q2);
	setfree(&q);
	setfree(&q1);
	setfree(&q2);
	
	return 0;
}