%{
    #include <iostream>
%}

%option noyywrap nodefault caseless yylineno

%x PHP
%x COMMENT
%%

"<?"|"<?php" {
    BEGIN PHP;
}

<PHP>"?>" {
    std::cout ';';
    BEGIN INITIAL;
}

. ;
<PHP>.          std::cout << yytext;
\n  ;
<PHP>\n;
