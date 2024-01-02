#include "Main.h"

void enQueue(Queue * myQueue, Team * teamA, Team * teamB)
{
	Match * newMatch = (Match *) malloc(sizeof(Match));
	newMatch->teamA = teamA;
	newMatch->teamB = teamB;
	newMatch->next = NULL;

	if (myQueue->rear == NULL) {
		myQueue->rear = newMatch;
	} else {
		(myQueue->rear)->next = newMatch;
		(myQueue->rear) = newMatch;
	}
	
	if (myQueue->front == NULL) {
		myQueue->front = myQueue->rear;
	}
}

void deQueue(Queue * myQueue)
{
	Match * copyFront = myQueue->front;
	myQueue->front = (myQueue->front)->next;
	free(copyFront);
	copyFront = NULL;
}

void fillQueue(Queue * myQueue, Node * headList) 
{
	Team * teamA, * teamB;

	for (headList; headList != NULL; headList = headList->next->next) {
		teamA = headList->data;
		teamB = headList->next->data;
		enQueue(myQueue, teamA, teamB);
	} 
}