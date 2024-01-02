#include "Main.h"

Node * allocateNode(int count) {
	int nameSize = 40;

	Node * newNode = (Node *) malloc (sizeof(Node));

	newNode->data = (Team *) malloc(sizeof(Team));
	newNode->data->name = (char *) malloc(sizeof(char) * nameSize);
	newNode->data->players = (Player *) malloc(sizeof(Player) * count);

	for (int i = 0; i < count; i++) {
		newNode->data->players[i].firstName = (char *) malloc(sizeof(char) * nameSize);
		newNode->data->players[i].secondName = (char *) malloc(sizeof(char) * nameSize);
	}

	return newNode;
}

void freeNode(Node * myNode)
{
	for (int i = 0; i < myNode->data->count; i++) {
		free(myNode->data->players[i].firstName);
		free(myNode->data->players[i].secondName);
	}

	free(myNode->data->players);
	free(myNode->data->name);
	free(myNode->data);
	free(myNode);
}

void deleteNode(Node ** headNode, Node * toRemoveNode) {
	Node * current = NULL;

	if ((*headNode) == toRemoveNode) {
		current = (*headNode)->next;
		freeNode(*headNode);
		(*headNode) = current;
	} else {
		Node * var = (*headNode);
		for (var; var->next != toRemoveNode; var = var->next);
		
		current = var->next;
		var->next = var->next->next;
		freeNode(current);	
	}
}

Node * copyList(Node * myNode)
{
	Node * newNode = allocateNode(myNode->data->count);

	newNode->data->count = myNode->data->count;
	strcpy(newNode->data->name, myNode->data->name);

	for (int i = 0; i < newNode->data->count; i++) {
		strcpy(newNode->data->players[i].firstName, myNode->data->players[i].firstName);
		strcpy(newNode->data->players[i].secondName, myNode->data->players[i].secondName);
		newNode->data->players[i].points = myNode->data->players[i].points;
	}

	return newNode;
}

int getEntriesNumber(Node * headList) 
{
	int entries = 0;
	for (entries, headList; headList != NULL; headList = headList->next, entries += 1);

	return entries;
}

float getAverageScore(Team * myTeam)
{
	float sum = 0;
	for (int i = 0; i < myTeam->count; i++) {
		sum += myTeam->players[i].points;
	}

	return sum / myTeam->count;
}

void increaseTeamPoints(Team * myTeam)
{
	for (int var = 0; var < myTeam->count; var++) {
		myTeam->players[var].points += 1;
	}
}

void trimString(char * name) 
{
	int nameLength = strlen(name);

	if (name[nameLength - 3] == ' ') {
			name[nameLength - 3] = '\0';
	} else {
		if (name[nameLength - 2] == '\r') {
			name[nameLength - 2] ='\0';
		}
	}
}

void displayList(Node * headList, FILE * fileOutput)
{
	for (headList; headList != NULL; headList = headList->next) {
		fprintf(fileOutput, "%s\r\n", headList->data->name);
	}
}

void deleteList(Node ** head) {
	Node * copy = NULL;

	while ((*head) != NULL) {
		copy = (*head)->next;
		freeNode(*head);
		(*head) = copy;
	}
}

void pushInStack(Node ** top, Team * data)
{
	Node * newNode = (Node *) malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = (*top);

	(*top) = newNode;
}

void popInStack(Node ** top)
{
	Node * current = (*top);
	(*top) = (*top)->next;
	free(current);
}

void emptyStack(Node ** myStack)
{
	while ((*myStack) != NULL) {
		popInStack(myStack);
	}
}