#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "directories.h"

int Menu(Position root, StackPosition head)
{
	char c[MAX_NAME_SIZE] = { 0 };
	Position tmp = NULL;
	Position currentDirectory = Pop(head);
	int status = 0;

	scanf(" %[^\n]s", c);

	if (strcmp(c, "md") == 0) {
		status = MakeDirectory(currentDirectory);
		return status;
	}

	else if (strcmp(c, "cd dir") == 0)
	{
		tmp = ChangeDirectory(currentDirectory);
		if (!tmp)
			return 0;
		else {
			status = Push(head, tmp);
			return status;
		}
	}

	else if (strcmp(c, "cd..") == 0) {
		if (head->next->next == NULL)
			return 0;

		DeleteAfter(head);
		return 0;
	}

	else if (strcmp(c, "dir") == 0)
	{
		if (currentDirectory->child == NULL) {
			printf("There aren't any directories.\n");
			return 0;
		}

		PrintDirectories(currentDirectory->child);
		return 0;
	}

	else if (strcmp(c, "exit") == 0)
		return -1;

	else {
		printf("Command not recognized\n");
		return 0;
	}

}

int MakeDirectory(Position currentDirectory)
{
	char name[MAX_NAME_SIZE] = { 0 };
	Position NewDirectory = NULL;
	Position LastDirectory = NULL;

	printf("Name of the new file: ");
	scanf(" %[^\n]s", name);

	if (NameCheck(currentDirectory->child, name)) {
		printf("Directory with that name already exists.\n");
		return 0;
	}

	NewDirectory = CreateNewDirectory(name);
	if (!NewDirectory)
		return -1;

	if (currentDirectory->child == NULL) {
		currentDirectory->child = NewDirectory;
	}

	else {
		LastDirectory = FindLastDirectory(currentDirectory->child);
		InsertAfter(LastDirectory, NewDirectory);
	}

	return 0;
}

Position CreateNewDirectory(char name[])
{
	Position NewDirectory = (Position)malloc(sizeof(Directory));
	if (!NewDirectory) {
		printf("Couldn't allocate memory!");
		return NULL;
	}

	strcpy(NewDirectory->name, name);
	NewDirectory->child = NULL;
	NewDirectory->sibling = NULL;
	return NewDirectory;
}

Position FindLastDirectory(Position first)
{
	Position temp = first;

	while (temp->sibling != NULL) {
		temp = temp->sibling;
	}

	return temp;
}

int InsertAfter(Position lastDirectory, Position newDirectory)
{
	newDirectory->sibling = lastDirectory->sibling;
	lastDirectory->sibling = newDirectory;

	return 0;
}

Position ChangeDirectory(Position currentDirectory)
{
	char name[MAX_NAME_SIZE] = { 0 };
	Position temp = currentDirectory->child;

	printf("Name of the directory: ");
	scanf(" %[^\n]s", name);

	while (temp != NULL && strcmp(name, temp->name) != 0) {
		temp = temp->sibling;
	}

	if (!temp) {
		printf("Cannot find the path specified.\n");
		return NULL;
	}

	return temp;
}

int DeleteAfter(StackPosition head)
{
	StackPosition temp = head->next;
	head->next = temp->next;
	free(temp);

	return 0;
}

int Push(StackPosition head, Position currentDirectory)
{
	StackPosition NewElement = (StackPosition)malloc(sizeof(Stack));
	if (!NewElement) {
		printf("Could not allocate memory!\n");
		return -1;
	}

	NewElement->directory = currentDirectory;
	NewElement->next = NULL;
	StackInsert(head, NewElement);

	return 0;
}

int StackInsert(StackPosition head, StackPosition newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return 0;
}

int PrintDirectories(Position first)
{
	while (first != NULL) {
		printf(" %s\n", first->name);
		first = first->sibling;
	}

	return 0;
}

Position Pop(StackPosition head)
{
	return head->next->directory;
}

int NameCheck(Position first, char name[])
{
	Position temp = first;

	while (temp != NULL) {
		if (strcmp(name, temp->name) == 0)
			return 1;
		temp = temp->sibling;
	}

	return 0;
}