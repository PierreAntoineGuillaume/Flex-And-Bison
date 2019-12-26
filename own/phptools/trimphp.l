%{
#include <iostream>
#include <stdexcept>
%}

%option noyywrap caseless yylineno

%x PHP
%x COMMENT_LINE
%x COMMENT_BLOCK

%%

"<?"|"<?php"|"<?=" {
    std::cout << yytext;
    BEGIN PHP;
}

<PHP>"?>" {
    std::cout << yytext;
    BEGIN INITIAL;
}

.                   ;
\n                  { std::cout  << '\n'; }
<PHP>.              { std::cout << yytext; }

<PHP>"#"            { BEGIN COMMENT_LINE; }
<PHP>"//"           { BEGIN COMMENT_LINE; }

<PHP>"/*"           { BEGIN COMMENT_BLOCK; }

<COMMENT_BLOCK>.    ;
<COMMENT_BLOCK>\n   { std::cout << '\n'; }
<COMMENT_BLOCK>"*/" { BEGIN PHP; }

<COMMENT_LINE>.     ;
<COMMENT_LINE>\n    { std::cout << '\n'; BEGIN PHP; }


%%

void scan(const char *filename);

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        yylex();
        return 0;
    }

    try
    {
        for (int i =1; i<argc; ++i){
            scan(argv[i]);
        }
        return 0;
    } catch(const std::runtime_error &e){
        return 1;
    }
}

void scan(const char *filename)
{
    FILE *file_handle = fopen(filename, "r");
    if (!file_handle)
    {
        throw std::runtime_error("Could not open file");
    }

    yyrestart(file_handle);
    yylex();
    fclose(file_handle);
}
