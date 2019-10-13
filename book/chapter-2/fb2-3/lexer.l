
%option noyywrap yylineno
%x IFILE

%{
    struct bufstack
    {
        struct bufstack *prev;
        YY_BUFFER_STATE bs;
        int lineno;
        char *filename;
        FILE *f;
    } *curbs = nullptr;

    char *curfilename;

    int newfile(char *fn);
    int popfile();
%}

%%

^"#"[ \t]*include[ \t]*[\"<]        { BEGIN IFILE; }

<IFILE>[^ \t\n\">]+                 {
                                        for (int c; c != '"' && c != '\n'; c=yyinput());
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
                                        char file[30];
                                        sprintf(file, "%s:%d", curfilename, yylineno);
                                        fprintf(yyout, "%-30s %s", file, yytext);
                                    }

^\n                                 ;

\n                                  {
                                        ECHO;
                                    }

.                                   {
                                        ECHO;
                                    }

%%

int main(int argc, char **argv)
{
    if (argc<2)
    {
        fprintf(stderr, "Error : fb2-2 requires a filename as an argument\n");
        return 1;
    }
    if (newfile(argv[1]))
    {
        yylex();
    }
    return 0;
}


#include <cstdlib>
#include <cstring>


int newfile(char *fn)
{
    FILE *f = fopen(fn, "r");
    if (!f)
    {
        perror(fn);
        return 0;
    }
    struct bufstack *bs = (struct bufstack*) malloc(sizeof(struct bufstack));

    if (!bs)
    {
        perror("malloc");
        exit(1);
    }

    if (curbs)
    {
        curbs->lineno = yylineno;
    }

    bs->prev = curbs;
    bs->f = f;
    bs->filename = strdup(fn);
    bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
    yy_switch_to_buffer(bs->bs);
    curbs = bs;
    yylineno = 1;
    curfilename = bs->filename;
    return 1;
}

int popfile()
{
    struct bufstack *bs = curbs;
    struct bufstack *prevbs;

    if (!bs)
    {
        return 0;
    }

    fclose(bs->f);
    free(bs->filename);
    yy_delete_buffer(bs->bs);
    prevbs = bs->prev;
    free(bs);

    if (!prevbs)
    {
        return 0;
    }

    yy_switch_to_buffer(prevbs->bs);
    curbs=prevbs;

    yylineno=curbs->lineno;
    curfilename=curbs->filename;

    return 1;
}