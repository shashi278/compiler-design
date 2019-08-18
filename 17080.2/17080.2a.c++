/*
	Topic: Compiler Design
	Program: Write a Cpp program to call first function in a realocatable file
	By: Shashi Ranjan(39/CSE/17080/278)
*/


#include <bits/stdc++.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int fd,size;
	Elf64_Ehdr *elfhp;
	Elf64_Shdr *shp;

	if (argc<2)
	{	
		printf("Relocatable file not specified. Exiting.\n");
		return 0;
	}

	fd= open(argv[1], O_RDONLY);
	size= sysconf(_SC_PAGE_SIZE);
	elfhp= (Elf64_Ehdr *)mmap(0, size, PROT_EXEC, MAP_SHARED, fd, 0);

	//section header pointer
	shp= (Elf64_Shdr *)((char *)elfhp+ elfhp->e_shoff);

	// section header string table index
	Elf64_Shdr *shstrp= &shp[elfhp->e_shstrndx];

	int offset;
	int txtIdx;
	for(int i=0; i<elfhp->e_shnum; i++){
		char * name;
		name= (((char*)elfhp+shstrp->sh_offset)+shp[i].sh_name);
		if(strcmp(name, ".text")==0){
			offset= shp[i].sh_offset;
			txtIdx= i;
		}

		//print each name
		//printf("%d => %s\n", i,(((char*)elfhp+shstrp->sh_offset)+shp[i].sh_name));
	}
	
	// calling of first function at .text
	int (*funp)(int);
	int n, sq;
	printf("Calling first function from .text\nEnter a number: ");
	scanf("%d",&n);
	funp= (int (*)(int))((char*)elfhp+offset);
	sq= (*funp)(n);
	printf("sq(%d)= %d\n",n,sq);
	
	close(fd);

	return 0;
}