#include "Main.h"

TreeNode * createTreeNode(Team * data) 
{
	TreeNode * Node = (TreeNode *) malloc(sizeof(TreeNode));

	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;

	return Node;
}

TreeNode * insertTreeNode(TreeNode * myNode, Team * data)
{
	if (myNode == NULL) {
		return createTreeNode(data);
	}

	if (getAverageScore(data) == getAverageScore(myNode->data)) {
		if (strcmp(data->name, myNode->data->name) < 0) {
			myNode->left = insertTreeNode(myNode->left, data);
		}
		else {
			myNode->right = insertTreeNode(myNode->right, data);
		}
	} else if (getAverageScore(data) < getAverageScore(myNode->data)) {
		myNode->left = insertTreeNode(myNode->left, data);
	} else {
		myNode->right = insertTreeNode(myNode->right, data);
	}

	return myNode;
}

void inOrderTraversal(TreeNode * rootTree, Node ** myStack)
{
	if (rootTree) {
		inOrderTraversal(rootTree->left, myStack);
		pushInStack(myStack, rootTree->data);
		inOrderTraversal(rootTree->right, myStack);
	}
}

void deleteTree(TreeNode * root)
{
    if (root == NULL) return;
 
    deleteTree(root->left);
    deleteTree(root->right);
   
    free(root);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(TreeNodeAVL * myNode)
{
	if (myNode == NULL) {
		return 0;
	} else {
		return myNode->height;
	}
}

int getBalance(TreeNodeAVL * myNode)
{
	if (myNode == NULL) {
		return 0;
	} else {
		return height(myNode->left) - height(myNode->right);
	}
}

TreeNodeAVL * newNodeAVL(Team * data, int key)
{
	TreeNodeAVL * myNode = (TreeNodeAVL*) malloc(sizeof(TreeNodeAVL));
	myNode->data = data;
	myNode->key = key;
	myNode->left = NULL;
	myNode->right = NULL;
	myNode->height = 1;

	return myNode;
}

TreeNodeAVL * rightRotate(TreeNodeAVL * T2)
{
	TreeNodeAVL * T1 = T2->left;
	TreeNodeAVL * T3 = T1->right;

	T1->right = T2;
	T2->left = T3;

	T2->height = max(height(T2->left), height(T2->right)) + 1;
	T1->height = max(height(T1->left), height(T1->right)) + 1;
 
	return T1;
}

TreeNodeAVL * leftRotate(TreeNodeAVL * T1)
{
	TreeNodeAVL * T2 = T1->right;
	TreeNodeAVL * T3 = T2->left;

	T2->left = T1;
	T1->right = T3;

	T1->height = max(height(T1->left), height(T1->right)) + 1;
	T2->height = max(height(T2->left), height(T2->right)) + 1;

	return T2;
}

TreeNodeAVL * insertNodeAVL(TreeNodeAVL * myNode, Team * data, int key)
{ 
    if (myNode == NULL)
        return (newNodeAVL(data, key));
 
 	if (key < myNode->key) {
		myNode->left = insertNodeAVL(myNode->left, data, key);
	} else {
		myNode->right = insertNodeAVL(myNode->right, data, key);
	}

    myNode->height = 1 + max(height(myNode->left), height(myNode->right));
 
    int balance = getBalance(myNode);
 
	if (balance > 1 && key < myNode->left->key) {
		return rightRotate(myNode);
	}

	if (balance < -1 && key > myNode->right->key) {
		return leftRotate(myNode);
	}

	if (balance > 1 && key > myNode->left->key) {
		myNode->left = leftRotate(myNode->left);
		return rightRotate(myNode);
	}

	if (balance < -1 && key < myNode->right->key) {
		myNode->right = rightRotate(myNode->right);
		return leftRotate(myNode);
	}
    
    return myNode;
}

void deleteAVLTree(TreeNodeAVL * root)
{
    if (root == NULL) return;
 
    deleteAVLTree(root->left);
    deleteAVLTree(root->right);
   
    free(root);
}

void printLevel(TreeNodeAVL * rootTree, int level, FILE * fileOutput)
{
	if (rootTree == NULL) {
		return;
	} else if (level == 1) {
		fprintf(fileOutput, "%s\r\n", rootTree->data->name);
	} else if (level > 1) {
		printLevel(rootTree->left, level - 1, fileOutput);
		printLevel(rootTree->right, level - 1, fileOutput);
	}
}