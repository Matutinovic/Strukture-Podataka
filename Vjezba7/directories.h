#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#define MAX_NAME_SIZE 100

struct _directory;
typedef struct _directory* Position;

typedef struct _directory {
	char name[MAX_NAME_SIZE];
	Position sibling;
	Position child;
}Directory;

struct _stack;
typedef  struct _stack* StackPosition;

typedef struct _stack
{
	Position directory;
	StackPosition next;
}Stack;

int Menu(Position root, StackPosition head);
int MakeDirectory(Position currentDirectory);
Position CreateNewDirectory(char name[]);
Position FindLastDirectory(Position first);
int InsertAfter(Position lastDirectory, Position newDirectory);
Position ChangeDirectory(Position currentDirectory);
int DeleteAfter(StackPosition head);
int Push(StackPosition head, Position currentDirectory);
Position Pop(StackPosition head);
int StackInsert(StackPosition head, StackPosition newElement);
int PrintDirectories(Position first);
int NameCheck(Position first, char name[]);

#endif