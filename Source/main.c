#include "Main.h"

int main(int argc, const char * argv[])
{
	FILE * fileInputA = fopen(argv[1], "r");
	FILE * fileInputB = fopen(argv[2], "r");
	FILE * fileOutput = fopen(argv[3], "a+t");

	Node * headList = NULL;
	Node * topEight = NULL;

	int myTask = getTask(fileInputA);
	
	if (myTask >= TASK1) {
		headList = createList(fileInputB);
		if (myTask == TASK1) {
			displayList(headList, fileOutput);
		}
	} if (myTask >= TASK2) {
		compressList(&headList);
		displayList(headList, fileOutput);
	} if (myTask >= TASK3) {
		topEight = matchTheTeams(headList, fileOutput);
	} if (myTask >= TASK4) {
		sortUsingBST(&topEight, fileOutput);
	} if (myTask == TASK5) {
		printLevelAVL(topEight, 2, fileOutput);
	}

	deleteList(&topEight);
	deleteList(&headList);

	fclose(fileInputA);
	fclose(fileInputB);
	fclose(fileOutput);

	return 0;
}
