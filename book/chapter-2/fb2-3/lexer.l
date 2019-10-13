
%option noyywrap yylineno
%x IFILE

%{

    struct bufstack
    {
        struct bufstacka *prev;
        YY_BUFFER_STATE bs;
        int lineno;
        char *filename;
        FILE *f;
    } *curbs = 0;

    char *curfilename;

    int newfile(char *fn);
    int popfile(void);
%}
%%

^"#"[ \t]*include[ \t]*[\"<]        { BEGIN IFILE; }

<IFILE>[^ \t\n\">]+                 {
                                        {
                                            int c;
                                            while ((c=yyinput()) && c != '\n');
                                        }
                                        ++yylineno;
                                        if (!newfile(yytext)) yyterminate();
                                        BEGIN INITIAL;
                                    }


<IFILE>.|\n                         {
                                        fprintf(stderr, "%4d bad include line", yylineno);
                                        yyterminate();
                                    }


<<EOF>>                             {
                                        if (!popfile()) yyterminate();
                                    }

^.                                  {
                                        fprintf(yyout, "%4d %s", yylineno, yytext);
                                    }

^\n                                 {
                                        fprintf(yyout, "%4d %s", yylineno, yytext);
                                    }

\n                                  {
                                        ECHO; yylineno+=1;
                                    }

.                                   {
                                        ECHO;
                                    }

%%

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Error : fb2-2 requires a filename as an argument\n");
        return 1;
    }
    return 0;
}

int newfile(char *fn)
{
    return 0;
}

int popfile(void)
{
    return 0;
}