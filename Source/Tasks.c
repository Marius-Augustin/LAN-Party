#include "Main.h"
 
int getTask(FILE * fileTasks) 
{
	bool * tasks = (bool *) malloc(sizeof(bool) * TASKS);

	for (int var = 0; var < TASKS; var++) 
		fscanf(fileTasks, "%d", &tasks[var]);
		
	for (int var = TASKS - 1; var >= 0; var--) {
		if (tasks[var]) return var;
	}
}

/* Task 1 - create a linked list reading the data from the file.
	Return a pointer (Node *) to the head node of the list. */

Node * createList(FILE * fileInput)
{
	int teamCount, playerCount, nameLength;
	Node * headNode = NULL;
	Node * newNode = NULL;
	
	fscanf(fileInput, "%d", &teamCount);

	for (int i = 0; i < teamCount; i++) {
		fscanf(fileInput, "%d ", &playerCount);
		newNode = allocateNode(playerCount);
		newNode->data->count = playerCount;
		
		/* Read the team's name and remove additional characters such 
			as Space, Carriage Return and Line Feed from it. */

		fgets(newNode->data->name, 40, fileInput);
		trimString(newNode->data->name);

		for (int i = 0; i < playerCount; i++) {
			fscanf(fileInput, "%s", newNode->data->players[i].firstName); 
			fscanf(fileInput, "%s", newNode->data->players[i].secondName);
			fscanf(fileInput, "%d", &newNode->data->players[i].points); 
		}

		newNode->next = headNode;
		headNode = newNode;
	}

	return headNode;
}

/* Task 2 - remove the lowest scoring teams from the list until n remain.
	n = the biggest power of 2 lower than the current team count. */

void compressList(Node ** headNode)
{
	Node * current = NULL; 
	float lowestScore, averageScore;

	int newCount, teamCount = getEntriesNumber(*headNode);
	for (newCount = 1; newCount * 2 <= teamCount; newCount *= 2);
	
	for (int i = 0; i < teamCount - newCount; i++) {
		lowestScore = 10;
		for (Node * var = (*headNode); var != NULL; var = var->next) {
			averageScore = getAverageScore(var->data);
			if (averageScore < lowestScore) {
				lowestScore = averageScore;
				current = var;
			}			
		}
		deleteNode(headNode, current);
	}
}

/* Tasks 3 - Create matches with the elements (teams) of a list in the given order.
			Return a list (Node *) with the Top 8 teams. */

Node * matchTheTeams(Node * headList, FILE * fileOutput)
{
	int roundCount = 0, teamCount = getEntriesNumber(headList);
	float scoreA, scoreB;

	/* Find the number of rounds. */

	for (teamCount; teamCount != 1; teamCount /= 2, roundCount += 1);

	Queue * myQueue = (Queue *) malloc(sizeof(Queue));
	myQueue->rear = NULL;
	myQueue->front = NULL;

	Node * winnerStack = NULL;
	Node * loserStack = NULL;
	Node * topEight = NULL;

	fillQueue(myQueue, headList);

	for (int i = 0; i < roundCount; i++) {
		fprintf(fileOutput, "\r\n--- ROUND NO:%d\r\n", i + 1);

		/* Create a match with every element from the Queue, push the 
			winner / loser team into their stacks and deQueue. */

		Match * var;
		while (myQueue->front != NULL) {
			scoreA = getAverageScore(myQueue->front->teamA);
			scoreB = getAverageScore(myQueue->front->teamB);
			if (scoreA > scoreB) {
				pushInStack(&winnerStack, myQueue->front->teamA);			
				pushInStack(&loserStack, myQueue->front->teamB);
			} else {
				pushInStack(&winnerStack, myQueue->front->teamB);			
				pushInStack(&loserStack, myQueue->front->teamA);
			}

			fprintf(fileOutput, "%-33s-%33s\r\n", myQueue->front->teamA->name, myQueue->front->teamB->name);
		
			deQueue(myQueue);
			if (i == roundCount - 1) {
				myQueue->front = NULL;
			}
		}
		
		/* Refill the Queue if there are more than 1 elements in the winner Stack. */

		if (getEntriesNumber(winnerStack) > 1) {
			fillQueue(myQueue, winnerStack);
		} 

		/* Increase the points of the winning teams and print them in the file. */

		fprintf(fileOutput, "\r\nWINNERS OF ROUND NO:%d\r\n", i + 1);
		for (Node * var = winnerStack; var != NULL; var = var->next) {
			increaseTeamPoints(var->data);
			fprintf(fileOutput, "%-34s-  %.2f\r\n", var->data->name, getAverageScore(var->data));
		}

		/* If 8 teams remains save them in another list. */

		if (getEntriesNumber(winnerStack) == 8) {
			Node * copy = NULL;
			for (Node * var = winnerStack; var != NULL; var = var->next) {
				copy = copyList(var);
				pushInStack(&topEight, copy->data);
			}
		}

		/* Empty the stacks */

		emptyStack(&winnerStack);
		emptyStack(&loserStack);	
	}

	return topEight;
}

/* Sort the elements of a list (topEight) by inserting them 
	into a Binary Search Tree and update the list. */

void sortUsingBST(Node ** topEight, FILE * fileOutput)
{
	/* Insert the elements into a Binary Search Tree */

	TreeNode * rootTree = NULL;
	for (Node * var = *topEight; var != NULL; var = var->next) {
		rootTree = insertTreeNode(rootTree, var->data);	
	}

	/* Empty the stack and fill it with the elements of the BST inorder. */

	emptyStack(topEight);
	inOrderTraversal(rootTree, topEight);

	/* Print the sorted order into the file */

	fprintf(fileOutput, "\r\nTOP 8 TEAMS:\r\n");
	for (Node * var = *topEight; var != NULL; var = var->next) {
		fprintf(fileOutput, "%-34s-  %.2f\r\n", var->data->name, getAverageScore(var->data));
	}

	deleteTree(rootTree);
}

/* Insert the elements of a list into an AVL Binary Tree 
	and print the elements of a given level. */

void printLevelAVL(Node * topEight, int level, FILE * fileOutput)
{
	TreeNodeAVL * AVL = NULL; 
	int keyToCompare = 0;

	for (Node * var = topEight; var != NULL; var = var->next) {	
		AVL = insertNodeAVL(AVL, var->data, keyToCompare);
		keyToCompare += 1;
	}

	fprintf(fileOutput, "\r\nTHE LEVEL %d TEAMS ARE: \r\n", level);
	printLevel(AVL, level + 1, fileOutput);

	deleteAVLTree(AVL);
}