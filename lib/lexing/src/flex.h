//
// Created by pierreantoine on 08/01/2020.
//

#pragma once

#include <cstdio>

int yylex();
void yyrestart(FILE * file);
static int yyinput();
void yyterminate();

extern int yylineno;
extern char* yytext;
extern FILE* yyout;
extern FILE* yyin;