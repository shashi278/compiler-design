#ifndef SYMTAB_H
#define SYMTAB_H
#define SIZE 60

typedef struct{
	int def;
	int val;
} symRec;

extern symRec symTab[SIZE];
void initSymTab();
void updateSymTab(int index, int val);
int getVal(int index, int *vp);

#endif