src = 17080
objfiles = $(src).tab.o lex.yy.o 

a.out : $(objfiles)
	g++ $(objfiles)

$(src).tab.c++ : $(src).y++ 
	bison -d $(src).y++ 

lex.yy.c : $(src).l
	flex $(src).l   

$(src).tab.o : $(src).tab.c++
	g++ -Wall -c $(src).tab.c++

lex.yy.o : lex.yy.c
	g++ -Wall -c lex.yy.c  

clean : 
	rm $(src).tab.c++ $(src).tab.h++ lex.yy.c $(objfiles)
