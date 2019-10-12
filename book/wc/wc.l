%{
    int chars = 0;
    int words = 0;
    int lines = 0;
%}

%%

[a-zA-Z0-9]+  { words+=1; chars+=strlen(yytext); }
\n            { chars+=1; lines+=1;}
.             { chars+=1; }

%%

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        if (!(yyin = fopen(argv[1], "r")))
        {
            perror(argv[1]);
            return 1;
        }
    }
    yylex();
    printf("Chars: %d\nWords: %d\nLines: %d\n",chars,words,lines);
    return 0;
}
