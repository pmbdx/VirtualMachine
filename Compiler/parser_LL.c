#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FALSE (0)
#define TRUE (1)
#define SYMBOL_TYPE_NON_TERMINAL 1
#define SYMBOL_TYPE_TERMINAL     2

#define TERMINAL_SYMBOL_program 1
#define TERMINAL_SYMBOL_if 2
#define TERMINAL_SYMBOL_else 3
#define TERMINAL_SYMBOL_while 4
#define TERMINAL_SYMBOL_Numeric 5
#define TERMINAL_SYMBOL_Real 6
#define TERMINAL_SYMBOL_Plus 7
#define TERMINAL_SYMBOL_Minus 8
#define TERMINAL_SYMBOL_Times 9
#define TERMINAL_SYMBOL_Division 10
#define TERMINAL_SYMBOL_Minor 11
#define TERMINAL_SYMBOL_MinorEq 12
#define TERMINAL_SYMBOL_Major 13
#define TERMINAL_SYMBOL_MajorEq 14
#define TERMINAL_SYMBOL_Exclamation 15
#define TERMINAL_SYMBOL_Different 16
#define TERMINAL_SYMBOL_Assign 17
#define TERMINAL_SYMBOL_Compare 18
#define TERMINAL_SYMBOL_AND 19
#define TERMINAL_SYMBOL_OR 20
#define TERMINAL_SYMBOL_Lbrace 21
#define TERMINAL_SYMBOL_Rbrace 22
#define TERMINAL_SYMBOL_Lparen 23
#define TERMINAL_SYMBOL_Rparen 24
#define TERMINAL_SYMBOL_Question 25
#define TERMINAL_SYMBOL_Semicolon 26
#define TERMINAL_SYMBOL_Space 27
#define TERMINAL_SYMBOL_Tab 28
#define TERMINAL_SYMBOL_EOL 29
#define TERMINAL_SYMBOL_EOF 30
#define TERMINAL_SYMBOL_ID 31
#define TERMINAL_SYMBOL_colon 32
#define TERMINAL_SYMBOL_switch 33
#define TERMINAL_SYMBOL_case 34
#define TERMINAL_SYMBOL_break 35
#define TERMINAL_SYMBOL_default 36
#define TERMINAL_SYMBOL_Print 37
#define TERMINAL_SYMBOL_pow 38
#define TERMINAL_SYMBOL_private 39
#define TERMINAL_SYMBOL_public 40
#define TERMINAL_SYMBOL_INT 41
#define TERMINAL_SYMBOL_STRING 42
#define TERMINAL_SYMBOL_BOOL 43
#define TERMINAL_SYMBOL_DATETIME 44
#define TERMINAL_SYMBOL_class 45
#define TERMINAL_SYMBOL_comma 46


#define NT_S 1
#define NT_CompoundInstruction 2
#define NT_InstructionBlock 3
#define NT_InstructionBlock2 4
#define NT_Instruction 5
#define NT_AssignInstruction 6
#define NT_IfInstruction 7
#define NT_IfInstruction2 8
#define NT_WhileInstruction 9
#define NT_PrintInstruction 10
#define NT_Expression 11
#define NT_Expression2 12
#define NT_RelationalExp 13
#define NT_RelationalExp2 14
#define NT_CompoundExp 15
#define NT_CompoundExp2 16
#define NT_SimpleExp 17
#define NT_SimpleExp2 18
#define NT_Factor 19
#define NT_Factor2 20
#define NT_Term 21
#define NT_AdditiveOp 22
#define NT_MultiplicativeOp 23
#define NT_RelacionalOp 24
#define NT_LogicOp 25
#define NT_PowOp 26
#define NT_Number 27
#define NT_ClassInstr  28
#define NT_Members 29
#define NT_Members2 30
#define NT_Attribute 31
#define NT_Method 32
#define NT_DataType 33
#define NT_Parameters 34
#define NT_Parameters2 35
#define NT_Access 36



#define NT_SYMBOL_NUMMAX 38
#define T_SYMBOL_NUMMAX 49


int RM[NT_SYMBOL_NUMMAX][T_SYMBOL_NUMMAX] = {
    {1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	2,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	3,	3,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	3,	-1,	-1,	-1,	-1,	-1,	3,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	3,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	5,	-1,	-1,	-1,	4,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	5},
{-1,	7,	13,	8,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	10,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	6,	-1,	-1,	-1,	-1,	-1,	9,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	68,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	11,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	12,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	13,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	14,	-1,	14,	-1,	14,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	14},
{-1,	-1,	-1,	15,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	16,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	17,	17,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	17,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	17,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	17,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	19,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	18,	18,	-1,	19,	-1,	19,	-1,	19,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	19},
{-1,	-1,	-1,	-1,	20,	20,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	20,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	20,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	20,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	22,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	21,	21,	21,	21,	-1,	21,	-1,	21,	22,	22,	-1,	22,	-1,	22,	-1,	22,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	22},
{-1,	-1,	-1,	-1,	23,	23,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	23,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	23,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	23,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	25,	-1,	-1,	-1,	24,	24,	-1,	-1,	25,	25,	25,	25,	-1,	25,	-1,	25,	25,	25,	-1,	25,	-1,	25,	-1,	25,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	25},
{-1,	-1,	-1,	-1,	26,	26,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	26,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	26,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	26,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	28,	-1,	-1,	-1,	28,	28,	27,	27,	28,	28,	28,	28,	-1,	28,	-1,	28,	28,	28,	-1,	28,	-1,	28,	-1,	28,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	28},
{-1,	-1,	-1,	-1,	29,	29,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	29,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	29,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	29,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	31,	-1,	-1,	-1,	31,	31,	31,	31,	31,	31,	31,	31,	-1,	31,	-1,	31,	31,	31,	-1,	31,	-1,	31,	-1,	31,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	30,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	31},
{-1,	-1,	-1,	-1,	32,	32,	32,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	35,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	34,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	33,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	36,	37,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	38,	39,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	41,	43,	40,	42,	-1,	45,	-1,	44,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	46,	47,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	48,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	49,	50,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	51,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	53,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	52,	52,	-1,	-1,	-1,	-1,	-1,	-1,	53},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	55,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	54,	54,	54,	54,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	56,	56,	56,	56,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	57,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	58,	59,	60,	61,	-1,	-1,	-1},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	63,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	62,	62,	62,	62,	-1,	-1,	63},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	65,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	64,	65},
{-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	67,	66,	-1,	-1,	-1,	-1,	-1,	-1,	-1},





};

struct t_token {
    int intTokenCode;
    char *strTokenSourceCodeText;
    int intRow;
    int intColumn;
    struct t_token *ptrNext;
};
typedef struct t_token t_token;

extern t_token *ptrTokenList;
extern t_token *ptrCurrentToken;

struct t_stack {
    int intSymbolType;
    int intSymbolCode;
    struct t_stack *ptrNext;
};
typedef struct t_stack t_stack;
t_stack *ptrStackTop = NULL;

int intFlagSyntaxError;
int intFlagAcceptedInput;

// Prototipos de funciones
void printT(int intSymbolCode);
void printNT(int intSymbolCode);

void push(int intSymbolType, int intSymbolCode) {
    t_stack *ptrNewNode = (t_stack *)malloc(sizeof(t_stack));
    ptrNewNode->intSymbolType = intSymbolType;
    ptrNewNode->intSymbolCode = intSymbolCode;
    ptrNewNode->ptrNext = NULL;

    if(ptrStackTop == NULL) {
        ptrStackTop = ptrNewNode;
    } else {
        ptrNewNode->ptrNext = ptrStackTop;
        ptrStackTop = ptrNewNode;
    }
}

void pushNT(int intSymbolCode) {
    push(SYMBOL_TYPE_NON_TERMINAL, intSymbolCode);
}

void pushT(int intSymbolCode) {
    push(SYMBOL_TYPE_TERMINAL, intSymbolCode);
}

void pop() {
    t_stack *aux;
    if(ptrStackTop != NULL) {
        aux = ptrStackTop;
        ptrStackTop = ptrStackTop->ptrNext;
        free(aux);
    }
}

void stack_flush() {
    while(ptrStackTop != NULL)
        pop();
}
//esto deberia cambiarse    CAMBIADO
void printNT(int intSymbolCode) {
    switch(intSymbolCode) {
       case NT_S: printf("NT_S"); break;
        case NT_CompoundInstruction: printf("NT_CompoundInstruction"); break;
        case NT_InstructionBlock: printf("NT_InstructionBlock"); break;
        case NT_InstructionBlock2: printf("NT_InstructionBlock2"); break;
        case NT_Instruction: printf("NT_Instruction"); break;
        case NT_AssignInstruction: printf("NT_AssignInstruction"); break;
        case NT_IfInstruction: printf("NT_IfInstruction"); break;
        case NT_IfInstruction2: printf("NT_IfInstruction2"); break;
        case NT_WhileInstruction: printf("NT_WhileInstruction"); break;
        case NT_PrintInstruction: printf("NT_PrintInstruction"); break;
        case NT_Expression: printf("NT_Expression"); break;
        case NT_Expression2: printf("NT_Expression2"); break;
        case NT_RelationalExp: printf("NT_RelationalExp"); break;
        case NT_RelationalExp2: printf("NT_RelationalExp2"); break;
        case NT_CompoundExp: printf("NT_CompoundExp"); break;
        case NT_CompoundExp2: printf("NT_CompoundExp2"); break;
        case NT_SimpleExp: printf("NT_SimpleExp"); break;
        case NT_SimpleExp2: printf("NT_SimpleExp2"); break;
        case NT_Factor: printf("NT_Factor"); break;
        case NT_Factor2: printf("NT_Factor2"); break;
        case NT_Term: printf("NT_Term"); break;
        case NT_AdditiveOp: printf("NT_AdditiveOp"); break;
        case NT_MultiplicativeOp: printf("NT_MultiplicativeOp"); break;
        case NT_RelacionalOp: printf("NT_RelacionalOp"); break;
        case NT_LogicOp: printf("NT_LogicOp"); break;
        case NT_PowOp: printf("NT_PowOp"); break;
        case NT_Number: printf("NT_Number"); break;
        case NT_ClassInstr : printf("NT_ClassInstr "); break;
        case NT_Members: printf("NT_Members"); break;
        case NT_Members2: printf("NT_Members2"); break;
        case NT_Attribute: printf("NT_Attribute"); break;
        case NT_Method: printf("NT_Method"); break;
        case NT_DataType: printf("NT_DataType"); break;
        case NT_Parameters: printf("NT_Parameters"); break;
        case NT_Parameters2: printf("NT_Parameters2"); break;
        case NT_Access: printf("NT_Access"); break;
        default: printf("ERROR"); break;
    }
}
//esto tambien deberia cambiar  CAMBIADO
void printT(int intSymbolCode) {
    switch(intSymbolCode) {
        case TERMINAL_SYMBOL_program: printf("program"); break;
        case TERMINAL_SYMBOL_if: printf("if"); break;
        case TERMINAL_SYMBOL_else: printf("else"); break;
        case TERMINAL_SYMBOL_while: printf("while"); break;
        case TERMINAL_SYMBOL_Numeric: printf("Numeric"); break;
        case TERMINAL_SYMBOL_Real: printf("Real"); break;
        case TERMINAL_SYMBOL_Plus: printf("Plus"); break;
        case TERMINAL_SYMBOL_Minus: printf("Minus"); break;
        case TERMINAL_SYMBOL_Times: printf("Times"); break;
        case TERMINAL_SYMBOL_Division: printf("Division"); break;
        case TERMINAL_SYMBOL_Minor: printf("Minor"); break;
        case TERMINAL_SYMBOL_MinorEq: printf("MinoEq"); break;
        case TERMINAL_SYMBOL_Major: printf("Major"); break;
        case TERMINAL_SYMBOL_MajorEq: printf("MajorEq"); break;
        case TERMINAL_SYMBOL_Exclamation: printf("Exclamation"); break;
        case TERMINAL_SYMBOL_Different: printf("Different"); break;
        case TERMINAL_SYMBOL_Assign: printf("Assign"); break;
        case TERMINAL_SYMBOL_Compare: printf("Compare"); break;
        case TERMINAL_SYMBOL_AND: printf("AND"); break;
        case TERMINAL_SYMBOL_OR: printf("OR"); break;
        case TERMINAL_SYMBOL_Lbrace: printf("Lbrace"); break;
        case TERMINAL_SYMBOL_Rbrace: printf("Rbrace"); break;
        case TERMINAL_SYMBOL_Lparen: printf("Lparen"); break;
        case TERMINAL_SYMBOL_Rparen: printf("Rparen"); break;
        case TERMINAL_SYMBOL_Question: printf("Question"); break;
        case TERMINAL_SYMBOL_Semicolon: printf("Semicolon"); break;
        case TERMINAL_SYMBOL_Space: printf("Space"); break;
        case TERMINAL_SYMBOL_Tab: printf("Tab"); break;
        case TERMINAL_SYMBOL_EOL: printf("EOL"); break;
        case TERMINAL_SYMBOL_EOF: printf("EOF"); break;
        case TERMINAL_SYMBOL_ID: printf("ID"); break;
        case TERMINAL_SYMBOL_colon: printf("colon"); break;
        case TERMINAL_SYMBOL_switch: printf("switch"); break;
        case TERMINAL_SYMBOL_case: printf("case"); break;
        case TERMINAL_SYMBOL_break: printf("break"); break;
        case TERMINAL_SYMBOL_default: printf("default"); break;
        case TERMINAL_SYMBOL_Print: printf("Print"); break;
        case TERMINAL_SYMBOL_pow: printf("pow"); break;
        case TERMINAL_SYMBOL_private: printf("TERMINAL_SYMBOL_private"); break;
        case TERMINAL_SYMBOL_public: printf("TERMINAL_SYMBOL_public"); break;
        case TERMINAL_SYMBOL_INT: printf("TERMINAL_SYMBOL_INT"); break;
        case TERMINAL_SYMBOL_STRING: printf("TERMINAL_SYMBOL_STRING"); break;
        case TERMINAL_SYMBOL_BOOL: printf("TERMINAL_SYMBOL_BOOL"); break;
        case TERMINAL_SYMBOL_DATETIME: printf("TERMINAL_SYMBOL_DATETIME"); break;
        case TERMINAL_SYMBOL_class: printf("TERMINAL_SYMBOL_class"); break;
        case TERMINAL_SYMBOL_comma: printf("TERMINAL_SYMBOL_comma"); break;

        default: printf("UNKNOWN");
    }
}

void stack_print2(t_stack *stackNode) {
    if(stackNode != NULL) {
        stack_print2(stackNode->ptrNext);
        switch(stackNode->intSymbolType) {
            case SYMBOL_TYPE_TERMINAL:
                printT(stackNode->intSymbolCode);
                printf(" ");
                break;
            case SYMBOL_TYPE_NON_TERMINAL:
                printNT(stackNode->intSymbolCode);
                printf(" ");
                break;
            default:
                printf("ERROR ");
                break;
        }
    }
}

void stack_print() {
    printf("Stack: ");
    stack_print2(ptrStackTop);
    printf("\n----------------------------------------\n");
}

void input_print() {
    t_token *aux = ptrCurrentToken;
    printf("Input: ");
    while(aux != NULL) {
        printT(aux->intTokenCode);
        printf(" ");
        aux = aux->ptrNext;
    }
    printf("\n");
}

int stack_top_is_NT() {
    if(ptrStackTop != NULL) {
        return (ptrStackTop->intSymbolType == SYMBOL_TYPE_NON_TERMINAL);
    }
    return FALSE;
}
//debe cambiar tambien
void print_GrammarRule(int intGrammarRuleNumber) {
    printf("\nRule: ");
    switch(intGrammarRuleNumber) {
       case 1: printf(" S -->  program CompoundInstruction "); break;
        case 2: printf("CompoundInstruction -->{ InstructionBlock }"); break;
        case 3: printf(" InstructionBlock --> Instruction InstructionBlock2"); break;
        case 4: printf(" InstructionBlock2 --> ; Instruction InstructionBlock2"); break;
        case 5: printf("InstructionBlock2 -->  epsilon  "); break;
        case 6: printf(" Instruction --> AssignInstruction "); break;
        case 7: printf("Instruction --> IfInstruction"); break;
        case 8: printf("Instruction  --> WhileInstruction"); break;
        case 9: printf("Instruction --> PrintInstruction"); break;
        case 10: printf("Instruction --> CompoundInstruction"); break;
        case 11: printf("AssignInstruction --> ID = Expression "); break;
        case 12: printf("IfInstruction --> if (  Expression ) Instruction  IfInstruction2"); break;
        case 13: printf("IfInstruction2 --> else Instruction "); break;
        case 14: printf("IfInstruction2 --> epsilon "); break;
        case 15: printf("WhileInstruction --> while ( Expression ) Instruction"); break;
        case 16: printf("PrintInstruction --> ? Expression"); break;
        case 17: printf("Expression --> RelationalExp Expression2 "); break;
        case 18: printf("Expression2 --> LogicOp RelationalExp Expression2 "); break;
        case 19: printf("Expression2 --> epsilon"); break;
        case 20: printf("RelationalExp --> CompoundExp RelationalExp2"); break;
        case 21: printf("RelationalExp2 --> RelacionalOp CompoundExp RelationalExp2 "); break;
        case 22: printf("RelationalExp2 --> epsilon"); break;
        case 23: printf("CompoundExp --> SimpleExp CompoundExp2"); break;
        case 24: printf("CompoundExp2 --> AdditiveOp SimpleExp CompoundExp2 "); break;
        case 25: printf("CompoundExp2 --> epsilon"); break;
        case 26: printf("SimpleExp --> Factor SimpleExp2"); break;
        case 27: printf("SimpleExp2 --> MultiplicativeOp Factor SimpleExp2 "); break;
        case 28: printf("SimpleExp2 --> epsilon"); break;
        case 29: printf("Factor --> Term Factor2"); break;
        case 30: printf("Factor2 --> PowOp Term "); break;
        case 31: printf("Factor2 --> epsilon "); break;
        case 32: printf("Term --> Number "); break;
        case 33: printf("Term --> ID "); break;
        case 34: printf("Term --> ( Expression )"); break;
        case 35: printf("Term --> ! (Expression )"); break;
        case 36: printf("Term --> ( Expression )"); break;
        case 37: printf("AdditiveOp --> -"); break;
        case 38: printf("MultiplicativeOp --> *"); break;
        case 39: printf("MultiplicativeOp -->  /"); break;
        case 40: printf("RelacionalOp --> >"); break;
        case 41: printf("RelacionalOp -->  <"); break;
        case 42: printf("RelacionalOp --> >="); break;
        case 43: printf("RelacionalOp -->  <="); break;
        case 44: printf("RelacionalOp --> =="); break;
        case 45: printf("RelacionalOp --> !="); break;
        case 46: printf("LogicOp  -->  AND"); break;
        case 47: printf("LogicOp --> OR"); break;
        case 48: printf("PowOp -->  ^"); break;
        case 49: printf("Number --> IntegerNumber "); break;
        case 50: printf("Number --> RealNumber"); break;
        case 51: printf("ClassInstr --> class ID { Members }"); break;
        case 52: printf("Members --> Access ID Members2 Members "); break;
        case 53: printf(" Members -> epsilon"); break;
        case 54: printf(" Members2 --> Attribute "); break;
        case 55: printf("  Members2 --> Method"); break;
        case 56: printf("Attribute --> DataType"); break;
        case 57: printf("Method -->  (Parameters) CompoundInstruction"); break;
        case 58: printf(" DataType -->  INT"); break;
        case 59: printf("DataType --> STRING"); break;
        case 60: printf("DataType --> BOOL"); break;
        case 61: printf("DataType --> DATETIME"); break;
        case 62: printf("Parameters --> DataType ID Parameters2"); break;
        case 63: printf("Parameters --> epsilon"); break;
        case 64: printf("Parameters2 --> ,DataType ID Parameters2"); break;
        case 65: printf("Parameters2 --> epsilon"); break;
        case 66: printf("Acces --> public "); break;
        case 67: printf("Access --> private"); break;
        case 68: printf("Instruction --> ClassInstr"); break;

        default: printf("WRONG RULE"); break;
    }
}
//debe cambiar esto
void Replace_LFS_NT_by_RHS_Symbols(int intGrammarRuleNumber) {
    pop(); // Elimina el no-terminal de la cabeza de la pila
    switch(intGrammarRuleNumber) {
        case 1: // S → "program" CompoundInstruction
            pushNT(NT_CompoundInstruction);
            pushT(TERMINAL_SYMBOL_program);

            break;

        case 2: // CompoundInstruction → "{" InstructionBlock "}"
            pushT(TERMINAL_SYMBOL_Rbrace);
            pushNT(NT_InstructionBlock);
            pushT(TERMINAL_SYMBOL_Lbrace);
            break;

        case 3: // InstructionBlock → Instruction { ";" Instruction }
            pushNT(NT_InstructionBlock2);
            pushNT(NT_Instruction); // Primera instrucción (la repetición se manejaría aparte)
            break;

        case 4: // Instruction → AssignInstruction
            pushNT(NT_InstructionBlock2);
            pushNT(NT_Instruction);
            pushT(TERMINAL_SYMBOL_Semicolon);
            break;

        case 5:
            break;

        case 6: // Instruction → WhileInstruction
            pushNT(NT_AssignInstruction);
            break;

        case 7: // Instruction → PrintInstruction
            pushNT(NT_IfInstruction);
            break;

        case 8: // Instruction → CompoundInstruction
            pushNT(NT_WhileInstruction);
            break;

        case 9: // AssignInstruction → ID "=" Expression
            pushNT(NT_PrintInstruction);
            break;

        case 10:
            pushNT(NT_CompoundInstruction);
            break;

        case 11:
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_Assign);
            pushT(TERMINAL_SYMBOL_ID);
            break;

        case 12: // PrintInstruction → "?" Expression
            pushNT(NT_InstructionBlock2);  // For what comes after the entire if-else
            pushNT(NT_IfInstruction2);     // For possible else part
            pushNT(NT_Instruction);        // For the main if body
            pushT(TERMINAL_SYMBOL_Rparen);
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_Lparen);
            pushT(TERMINAL_SYMBOL_if);
            break;


        case 13:
            pushNT(NT_Instruction);
            pushT(TERMINAL_SYMBOL_else);
            break;

        case 14:
            break;

        case 15:
            pushNT(NT_Instruction);
            pushT(TERMINAL_SYMBOL_Rparen);
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_Lparen);
            pushT(TERMINAL_SYMBOL_while);
            break;

        case 16:
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_Print);
            break;

        case 17: pushNT(NT_Expression2);
                pushNT(NT_RelationalExp);
            break;

        case 18: pushNT(NT_Expression2);
                pushNT(NT_RelationalExp);
                pushNT(NT_LogicOp);
            break;

        case 19:
            break;

        case 20: pushNT(NT_RelationalExp2);
                pushNT(NT_CompoundExp);
            break;

        case 21: pushNT(NT_RelationalExp2);
                pushNT(NT_CompoundExp);
                pushNT(NT_RelacionalOp);
            break;


        case 22: break;
        case 23: pushNT(NT_CompoundExp2);
                pushNT(NT_SimpleExp);
                break;
        case 24: pushNT(NT_CompoundExp2);
                pushNT(NT_SimpleExp);
                pushNT(NT_AdditiveOp);

                    break;    // MultiplicativeOp → "*"
        case 25:
        break; // MultiplicativeOp → "/"
        case 26: pushNT(NT_SimpleExp2);
                pushNT(NT_Factor);
                break;
        case 27: pushNT(NT_SimpleExp2);
                  pushNT(NT_Factor);
                  pushNT(NT_MultiplicativeOp);
                break;
        case 28:
                break;  // RelacionalOp → ">="
        case 29: pushNT(NT_Factor2);
                 pushNT(NT_Term);
                    break;  // RelacionalOp → "<="
        case 30: pushNT(NT_Term);
                  pushNT(NT_PowOp);
                    break;  // RelacionalOp → "=="
        case 31:
                break;// RelacionalOp → "!="
        case 32: pushNT(NT_Number);
                    break;      // LogicOp → "AND"
        case 33: pushT(TERMINAL_SYMBOL_ID);
                    break;
        case 34: pushT(TERMINAL_SYMBOL_Rparen);
                 pushNT(NT_Expression);
                pushT(TERMINAL_SYMBOL_Lparen);
                break;      // PowOp → "^"
        case 35: pushT(TERMINAL_SYMBOL_Rparen);
                 pushNT(NT_Expression);
                pushT(TERMINAL_SYMBOL_Lparen);
                pushT(TERMINAL_SYMBOL_Exclamation);
                break;  // Number → IntegerNumber
        case 36: pushT(TERMINAL_SYMBOL_Plus);
                break;     // Number → RealNumber
        case 37: pushT(TERMINAL_SYMBOL_Minus);
                break;
        case 38: pushT(TERMINAL_SYMBOL_Times);
                break;
        case 39: pushT(TERMINAL_SYMBOL_Division);
                    break;
        case 40: pushT(TERMINAL_SYMBOL_Major);
                 break;
        case 41:  pushT(TERMINAL_SYMBOL_Minor);
                    break;

        case 42: pushT(TERMINAL_SYMBOL_MajorEq);
                break;
        case 43: pushT(TERMINAL_SYMBOL_MinorEq);
                    break;
        case 44: pushT(TERMINAL_SYMBOL_Compare);
                    break;
        case 45: pushT(TERMINAL_SYMBOL_Different);
                    break;
        case 46: pushT(TERMINAL_SYMBOL_AND);
                break;
        case 47: pushT(TERMINAL_SYMBOL_OR);
                break;
        case 48: pushT(TERMINAL_SYMBOL_pow);
                break;
        case 49: pushT(TERMINAL_SYMBOL_Numeric);
                break;
        case 50: pushT(TERMINAL_SYMBOL_Real);
                    break;
        case 51: pushT(TERMINAL_SYMBOL_Rbrace);
                pushNT(NT_Members);
                pushT(TERMINAL_SYMBOL_Lbrace);
                pushT(TERMINAL_SYMBOL_ID);
                pushT(TERMINAL_SYMBOL_class);
                break;
        case 52: pushNT(NT_Members);
                  pushNT(NT_Members2);
                  pushT(TERMINAL_SYMBOL_ID);
                  pushNT(NT_Access);
            break;
        case 53:
                break;
        case 54: pushNT(NT_Attribute);
            break;
        case 55: pushNT(NT_Method);
            break;
        case 56: pushT(TERMINAL_SYMBOL_Semicolon);
                pushNT(NT_DataType);
                break;
        case 57: pushNT(NT_CompoundInstruction);
                pushT(TERMINAL_SYMBOL_Rparen);
                pushNT(NT_Parameters);
                pushT(TERMINAL_SYMBOL_Lparen);
                    break;
        case 58: pushT(TERMINAL_SYMBOL_INT);
                break;
        case 59: pushT(TERMINAL_SYMBOL_STRING);
            break;
        case 60: pushT(TERMINAL_SYMBOL_BOOL);
                break;
        case 61: pushT(TERMINAL_SYMBOL_DATETIME);
                break;
        case 62: pushNT(NT_Parameters2);
                pushT(TERMINAL_SYMBOL_ID);
                pushNT(NT_DataType);
                break;
        case 63:
                break;
        case 64: pushNT(NT_Parameters2);
                pushT(TERMINAL_SYMBOL_ID);
                pushNT(NT_DataType);
                pushT(TERMINAL_SYMBOL_comma);
                break;
        case 65:
                break;
        case 66: pushT(TERMINAL_SYMBOL_public);
                break;
        case 67: pushT(TERMINAL_SYMBOL_private);
                break;
        case 68: pushNT(NT_ClassInstr);
                break;
        default:
            printf("Error: Regla gramatical no reconocida: %d\n", intGrammarRuleNumber);
            break;
    }
}

int ParserLL_ApplyGrammarRule() {
    int intGrammarRuleNumber = RM[(ptrStackTop->intSymbolCode)-1][(ptrCurrentToken->intTokenCode)-1];

    if(intGrammarRuleNumber > 0) {
        print_GrammarRule(intGrammarRuleNumber);
        Replace_LFS_NT_by_RHS_Symbols(intGrammarRuleNumber);
        return FALSE;
    } else {
        return TRUE;
    }
}

void parser_LL() {
    intFlagSyntaxError = FALSE;
    intFlagAcceptedInput = FALSE;
    ptrCurrentToken = ptrTokenList;

    pushT(TERMINAL_SYMBOL_EOF);
    pushNT(NT_S);

    do {
        printf("\n------------------------------------------\n");
        stack_print();
        input_print();

        if(stack_top_is_NT()) {
            intFlagSyntaxError = ParserLL_ApplyGrammarRule();
            if(intFlagSyntaxError == TRUE) {
                printf("\nSyntax Error=%s, Row=%d, Column=%d",
                    ptrCurrentToken->strTokenSourceCodeText,
                    ptrCurrentToken->intRow,
                    ptrCurrentToken->intColumn);
            }
        } else {
            if((ptrStackTop != NULL) && (ptrCurrentToken != NULL)) {
                if(ptrStackTop->intSymbolCode == ptrCurrentToken->intTokenCode) {
                    if(ptrStackTop->intSymbolCode == TERMINAL_SYMBOL_EOF) {
                        intFlagAcceptedInput = TRUE;
                        printf("\nInput Recognized. Syntatic analysis OK.");
                    } else {
                        printf("\nExpect.");
                        pop();
                        ptrCurrentToken = ptrCurrentToken->ptrNext;
                    }
                } else {
                    intFlagSyntaxError = TRUE;
                    printf("\nSyntax Error=%s, Row=%d, Column=%d",
                        ptrCurrentToken->strTokenSourceCodeText,
                        ptrCurrentToken->intRow,
                        ptrCurrentToken->intColumn);
                }
            } else {
                intFlagSyntaxError = TRUE;
                if(ptrStackTop == NULL) {
                    printf("\nRecognition Stack is EMPTY");
                } else {
                    printf("\nInput Sent by Scanner is Empty");
                }
            }
        }
    } while(!intFlagSyntaxError && !intFlagAcceptedInput);
}
