#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum myTasks {
	TASK1,
	TASK2,
	TASK3,
	TASK4,
	TASK5,
	TASKS
};

typedef struct Player {
    char * firstName;
    char * secondName;
    int points;
} Player;

typedef struct Team {
	int count;
	char * name;
	Player * players;
} Team;

typedef struct Node {
	Team * data;
	struct Node * next;
} Node;

typedef struct Match {
	Team * teamA;
	Team * teamB;
	struct Match * next;
} Match;

typedef struct Queue {
	Match * front;
	Match * rear;
} Queue;

typedef struct TreeNode {
	Team * data;
	struct TreeNode * left;
	struct TreeNode * right;
} TreeNode;

typedef struct TreeNodeAVL {
	int key;
	int height;
	Team * data;
	struct TreeNodeAVL * left;
	struct TreeNodeAVL * right;
} TreeNodeAVL;

/* Declarations of the main tasks functions. */

int getTask(FILE * fileInput);
Node * createList(FILE * fileInput);
void compressList(Node ** headNode);
Node * matchTheTeams(Node * headList, FILE * fileOutput);
void sortUsingBST(Node ** topEight, FILE * fileOutput);
void printLevelAVL(Node * topEight, int level, FILE * fileOutnput);

/* Declarations of the List (utility) functions */

Node * allocateNode(int count);
Node * copyList(Node * myNode);

int getEntriesNumber(Node * headList);
float getAverageScore(Team * myTeam);

void freeNode(Node * myNode);
void increaseTeamPoints(Team * myTeam);
void deleteNode(Node ** headNode, Node * removeNode);
void displayList(Node * headList, FILE * fileOut);
void deleteList(Node ** head);

/* Declarations of the Stack (utility) functions. */

void pushInStack(Node ** top, Team * data);
void popInStack(Node ** top);
void emptyStack(Node ** myStack);

/* Declarations of the Queue (utility) functions. */

void enQueue(Queue * myQueue, Team * teamA, Team * teamB);
void deQueue(Queue * myQueue);
void fillQueue(Queue * myQueue, Node * headList);

/* Declarations of the BinarySearchTree (utility) functions. */

TreeNode * createTreeNode(Team * data);
TreeNode * insertTreeNode(TreeNode * Node, Team * data);
void deleteTree(TreeNode * root);
void inOrderTraversal(TreeNode * rootTree, Node ** myStack);

/* Declarations of the AVL Tree (utility) functions. */

int height(TreeNodeAVL * myNode);
int getBalance(TreeNodeAVL * myNode);

TreeNodeAVL * newNode(Team * data, int key);
TreeNodeAVL * rightRotate(TreeNodeAVL * T2);
TreeNodeAVL * leftRotate(TreeNodeAVL * T1);
TreeNodeAVL * insertNodeAVL(TreeNodeAVL * myNode, Team * data, int key);

void deleteAVLTree(TreeNodeAVL * root);
void printLevel(TreeNodeAVL * rootTree, int level, FILE * fileOutput);

/* Declarations of general (utility) functions. */

int max(int a, int b);
void trimString(char * name);

#endif