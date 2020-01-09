//
// Created by pierreantoine on 08/01/2020.
//

#pragma once

int yylex();
void yyrestart(FILE *file);
int yyinput();
void yyterminate();

extern int yylineno;
extern char* yytext;
extern FILE* yyout;
extern FILE* yyin;