#include <stdio.h>
#include <stdlib.h>

struct t_token
{
    int intTokenCode;
    char *strTokenSourceCodeText;
    int intRow;
    int intColumn;
    struct t_token *ptrNext;
};
typedef struct t_token t_token;
t_token *ptrTokenList = NULL;
t_token *ptrCurrentToken = NULL;

int scanner(char * strFileName);
void PrintTokenList();
void FreeTokenList();
void parser_LL();
void parser_RDCP();


int main()
{
    scanner("../SourceCode.txt");
    PrintTokenList();
    //parser_LL();
    parser_RDCP();
    FreeTokenList ();
    return 0;
}
