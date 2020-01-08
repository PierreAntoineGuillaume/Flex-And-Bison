%{
#include <iostream>
#include <stdexcept>
#include <vector>
bool only_side_effects = false;

void toggle_php_mode();
%}

%option noyywrap caseless yylineno

%x PHP
%x PHP_SIDE_EFFECT
%x COMMENT_LINE
%x COMMENT_BLOCK

%%

"<?"|"<?php"|"<?=" {
    std::cout << yytext;
    toggle_php_mode();
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

<PHP_SIDE_EFFECT>"#"            { BEGIN COMMENT_LINE; }
<PHP_SIDE_EFFECT>"//"           { BEGIN COMMENT_LINE; }
<PHP_SIDE_EFFECT>"/*"           { BEGIN COMMENT_BLOCK; }

<PHP>.              { std::cout << yytext; }
<PHP_SIDE_EFFECT>.              { ; }

<COMMENT_BLOCK>\n   { std::cout << '\n'; }
<COMMENT_BLOCK>"*/" { toggle_php_mode(); }
<COMMENT_BLOCK>.    ;

<COMMENT_LINE>\n    { std::cout << '\n'; toggle_php_mode(); }
<COMMENT_LINE>.     ;


%%

void scan(const char *filename);
bool is_option(const char* string);
void parse_option(int argc, char **argv);
int main(int argc, char **argv)
{
    std::vector<char*> arguments;
    arguments.reserve(argc);

    for (int i =1; i<argc; ++i){
        if (is_option(argv[i])) {
            parse_option(argc-i, argv+i);
            continue;
        }
        arguments.push_back(argv[i]);
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
    return strcmp(string, "--side-effects") == 0;
}

void parse_option(int argc, char **argv)
{
    if (argc == 0)
    {
        return;
    }
    if (strcmp(argv[0], "--side-effects") == 0)
    {
        only_side_effects=true;
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

void toggle_php_mode() 
{
    if (only_side_effects)
    {
        BEGIN PHP_SIDE_EFFECT;
    }
    else
    {
        BEGIN PHP;
    }
}