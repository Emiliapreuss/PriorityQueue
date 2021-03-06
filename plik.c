#include <stdio.h>
#include<string.h>

struct element {
    char value[50] ;
	struct element* next;
	struct element* previous;
	int priority;
};

struct queue {
	struct element* wierzchołek;
	struct element* koniec;
};


void push(struct element* e, struct queue* q)
{
	e->priority = 0;
	e->next = NULL;
	//gdy kolejka jest pusta:
	if (q->wierzchołek == NULL)
	{
		e->previous = NULL;
		q->wierzchołek = q->koniec = e;

	}
	else //kolejka miała już inne wartości 
	{
		e->previous = q->koniec;
		q->koniec->next = e;
		q->koniec = e;
	}
}


char* pop(struct queue* q)
{
	if (q->wierzchołek )
	{
		char e[50];
		strcpy_s( e, sizeof(e),q->koniec->value);
		struct element* tmp = q->koniec; 
		q->koniec = tmp->previous;
		if (q->koniec)
		{
			q->koniec->next = NULL;
					
		}
		else
		{
			q->wierzchołek = NULL;
		}
		free(tmp);
		return e;
	}
	else return "Kolejka jest pusta";
}

void insert(struct element* newElement, int prior, struct queue* q)
{
	
	newElement->priority = prior;
	struct element* tmp = q->wierzchołek;
	if (tmp == NULL) // pusta kolejka
	{

		newElement->previous = NULL;
		newElement->next = NULL;
		q->wierzchołek = q->koniec = newElement;

	}
	else if (prior <= tmp->priority) // priorytet mniejszy od wierzcholka
	{
		newElement->previous = NULL;
		newElement->next = q->wierzchołek;
		q->wierzchołek = newElement;
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
							q->koniec->next = newElement;
							newElement->previous = q->koniec;
							q->koniec = newElement;
							q->koniec->next = NULL;
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
	if (q->wierzchołek!= NULL)
	{
		struct element* tmp = q->wierzchołek; //iterator po kolejce
		
			while (tmp != NULL)
			{
				if (tmp->priority == prior) //pierwszy element o zadanym priorytecie
				{
					if (prior == q->koniec->priority)
					{   
						q->koniec = tmp->previous;
						if (q->koniec == NULL)//kolejka ma wszystkie el tego samego priorytetu
						{
							q->wierzchołek == NULL; // kolejka bedzie pusta
						}
						else
						{
							q->koniec->next = NULL;
						}
						while (tmp!= NULL) //wszystkie elementy o zadanym priorytecie
						{
							struct element* usun = tmp;
							tmp = tmp->next;
							free(usun);
						}
						
					}
					else if (prior == q->wierzchołek->priority)
					{
						while (tmp->priority == prior) //wszystkie elementy o zadanym priorytecie
						{
							struct element* usun = tmp;
							tmp = tmp->next;
							free(usun);
						}
						tmp->previous = NULL;
						q->wierzchołek = tmp;
					}
					else
					{
						while (tmp->priority == prior) //wszystkie elementy o zadanym priorytecie
						{
							struct element* usun = tmp;
							tmp->previous->next = tmp->next;
							tmp->next->previous = tmp->previous;
							tmp = tmp->next;
							free(usun);
						}
					}
					
					break;
				}
				tmp = tmp->next;
			}
			printf("\n Usunieto elementy o priorytecie %i\n", prior);
	}
}

void print(struct queue* q)
{
	struct element* tmp = q->wierzchołek; //pierwszy element - wierzchołek kolejki

	if (tmp == NULL) {
		printf("\nKOLEJKA JEST PUSTA\n");
	}
	else {
		printf("\nAKTUALNA ZAWARTOSC KOLEJKI: \n");
		while (tmp != NULL) {
			printf("( %i ) , %s \n", tmp->priority, tmp->value);
			tmp = tmp->next;
		}
	}

}

struct queue merge(struct queue* q, struct queue* q1)
{
	struct queue w;
	w.wierzchołek = NULL;
	w.koniec = NULL;
	struct element* it = q->wierzchołek, * it1 = q1->wierzchołek; //iteratory po kolejkach 
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
void usun(struct queue* kolejka)
{
	struct element* usun = kolejka->wierzchołek;
	if (kolejka->wierzchołek)
	{
		kolejka->wierzchołek = kolejka->wierzchołek->next;
		free(usun);
	}
}

int main()
{
	struct queue q;
	q.wierzchołek = NULL;
	q.koniec = NULL;
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

	char wypisz[50] ;
	strcpy_s(wypisz, sizeof(wypisz), pop(&q));
	printf("\n Usunieto element: %s\n", wypisz);
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
	q1.wierzchołek = NULL;
	q1.koniec = NULL;
	insert(e5, 1, &q1);
	insert(e6, 2,&q1);
	print(&q1);
	delete_by_priority(1, &q1);
	print(&q1);

	strcpy_s(wypisz, sizeof(wypisz), pop(&q1));
	printf("\n Usunieto element: %s\n", wypisz);
	print(&q1);
	struct element* e7 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e7->value, sizeof(e7->value), "Jola Adamczyk");
	struct element* e8 = (struct element*) malloc(sizeof(struct element));
	strcpy_s(e8->value , sizeof(e8->value), "Zyta Jowisz");
	insert(e7, 1, &q1);
	insert(e8, 0, &q1);
	printf("\n Kolejki do polaczenia:\n");
	print(&q1);
	print(&q);
	struct queue q2;
	q2 = merge(&q, &q1);
	printf("\nKolejka polaczona:\n");
	print(&q2);
	usun(&q);
	usun(&q1);
	usun(&q2);
	
	return 0;
}