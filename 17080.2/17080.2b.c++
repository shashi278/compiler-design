/*
	Topic: Compiler Design
	Program: Write a Cpp program to call any desired function in a realocatable file
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

	int sym_offset;
	int symIdx;
	int link;
	int sh_size;
	int txt_offset;

	for(int i=0; i<elfhp->e_shnum; i++){
		char * name;
		name= (((char*)elfhp+shstrp->sh_offset)+shp[i].sh_name);
		if(strcmp(name, ".symtab")==0){
			sym_offset= shp[i].sh_offset;
			link= shp[i].sh_link;
			symIdx= i;
			sh_size= shp[i].sh_size;
		}
		if(strcmp(name, ".text")==0)
			txt_offset= shp[i].sh_offset;

		//print each name
		//printf("%d => %s\n", i,(((char*)elfhp+shstrp->sh_offset)+shp[i].sh_name));
	}
	
	//symtab strtab pointer
	Elf64_Shdr *symstr= &shp[link];
	int symstr_offset= symstr->sh_offset;

	//symtab pointer
	Elf64_Sym *symtab= (Elf64_Sym *)((char*)elfhp+sym_offset);

	//Store all the functions name.
	char* all_funcs[sh_size/24];

	//not sure why is it working for 24
	for(int i=0; i<(sh_size/24);i++){
		char * func= ((char *)elfhp+symstr_offset)+symtab[i].st_name;
		all_funcs[i]= func;

		//print names of each section in .symtab
		//printf("%d => %s\n", i,func);

	}

	printf("\nAll functions in %s:\n-----------------------\n", all_funcs[1]);
	for(int i=0; i<(sh_size/24); i++){
		if(strlen(all_funcs[i])!=0 && i!=1)
			printf("%s\n", all_funcs[i]);
	}
	printf("-----------------------\n");

	char user_func[10];
	printf("Enter a function name: ");
	scanf("%s", user_func);
	int func_ent_idx;

	for(int i=0; i<(sh_size/24);i++){
		char * func= ((char *)elfhp+symstr_offset)+symtab[i].st_name;
		
		if(strcmp(user_func, func)==0 && strlen(func)!=0){
			func_ent_idx= i;
			break;
		}
		else
			func_ent_idx=  -1;

	}

	if(func_ent_idx==-1){
		printf("No function '%s' in %s. Exiting.\n", user_func, all_funcs[1]);
		close(fd);
		return 0;
	}

	int (*funp)(int);
	int n, res;
	printf("Enter a number: ");
	scanf("%d",&n);

	//pointer to the desired function
	funp= (int (*)(int))((char*)elfhp+txt_offset+symtab[func_ent_idx].st_value);
	res= (*funp)(n);
	printf("%s(%d)= %d\n",user_func,n,res);
	
	close(fd);
	return 0;
}