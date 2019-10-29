%{
    #include <iostream>
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

int main()
{
    yylex();
    return 0;
}
