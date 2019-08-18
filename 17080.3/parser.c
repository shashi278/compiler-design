//parser.c
#include<malloc.h>
#include<parser.h>
#include<lex.h>

token_t token;

int parseExp(ASTnode_t **, FILE *);

int parser(ASTnode_t **tpp, FILE *fp){

	//first token must be '('
	if(getNextToken(fp)==1 && token.tokenClass=='('){
		//create internal node I & call parseExp
		(*tpp)->type= 'I';
		(*tpp)->left= (ASTnode_t *)malloc(sizeof(ASTnode_t));

		//go for the left sub-tree
		if(getNextToken(fp)==1 && parseExp(&(*tpp)->left, fp)==1){
			//if left sub-tree gives a success, construct right one
			(*tpp)->op= token.tokenClass;
			(*tpp)->right= (ASTnode_t *)malloc(sizeof(ASTnode_t));

			//go for right one
			if(getNextToken(fp)==1 && parseExp(&(*tpp)->right, fp)==1){
				//if right gives a success, it must be the end
				if(getNextToken(fp)==1 && token.tokenClass==END)
					return 1;
			}
		}
	}
	//If anything else, can't accept that!
	return 0;
}

int parseExp(ASTnode_t **tpp, FILE *fp){

	if(token.tokenClass==NUM || token.tokenClass=='r'){
		//create leaf node
		if(token.tokenClass==NUM){
			(*tpp)->type='D';
			(*tpp)->val= token.val;
		}
		else{
			(*tpp)->type='R';
		}
		(*tpp)->left= NULL;
		(*tpp)->right= NULL;

		//getNextToken(fp);
		if(getNextToken(fp)==1 && (token.tokenClass=='+' || token.tokenClass=='-' || token.tokenClass=='*' || token.tokenClass=='/' || token.tokenClass==')'))
			return 1;
		return 0;
	}

	if(token.tokenClass=='('){
		//create internal node I & make a recursive call to parseExp
		(*tpp)->type= 'I';
		(*tpp)->left= (ASTnode_t *)malloc(sizeof(ASTnode_t));
		
		//go for inner left sub-tree
		if(getNextToken(fp)==1 && parseExp(&(*tpp)->left, fp)==1 ){
			//if left sub-tree gives a success, construct right one
			(*tpp)->op= token.tokenClass;
			(*tpp)->right= (ASTnode_t *)malloc(sizeof(ASTnode_t));
			//go for inner right sub-tree
			if(getNextToken(fp)==1 && parseExp(&(*tpp)->right, fp)==1 && token.tokenClass==')'){
				//if inner right gives a success, it must not be the end
				if(getNextToken(fp)==1 && token.tokenClass!=END)
					return 1;
			}
		}
	}
	//again if anything else, condition still holds
	return 0;
}