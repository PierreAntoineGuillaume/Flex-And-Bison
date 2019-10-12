
%option noyywrap

%{
    int chars = 0;
    int words = 0;
    int lines = 0;
    int total_chars = 0;
    int total_words = 0;
    int total_lines = 0;
%}


%%

[a-zA-Z0-9]+  { words+=1; chars+=strlen(yytext); }
\n            { chars+=1; lines+=1;}
.             { chars+=1; }

%%


int scan(const char *filename);
void print_results(const char *filename);
void reset_counters();
void accumulate_counters();

int main(int argc, char** argv)
{
    if (argc < 1)
    {
        yylex();
        print_results("");
        return 0;
    }

    for (int i =1; i<argc; ++i){
        if (scan(argv[i]))
        {
            return 1;
        }
    }

    if (argc>2)
    {
        printf("%8d%8d%8d total\n", total_chars, total_words, total_lines);
    }

    return 0;
}

int scan(const char *filename)
{
    FILE *file_handle = fopen(filename, "r");
    if (!file_handle)
    {
        perror(filename);
        return 1;
    }

    yyrestart(file_handle);
    yylex();
    fclose(file_handle);

    print_results(filename);

    accumulate_counters();
    reset_counters();
    return 0;
}

void accumulate_counters()
{
    total_chars +=chars;
    total_words +=words;
    total_lines +=lines;
}

void reset_counters()
{
    words = 0;
    lines = 0;
    chars = 0;
}

void print_results(const char *filename)
{
    printf("%8d%8d%8d %s\n",chars,words,lines, filename);
}