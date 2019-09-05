//backend.h
#ifndef BACKEND_H
#define BACKEND_H

#include<parser.h>

#define ZeroDivisionError -9999
#define NameError -9998
#define ZDE_msg "\nZeroDivisionError: Integer division or modulo by zero\n"
#define NE_msg "\nNameError: Name '%c' is not defined\n"

extern void raiseError(int, char);
extern int interpreter(ASTnode_t *);

#endif