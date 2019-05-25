%{

int in_quote=0;
%}

quote \"

%%


{quote}             { in_quote=!in_quote; }
[^"\n]*             { printf ("%s", yytext); }
\n                  { if (!in_quote) printf("\n");}

