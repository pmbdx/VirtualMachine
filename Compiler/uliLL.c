#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//parser_LL.c

#define FALSE (0)
#define TRUE (-1)

#define SYMBOL_TYPE_NON_TERMINAL 1
#define SYMBOL_TYPE_TERMINAL     2

#define TERMINAL_SYMBOL_program 1
#define TERMINAL_SYMBOL_if 2
#define TERMINAL_SYMBOL_else 3
#define TERMINAL_SYMBOL_while 4
#define TERMINAL_SYMBOL_AND 5
#define TERMINAL_SYMBOL_OR 6
#define TERMINAL_SYMBOL_lbrace 7
#define TERMINAL_SYMBOL_rbrace 8
#define TERMINAL_SYMBOL_equal 9
#define TERMINAL_SYMBOL_lparen 10
#define TERMINAL_SYMBOL_rparen 11
#define TERMINAL_SYMBOL_print 12
#define TERMINAL_SYMBOL_not 13
#define TERMINAL_SYMBOL_plus 14
#define TERMINAL_SYMBOL_minus 15
#define TERMINAL_SYMBOL_mult 16
#define TERMINAL_SYMBOL_div 17
#define TERMINAL_SYMBOL_gt 18
#define TERMINAL_SYMBOL_lt 19
#define TERMINAL_SYMBOL_eq 20
#define TERMINAL_SYMBOL_ge 21
#define TERMINAL_SYMBOL_le 22
#define TERMINAL_SYMBOL_ne 23
#define TERMINAL_SYMBOL_pow 24
#define TERMINAL_SYMBOL_intergernumber 25
#define TERMINAL_SYMBOL_realnumber 26
#define TERMINAL_SYMBOL_ID 27
#define TERMINAL_SYMBOL_SemiColon 28
#define TERMINAL_SYMBOL_Space 29
#define TERMINAL_SYMBOL_Tab 30
#define TERMINAL_SYMBOL_EOL 31
#define TERMINAL_SYMBOL_EOF 32
#define TERMINAL_SYMBOL_EQUAL 33
#define TERMINAL_SYMBOL_switch 34
#define TERMINAL_SYMBOL_case 35
#define TERMINAL_SYMBOL_colon 36
#define TERMINAL_SYMBOL_default 37
#define TERMINAL_SYMBOL_break 38

#define NT_S 1
#define NT_CompoundInstruction 2
#define NT_InstructionBlock 3
#define NT_InstructionBlock2 4
#define NT_Instruction 5
#define NT_AssignInstr 6
#define NT_IfInstr 7
#define NT_ElseInstr 8
#define NT_WhileInstr 9
#define NT_PrintInstr 10
#define NT_Expression 11
#define NT_Expression2 12
#define NT_RelationalExp 13
#define NT_RelationalExp2 14
#define NT_CompoundExp 15
#define NT_CompoundExp2 16
#define NT_SimpleExp 17
#define NT_SimpleExp2 18
#define NT_Factor 19
#define NT_Term 20
#define NT_Number 21
#define NT_SwitchInstr 22
#define NT_CaseList 23
#define NT_CaseStatement 24
#define NT_BreakInstr 25


#define NT_SYMBOL_NUMMAX 26
#define T_SYMBOL_NUMMAX 38

int RM[NT_SYMBOL_NUMMAX][T_SYMBOL_NUMMAX] = {
/*  1  2   3   4   5    6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32 33 34 35 36 37 38*/
{  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1,-1,-1,-1},
{ -1,  3, -1,  3, -1, -1,  3, -1, -1, -1, -1,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  3, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5,  5,  5, -1 ,-1,-1, 5, 5, 5, 5},
{ -1,  7, -1,  8, -1, -1, 10, -1, -1, -1, -1,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  6, -1, -1, -1, -1, -1, -1,45,-1,-1,-1,46},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, 13, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, 14, 14, 14, 14 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, 17, 17, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, 20, -1, 19, 18, -1, 20, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, 20, 20, 20, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, 21, 21, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, 28, -1, 28, 28, -1, 28, -1, -1, 28, -1, -1, -1, -1, -1, -1, 22, 23, 26, 24, 25, 27, -1, -1, -1, -1, 28, 28, 27, 28, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, 29, 29, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, 32, -1, 32, 32, -1, 32, -1, -1, 32, -1, -1, 30, 31, -1, 32, 32, 32, 32, 32, 32, -1, -1, -1, -1, -1, 32, 32, 31, 32, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, 33, 33, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, 36, -1, 36, 36, -1, 36, -1, -1, 36, -1, -1, 36, 36, 34, 35, 36, 36, 36, 36, 36, 36, -1, -1, -1, -1, 36, 36, 36, 36, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, -1, -1, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, 38, 38, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 41, -1, -1, 42, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 39, 44, 40, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 43, 44, -1, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1,47,-1,-1,-1,-1},
{ -1, -1, -1, -1, -1, -1, -1, 49, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1,-1,48,-1,48,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1,-1,50,-1,51,-1},
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1,-1,-1,-1,-1,52},
};


struct t_token
{
    int intTokenCode;
    char *strTokenSourceCodeText;
    int intRow;
    int intColumn;
    struct t_token *ptrNext;
};
typedef struct t_token t_token;
t_token *ptrTokenList;
t_token *ptrCurrentToken; //Pointer to current token analyzed by parser

//Recognition Stack
struct t_stack {
    int intSymbolType; //Terminal or Non-Terminal symbol
    int intSymbolCode; //Code in define
    struct t_stack *ptrNext;
};
typedef struct t_stack t_stack;
t_stack *ptrStackTop = NULL;

int intFlagSyntaxError;
int intFlagAcceptedInput;
int boolParserError;

void push(int intSymbolType, int intSymbolCode)
{
    t_stack *ptrNewNode = (t_stack *)malloc(sizeof(t_stack));
    ptrNewNode->intSymbolType = intSymbolType;
    ptrNewNode->intSymbolCode = intSymbolCode;
    ptrNewNode->ptrNext = NULL;

    if (ptrStackTop == NULL) //Stack is empty
    {
        ptrStackTop = ptrNewNode;
    }//if
    else //Stack Is Not Empty
    {
        ptrNewNode->ptrNext = ptrStackTop;
        ptrStackTop = ptrNewNode;
    }//else
}//push

void pushNT(int intSymbolCode)
{
    push(SYMBOL_TYPE_NON_TERMINAL, intSymbolCode);
}//pushNT

void pushT(int intSymbolCode)
{
    push(SYMBOL_TYPE_TERMINAL, intSymbolCode);
}//pushT

void pop()
{
    t_stack *aux;

    if(ptrStackTop != NULL) //Stack is not Empty
    {
        aux = ptrStackTop;
        ptrStackTop = ptrStackTop->ptrNext;
        free(aux);
    }//if
}//pop

void stack_flush()
{
    while(ptrStackTop != NULL)
        pop();
}//stack_flush

void printT(int intSymbolCode)
{//Terminal Symbol Print Function
    switch(intSymbolCode)
    {
        case TERMINAL_SYMBOL_program:
            printf("TERMINAL_SYMBOL_program");
        break;
        case TERMINAL_SYMBOL_if:
            printf("TERMINAL_SYMBOL_if");
        break;
        case  TERMINAL_SYMBOL_else:
            printf("TERMINAL_SYMBOL_else");
        break;
        case  TERMINAL_SYMBOL_while:
            printf("TERMINAL_SYMBOL_while");
        break;
        case  TERMINAL_SYMBOL_AND:
            printf("TERMINAL_SYMBOL_AND");
        break;
        case  TERMINAL_SYMBOL_OR:
            printf("TERMINAL_SYMBOL_OR");
        break;
        case  TERMINAL_SYMBOL_lbrace:
            printf("TERMINAL_SYMBOL_lbrace");
        break;
        case  TERMINAL_SYMBOL_rbrace:
            printf("TERMINAL_SYMBOL_rbrace");
        break;
        case  TERMINAL_SYMBOL_equal:
            printf("TERMINAL_SYMBOL_equal");
        break;
        case  TERMINAL_SYMBOL_lparen:
            printf("TERMINAL_SYMBOL_lparen");
        break;
        case  TERMINAL_SYMBOL_rparen:
            printf("TERMINAL_SYMBOL_rparen");
        break;
        case  TERMINAL_SYMBOL_print:
            printf("TERMINAL_SYMBOL_print");
        break;
        case  TERMINAL_SYMBOL_not:
            printf("TERMINAL_SYMBOL_not");
        break;
        case  TERMINAL_SYMBOL_plus:
            printf("TERMINAL_SYMBOL_plus");
        break;
        case  TERMINAL_SYMBOL_minus:
            printf("TERMINAL_SYMBOL_minus");
        break;
        case  TERMINAL_SYMBOL_div:
            printf("TERMINAL_SYMBOL_div");
        break;
        case  TERMINAL_SYMBOL_gt:
            printf("TERMINAL_SYMBOL_gt");
        break;
        case  TERMINAL_SYMBOL_lt:
            printf("TERMINAL_SYMBOL_lt");
        break;
        case  TERMINAL_SYMBOL_eq:
            printf("TERMINAL_SYMBOL_eq");
        break;
        case  TERMINAL_SYMBOL_ge:
            printf("TERMINAL_SYMBOL_ge");
        break;
        case  TERMINAL_SYMBOL_le:
            printf("TERMINAL_SYMBOL_le");
        break;
        case  TERMINAL_SYMBOL_ne:
            printf("TERMINAL_SYMBOL_ne");
        break;
        case  TERMINAL_SYMBOL_pow:
            printf("TERMINAL_SYMBOL_pow");
        break;
        case  TERMINAL_SYMBOL_intergernumber:
            printf("TERMINAL_SYMBOL_integernumber");
        break;
        case  TERMINAL_SYMBOL_realnumber:
            printf("TERMINAL_SYMBOL_realnumber");
        break;
        case  TERMINAL_SYMBOL_ID:
            printf("TERMINAL_SYMBOL_ID");
        break;
        case  TERMINAL_SYMBOL_SemiColon:
            printf("TERMINAL_SYMBOL_SemiColon");
        break;
        case  TERMINAL_SYMBOL_Space:
            printf("TERMINAL_SYMBOL_Space");
        break;
        case  TERMINAL_SYMBOL_Tab:
            printf("TERMINAL_SYMBOL_Tab");
        break;
        case  TERMINAL_SYMBOL_EOL:
            printf("TERMINAL_SYMBOL_EOL");
        break;
        case  TERMINAL_SYMBOL_EOF:
            printf("TERMINAL_SYMBOL_EOF");
        break;
       case  TERMINAL_SYMBOL_switch:
            printf("TERMINAL_SYMBOL_switch");
        break;
        case  TERMINAL_SYMBOL_case:
            printf("TERMINAL_SYMBOL_case");
        break;
        case  TERMINAL_SYMBOL_colon:
            printf("TERMINAL_SYMBOL_colon");
        break;
        case  TERMINAL_SYMBOL_default:
            printf("TERMINAL_SYMBOL_defualt");
        break;
        case  TERMINAL_SYMBOL_break:
            printf("TERMINAL_SYMBOL_break");
        break;
        default:
            printf("ERROR");
        break;
    }//switch
}//printT

void printNT(int intSymbolCode)
{
    switch(intSymbolCode)
    {
                case NT_S:
            printf("NT_S");
            break;
        case NT_CompoundInstruction:
            printf("NT_CompoundInstruction");
            break;
        case NT_InstructionBlock:
            printf("NT_InstructionBlock");
            break;
        case NT_InstructionBlock2:
            printf("NT_InstructionBlock2");
            break;
        case NT_Instruction:
            printf("NT_Instruction");
            break;
        case NT_AssignInstr:
            printf("NT_AssignInstr");
            break;
        case NT_IfInstr:
            printf("NT_IfInstr");
            break;
        case NT_ElseInstr:
            printf("NT_ElseInstr");
            break;
        case NT_WhileInstr:
            printf("NT_WhileInstr");
            break;
        case NT_PrintInstr:
            printf("NT_PrintInstr");
            break;
        case NT_Expression:
            printf("NT_Expression");
            break;
        case NT_Expression2:
            printf("NT_Expression2");
            break;
        case NT_RelationalExp:
            printf("NT_RelationalExp");
            break;
        case NT_RelationalExp2:
            printf("NT_RelationalExp2");
            break;
        case NT_CompoundExp:
            printf("NT_CompoundExp");
            break;
        case NT_CompoundExp2:
            printf("NT_CompoundExp2");
            break;
        case NT_SimpleExp:
            printf("NT_SimpleExp");
            break;
        case NT_SimpleExp2:
            printf("NT_SimpleExp2");
            break;
        case NT_Factor:
            printf("NT_Factor");
            break;
        case NT_Term:
            printf("NT_Term");
            break;
        case NT_Number:
            printf("NT_Number");
            break;
        case NT_SwitchInstr: printf("NT_SwitchInstr"); break;
        case NT_CaseList: printf("NT_CaseList"); break;
        case NT_CaseStatement: printf("NT_CaseStatement"); break;
        case NT_BreakInstr: printf("NT_BreakInstr"); break;
        default:
            printf("ERROR");
            break;

    }//switch
}//printNT

void stack_print2(t_stack *stackNode)
{
    if(stackNode != NULL) //No more elements in stack traversing
    {
        stack_print2(stackNode->ptrNext);
        switch(stackNode->intSymbolType)
        {
            case SYMBOL_TYPE_TERMINAL:
                printT(stackNode->intSymbolCode);
                printf(" ",stackNode->intSymbolCode);
                break;
            case SYMBOL_TYPE_NON_TERMINAL:
                printNT(stackNode->intSymbolCode);
                printf(" ",stackNode->intSymbolCode);
                break;
            default:
                printf(" ERROR ");
                break;
        }//switch
    }//if
}//stack_print2

void stack_print()
{
    printf("Stack: ");
    stack_print2(ptrStackTop);
    printf("\n");
    printf("-------------------------------------------\n");
}//stack_print

void input_print()
{
    t_token *aux = ptrCurrentToken;

    printf("Input: ");
    while(aux!=NULL)
    {
        printT(aux->intTokenCode);
        printf(" ",aux->intTokenCode);
        aux = aux->ptrNext;
    }//while
    printf("\n");
}//input_print

int stack_top_is_NT()
{
    int boolRes = FALSE;

    if (ptrStackTop != NULL) //Stack is NOT empty
    {
        if(ptrStackTop->intSymbolType == SYMBOL_TYPE_NON_TERMINAL)
            boolRes = TRUE;
    }//if

    return boolRes;
}//stack_top_is_NT

void print_GrammarRule(int intGrammarRuleNumber)
{
    printf("\nRule: ");
    switch(intGrammarRuleNumber)
    {
        case 1: printf("1) S -> program CompoundInstruction"); break;
        case 2: printf("2) CompoundInstruction -> { InstructionBlock }"); break;
        case 3: printf("3) InstructionBlock -> Instruction InstructionBlock2"); break;
        case 4: printf("4) InstructionBlock2 -> ; Instruction InstructionBlock2"); break;
        case 5: printf("5) InstructionBlock2 -> epsilon"); break;
        case 6: printf("6) Instruction -> AssignInstruction"); break;
        case 7: printf("7) Instruction -> IfInstruction"); break;
        case 8: printf("8) Instruction -> WhileInstruction"); break;
        case 9: printf("9) Instruction -> PrintInstruction"); break;
        case 10: printf("10) Instruction -> CompoundInstruction"); break;
        case 11: printf("11) AssignInstruction -> ID = Expression"); break;
        case 12: printf("12) IfInstruction -> if ( Expression ) Instruction ElseInstruction"); break;
        case 13: printf("13) ElseInstruction -> else Instruction"); break;
        case 14: printf("14) ElseInstruction -> epsilon"); break;
        case 15: printf("15) WhileInstruction -> while ( Expression ) Instruction"); break;
        case 16: printf("16) PrintInstruction -> ? Expression"); break;
        case 17: printf("17) Expression -> RelationalExp Expression2"); break;
        case 18: printf("18) Expression2 -> OR RelationalExp Expression2"); break;
        case 19: printf("19) Expression2 -> AND RelationalExp Expression2"); break;
        case 20: printf("20) Expression2 -> epsilon"); break;
        case 21: printf("21) RelationalExp -> CompoundExp RelationalExp2"); break;
        case 22: printf("22) RelationalExp2 -> > CompoundExp RelationalExp2"); break;
        case 23: printf("23) RelationalExp2 -> < CompoundExp RelationalExp2"); break;
        case 24: printf("24) RelationalExp2 -> >= CompoundExp RelationalExp2"); break;
        case 25: printf("25) RelationalExp2 -> <= CompoundExp RelationalExp2"); break;
        case 26: printf("26) RelationalExp2 -> == CompoundExp RelationalExp2"); break;
        case 27: printf("27) RelationalExp2-> != CompoundExp RelationalExp2"); break;
        case 28: printf("28) RelationalExp2 -> epsilon"); break;
        case 29: printf("29) CompoundExp -> SimpleExp CompoundExp2"); break;
        case 30: printf("30) CompoundExp2 -> + SimpleExp CompoundExp2"); break;
        case 31: printf("31) CompoundExp2 -> - SimpleExp CompoundExp2"); break;
        case 32: printf("32) CompoundExp2 -> epsilon"); break;
        case 33: printf("33) SimpleExp -> Factor SimpleExp2"); break;
        case 34: printf("34) SimpleExp2 -> * Factor SimpleExp2"); break;
        case 35: printf("35) SimpleExp2 -> / Factor SimpleExp2"); break;
        case 36: printf("36) SimpleExp2 -> epsilon"); break;
        case 37: printf("37) Factor -> Term PowOP Term"); break;
        case 38: printf("38) Factor -> Term"); break;
        case 39: printf("39) Term -> Number"); break;
        case 40: printf("40) Term -> ID"); break;
        case 41: printf("41) Term -> ( Expression )"); break;
        case 42: printf("42) Term -> ! ( Expression )"); break;
        case 43: printf("43) Number -> IntegerNumber"); break;
        case 44: printf("44) Number -> RealNumber"); break;
        case 45: printf("45) Instruction -> SwitchInstr"); break;
        case 46: printf("46) Instruction -> BreakInstr"); break;
        case 47: printf("47) SwitchInstr -> switch ( ID ) { CaseList }"); break;
        case 48: printf("48) CaseList -> CaseStatement CaseList"); break;
        case 49: printf("49) CaseList -> epsilon"); break;
        case 50: printf("50) CaseStatement -> case IntegerNumber : InstructionBlock"); break;
        case 51: printf("51) CaseStatement -> default : InstructionBlock"); break;
        case 52: printf("52) BreakInstr -> break"); break;
        default: printf("Wrong Rule"); break;

    }//switch
}//print_GrammarRule

void Replace_LHS_NT_by_RHS_Symbols(int intGrammarRuleNumber)
{
    pop(); // Pop NT at Stack Top

    switch(intGrammarRuleNumber)
    {
        case 1: //1) S -> program CompoundInstruction
            pushNT(NT_CompoundInstruction);
            pushT(TERMINAL_SYMBOL_program);
            break;
        case 2: //"2) CompoundInstruction -> { InstructionBlock }
            pushT(TERMINAL_SYMBOL_rbrace);
            pushNT(NT_InstructionBlock);
            pushT(TERMINAL_SYMBOL_lbrace);
            break;
        case 3: //3) InstructionBlock -> Instruction InstructionBlock2
            pushNT(NT_InstructionBlock2);
            pushNT(NT_Instruction);
            break;
        case 4: //4) InstructionBlock2 -> ; Instruction InstructionBlock2
            pushNT(NT_InstructionBlock2);
            pushNT(NT_Instruction);
            pushT(TERMINAL_SYMBOL_SemiColon);
            break;
        case 5:
            break; // ε
        case 6: //6) Instruction -> AssignInstruction
            pushNT(NT_AssignInstr);
            break;
        case 7: //7) Instruction -> IfInstruction
            pushNT(NT_IfInstr);
            break;
        case 8: //8) Instruction -> WhileInstruction
            pushNT(NT_WhileInstr);
            break;
        case 9: //9) Instruction -> PrintInstruction
            pushNT(NT_PrintInstr);
            break;
        case 10: //10) Instruction -> CompoundInstruction
            pushNT(NT_CompoundInstruction);
            break;
        case 11: //11) AssignInstruction -> ID = Expression
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_equal);
            pushT(TERMINAL_SYMBOL_ID);
            break;
        case 12: //12) IfInstruction -> if ( Expression ) Instruction ElseInstruction
            pushNT(NT_ElseInstr);
            pushNT(NT_Instruction);
            pushT(TERMINAL_SYMBOL_rparen);
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_lparen);
            pushT(TERMINAL_SYMBOL_if);
            break;
        case 13: //13) ElseInstruction -> else Instruction
            pushNT(NT_Instruction);
            pushT(TERMINAL_SYMBOL_else);
            break;
        case 14:
            break; // ε
        case 15: //15) WhileInstruction -> while ( Expression ) Instruction
            pushNT(NT_Instruction);
            pushT(TERMINAL_SYMBOL_rparen);
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_lparen);
            pushT(TERMINAL_SYMBOL_while);
            break;
       case 16: //16) PrintInstruction -> ? Expression
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_print);
            /*case 16: // PrintInstruction -> ? Expression ;
            pushT(TERMINAL_SYMBOL_SemiColon);
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_print);*/
            break;
        case 17: //17) Expression -> RelationalExp Expression2
            pushNT(NT_Expression2);
            pushNT(NT_RelationalExp);
            break;
        case 18://18) Expression2 -> OR RelationalExp Expression2
             pushNT(NT_Expression2);
             pushNT(NT_RelationalExp);
             pushT(TERMINAL_SYMBOL_OR);
             break;
        case 19: //19) Expression2 -> AND RelationalExp Expression2
            pushNT(NT_Expression2);
            pushNT(NT_RelationalExp);
            pushT(TERMINAL_SYMBOL_AND);
             break;
        case 20:
            break; // ε
        case 21: //21) RelationalExp -> CompoundExp RelationalExp2
            pushNT(NT_RelationalExp2);
            pushNT(NT_CompoundExp);
            break;
        case 22: //22) RelationalExp2 -> > CompoundExp RelationalExp2
            pushNT(NT_RelationalExp2);
            pushNT(NT_CompoundExp);
            pushT(TERMINAL_SYMBOL_gt);
            break;
        case 23: //23) RelationalExp2 -> < CompoundExp RelationalExp2
            pushNT(NT_RelationalExp2);
            pushNT(NT_CompoundExp);
            pushT(TERMINAL_SYMBOL_lt);
            break;
        case 24: //24) RelationalExp2 -> >= CompoundExp RelationalExp2
            pushNT(NT_RelationalExp2);
            pushNT(NT_CompoundExp);
            pushT(TERMINAL_SYMBOL_ge);
            break;
        case 25: //25) RelationalExp2 -> <= CompoundExp RelationalExp2
            pushNT(NT_RelationalExp2);
            pushNT(NT_CompoundExp);
            pushT(TERMINAL_SYMBOL_le);
            break;
        case 26: //26) RelationalExp2 -> == CompoundExp RelationalExp2
            pushNT(NT_RelationalExp2);
            pushNT(NT_CompoundExp);
            pushT(TERMINAL_SYMBOL_eq);
            break;
        case 27: //27) RelationalExp2-> != CompoundExp RelationalExp2
            pushNT(NT_RelationalExp2);
            pushNT(NT_CompoundExp);
            pushT(TERMINAL_SYMBOL_ne);
            break;
        case 28: //
            break; // ε
        case 29: //"29) CompoundExp -> SimpleExp CompoundExp2
            pushNT(NT_CompoundExp2);
            pushNT(NT_SimpleExp);
            break;
        case 30: //30) CompoundExp2 -> + SimpleExp CompoundExp2
            pushNT(NT_CompoundExp2);
            pushNT(NT_SimpleExp);
            pushT(TERMINAL_SYMBOL_plus);
            break;
        case 31: //31) CompoundExp2 -> - SimpleExp CompoundExp2
            pushNT(NT_CompoundExp2);
            pushNT(NT_SimpleExp);
            pushT(TERMINAL_SYMBOL_minus);
            break;
        case 32: //
            break; // ε
        case 33: //33) SimpleExp -> Factor SimpleExp2
            pushNT(NT_SimpleExp2);
            pushNT(NT_Factor);
            break;
        case 34: //34) SimpleExp2 -> * Factor SimpleExp2
            pushNT(NT_SimpleExp2);
            pushNT(NT_Factor);
            pushT(TERMINAL_SYMBOL_mult);
            break;
        case 35: //35) SimpleExp2 -> / Factor SimpleExp2
            pushNT(NT_SimpleExp2);
            pushNT(NT_Factor);
            pushT(TERMINAL_SYMBOL_div);
            break;
        case 36: //
            break; // ε
        case 37: //37) Factor -> Term PowOP Term
            pushNT(NT_Term);
            pushT(TERMINAL_SYMBOL_pow);
            pushNT(NT_Term);
            break;
        case 38: //38) Factor -> Term");
            pushNT(NT_Term);
            break;
        case 39: //39) Term -> Number
            pushNT(NT_Number);
            break;
        case 40: //40) Term -> ID
            pushT(TERMINAL_SYMBOL_ID);
            break;
        case 41: //41) Term -> ( Expression )
            pushT(TERMINAL_SYMBOL_rparen);
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_lparen);
            break;
        case 42: //42) Term -> ! ( Expression )
            pushT(TERMINAL_SYMBOL_rparen);
            pushNT(NT_Expression);
            pushT(TERMINAL_SYMBOL_lparen);
            pushT(TERMINAL_SYMBOL_not);
            break;
        case 43://43) Number -> IntegerNumber
            pushT(TERMINAL_SYMBOL_intergernumber);
            break;
        case 44: //44) Number -> RealNumber
            pushT(TERMINAL_SYMBOL_realnumber);
            break;
        case 45: // Instruction -> SwitchInstr
            pushNT(NT_SwitchInstr);
            break;
        case 46: // Instruction -> BreakInstr
            pushNT(NT_BreakInstr);
            break;
        case 47: // SwitchInstr -> switch ( ID ) { CaseList }
            pushT(TERMINAL_SYMBOL_rbrace);
            pushNT(NT_CaseList);
            pushT(TERMINAL_SYMBOL_lbrace);
            pushT(TERMINAL_SYMBOL_rparen);
            pushT(TERMINAL_SYMBOL_ID);
            pushT(TERMINAL_SYMBOL_lparen);
            pushT(TERMINAL_SYMBOL_switch);
            break;
        case 48: // CaseList -> CaseStatement CaseList
            pushNT(NT_CaseList);
            pushNT(NT_CaseStatement);
            break;
        case 49: // CaseList -> ε
            break;
        case 50: // CaseStatement -> case IntegerNumber : InstructionBlock
            pushNT(NT_InstructionBlock);
            pushT(TERMINAL_SYMBOL_colon);
            pushT(TERMINAL_SYMBOL_intergernumber);
            pushT(TERMINAL_SYMBOL_case);
            break;
        case 51: // CaseStatement -> default : InstructionBlock
            pushNT(NT_InstructionBlock);
            pushT(TERMINAL_SYMBOL_colon);
            pushT(TERMINAL_SYMBOL_default);
            break;
        case 52: // BreakInstr -> break
            pushT(TERMINAL_SYMBOL_break);
    break;
        default://
            break;
    }
}


int ParserLL_ApplyGrammarRule()
{
    //We return TRUE if there is an ERROR.
    int intGrammarRuleNumber;
    int intRes = FALSE;

    //Get the Grammar Rule Number from Recognition Table
    intGrammarRuleNumber =
       RM[(ptrStackTop->intSymbolCode)-1][(ptrCurrentToken->intTokenCode)-1];

    if (intGrammarRuleNumber > 0) //Is a valid grammar rule
    {
        print_GrammarRule(intGrammarRuleNumber);
        Replace_LHS_NT_by_RHS_Symbols(intGrammarRuleNumber);
        // LHS -> RHS  // Left Hand Side -> Right Hand Side
    }//if
    else
        intRes = TRUE; //There is an ERROR because the cell is EMPTY

    return intRes;
}//ParserLL_ApplyGrammarRule

void parser_LL()
{
    intFlagSyntaxError = FALSE;
    intFlagAcceptedInput = FALSE;

    //It's initialized the CurrentToken pointer to the Head List
    //sent by the scanner
    ptrCurrentToken = ptrTokenList;

    //Stack initial condition
    pushT(TERMINAL_SYMBOL_EOF);
    pushNT(NT_S);

    do
    {
        printf("\n----------------------------------------------\n");
        stack_print();
        input_print();

        if(stack_top_is_NT())
        { //We use de Recognition Table
            //Apply the Grammar Rule from Recog. Table
            //It will return TRUE if there is an error
            intFlagSyntaxError = ParserLL_ApplyGrammarRule();
            if (intFlagSyntaxError == TRUE)
            {
                printf("\nSyntax Error=%s, Row=%d, Column=%d",
                       ptrCurrentToken->strTokenSourceCodeText,
                       ptrCurrentToken->intRow,
                       ptrCurrentToken->intColumn);
            }//if
        }//if
        else
        { //Stack top is T
            //If the stack is not empty and input is not empty
            if ((ptrStackTop != NULL) && (ptrCurrentToken!=NULL))
            {
                //If stack top token and current token are same
                if (ptrStackTop->intSymbolCode == ptrCurrentToken->intTokenCode)
                {
                    //If stack top and current token are EOF ($)
                    if (ptrStackTop->intSymbolCode == TERMINAL_SYMBOL_EOF)
                    {
                        //All input is OK
                        intFlagAcceptedInput = TRUE;
                        printf("\nRecognized input. Syntactic Analysis OK.");
                    }//if
                    else //Else stack top and current token are different from EOF
                    {//EXPECT
                        printf("\nEXPECT.");
                        //Pop from stack
                        pop();
                        //Advance to the next input token
                        ptrCurrentToken = ptrCurrentToken->ptrNext;
                    }//else
                } //if
                else //Else Syntax Error
                {//Different elements at stack top and current token
                    intFlagSyntaxError = TRUE;
                    printf("\nSyntax Error=%s, Row=%d, Column=%d",
                           ptrCurrentToken->strTokenSourceCodeText,
                           ptrCurrentToken->intRow,
                           ptrCurrentToken->intColumn);
                }//else
            }//if
            else //Else Syntax Error
            {
                intFlagSyntaxError = TRUE;
                if(ptrStackTop == NULL)
                    printf("\nRecognition Stack is EMPTY");
                else
                    printf("\nInput Sent by Scanner is EMPTY");
            }//else
        }//else
    }while(!intFlagSyntaxError && !intFlagAcceptedInput);
}//paser_LL
