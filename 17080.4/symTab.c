#include<symTab.h>

symRec symTab[SIZE];

void initSymTab(){
	for(int i=0; i<SIZE; i++){
		symTab[i].def= 0;	//initially not defined
	}
}

void updateSymTab(int index, int val){
	symTab[index].def=1;
	symTab[index].val= val;
}

int getVal(int index, int *vp){
	if(symTab[index].def==1){
		*vp= symTab[index].val;
		return 1;
	}
	return 0;
}