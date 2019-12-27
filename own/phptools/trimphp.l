%{
#include <iostream>
#include <stdexcept>
#include <vector>
bool only_side_effects = false;
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

<PHP>"#"            { BEGIN COMMENT_LINE; }
<PHP>"//"           { BEGIN COMMENT_LINE; }

<PHP>"/*"           { BEGIN COMMENT_BLOCK; }
<PHP>.              { std::cout << yytext; }

<COMMENT_BLOCK>\n   { std::cout << '\n'; }
<COMMENT_BLOCK>"*/" { BEGIN PHP; }
<COMMENT_BLOCK>.    ;

<COMMENT_LINE>\n    { std::cout << '\n'; BEGIN PHP; }
<COMMENT_LINE>.     ;


%%

void scan(const char *filename);
bool is_option(const char* string);

int main(int argc, char **argv)
{
    std::vector<char*> arguments;
    arguments.reserve(argc);

    for (int i =1; i<argc; ++i){
        if (!is_option(argv[i])) {
            arguments.push_back(argv[i]);
        }
    }

    if (arguments.size() < 1)
    {
        yylex();
        return 0;
    }

    try
    {
        for (const auto & file : arguments){
            scan(file);
        }
        return 0;
    } catch(const std::runtime_error &e){
        return 1;
    }
}

bool is_option(const char* string) {
    return strcmp(string, "--side-effect") == 0;
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
