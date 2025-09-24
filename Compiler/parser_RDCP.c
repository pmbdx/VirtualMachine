//parser_RDCP.c
//17/03/2025 15:20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE (0)
#define TRUE (-1)

// Terminal symbols (from your defines)
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
#define TERMINAL_SYMBOL_Print 33
#define TERMINAL_SYMBOL_pow  34
#define TERMINAL_SYMBOL_CRANK 35
#define TERMINAL_SYMBOL_DROWN 36
#define TERMINAL_SYMBOL_BEEP 37
#define TERMINAL_SYMBOL_TURNON 38
#define TERMINAL_SYMBOL_TURNOFF 39
#define TERMINAL_SYMBOL_DRIGHT 40
#define TERMINAL_SYMBOL_DLEFT 41
#define TERMINAL_SYMBOL_FORWARD 42
#define TERMINAL_SYMBOL_REVERSE 43
#define TERMINAL_SYMBOL_IF_ENDOFROAD 44

// Non-terminal symbols
#define NT_Instruction 1
#define NT_InstrEngine 2
#define NT_InstrHorn 3
#define NT_InstrLights 4
#define NT_InstrDrift 5
#define NT_InstrDrive 6
#define NT_InstrIfEndOfRoad 7

// Assembly Instructions
#define A_MOV     1 // Move a value
#define A_ADV     2 // Advance 1 location
#define A_DEC     3 // Decrement Accumulator by 1
#define A_JNZ     4 // Jump if Not equal to Zero
#define A_JEZ     5 // Jump if Equal to Zero
#define A_PUSH    6 // Push to Stack
#define A_CMP     7 // Compare 2 popped values from Stack, it will subtract them
#define A_END     8 // Ends the program
#define A_DRIGHT  9 // Turn to Right
#define A_DLEFT   10 // Turn to Left
#define A_DROWN   11 // Pickup Object
#define A_CRANK   12 // Put down Object
#define A_TURNON  13 // Turn on lights
#define A_TURNOFF 14 // Turn off lights
#define A_BEEP    15 // Sound horn
#define A_FORWARD 16 // Move forward
#define A_REVERSE 17 // Move reverse

// Processor Registers
#define R_PC   1 // Program Counter
#define R_IR1  2 // Instruction Register 1
#define R_IR2  3 // Instruction Register 2
#define R_SP   4 // Stack Pointer
#define R_CRC  5 // Crash Counter
#define R_AC   6 // Advance Counter
#define R_ACC  7 // Accumulator

// Addressing Modes
#define AM_IMMEDT 1 // Immediate Addressing Mode
#define AM_DIRREG 2 // Direct to Register Addressing Mode

/*
Grammar Rules:
1) Instruction ::= InstrHorn | InstrDrift | InstrDrive | InstrIfEndOfRoad | InstrEngine | InstrLights
2) InstrEngine ::= "CRANK" | "DROWN"
3) InstrHorn ::= "BEEP" | InstrHorn "BEEP"
4) InstrLights ::= "TURNON" | "TURNOFF"
5) InstrDrift ::= "DRIGHT" | "DLEFT"
6) InstrDrive ::= "FORWARD" Num | "REVERSE" Num
7) InstrIfEndOfRoad ::= "IF_ENDOFROAD" Instruction
*/

struct t_token {
    int intTokenCode;
    char *strTokenSourceCodeText;
    int intRow;
    int intColumn;
    struct t_token *ptrNext;
};
typedef struct t_token t_token;
extern t_token *ptrTokenList;
extern t_token *ptrCurrentToken; // Pointer to current token analyzed by parser

int boolParserError;

FILE *ptrGCBinaryFile; // Pointer to Binary File for Code Generation
int PC = 0; // Program Counter to Generate Code

// Information to Solve Pending Addresses
struct t_GCPtr {
    int intPos;
    signed short sshValue;
};
typedef struct t_GCPtr t_GCPtr;

#define GC_PTR_MAX 50
t_GCPtr GCPtr[GC_PTR_MAX];
int intGCPtrNum = 0;

int CurrentToken(int intTSymbol) {
    int bolRes = FALSE;

    if (!boolParserError) {
        if (ptrCurrentToken->intTokenCode == intTSymbol) {
            bolRes = TRUE;
        } else {
            bolRes = FALSE;
        }
    }
    return bolRes;
}

void Expect(int intTSymbol) {
    if (!boolParserError) {
        if (CurrentToken(intTSymbol)) {
            printf("\nSyntactically OK Token=%s, Row=%d, Column=%d",
                   ptrCurrentToken->strTokenSourceCodeText,
                   ptrCurrentToken->intRow,
                   ptrCurrentToken->intColumn);
            ptrCurrentToken = ptrCurrentToken->ptrNext;
        } else {
            boolParserError = TRUE;
            printf("\nSyntax Error=%s, Row=%d, Column=%d",
                   ptrCurrentToken->strTokenSourceCodeText,
                   ptrCurrentToken->intRow,
                   ptrCurrentToken->intColumn);
        }
    }
}

int CurrentTokenInFirst(int intNTSymbol) {
    int boolRes = FALSE;

    if (!boolParserError) {
        switch(intNTSymbol) {
            case NT_Instruction:
                if (CurrentToken(TERMINAL_SYMBOL_BEEP)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_CRANK)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_DROWN)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_TURNON)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_TURNOFF)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_DRIGHT)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_DLEFT)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_FORWARD)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_REVERSE)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_IF_ENDOFROAD)) { boolRes=TRUE; break; }
                break;
            case NT_InstrEngine:
                if (CurrentToken(TERMINAL_SYMBOL_CRANK)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_DROWN)) { boolRes=TRUE; break; }
                break;
            case NT_InstrHorn:
                if (CurrentToken(TERMINAL_SYMBOL_BEEP)) { boolRes=TRUE; break; }
                break;
            case NT_InstrLights:
                if (CurrentToken(TERMINAL_SYMBOL_TURNON)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_TURNOFF)) { boolRes=TRUE; break; }
                break;
            case NT_InstrDrift:
                if (CurrentToken(TERMINAL_SYMBOL_DRIGHT)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_DLEFT)) { boolRes=TRUE; break; }
                break;
            case NT_InstrDrive:
                if (CurrentToken(TERMINAL_SYMBOL_FORWARD)) { boolRes=TRUE; break; }
                if (CurrentToken(TERMINAL_SYMBOL_REVERSE)) { boolRes=TRUE; break; }
                break;
            case NT_InstrIfEndOfRoad:
                if (CurrentToken(TERMINAL_SYMBOL_IF_ENDOFROAD)) { boolRes=TRUE; break; }
                break;
        }
    }

    return boolRes;
}

void GC(signed short sshByte); // GC = Generate Code
void GC_AddToVectorOfAddressesToBeUpdated(int intPos, signed short Value);
void GC_UpdatePendindAddressesToBeSolved();

void Program();
void Instruction();
void InstrEngine();
void InstrHorn();
void InstrLights();
void InstrDrift();
void InstrDrive();
void InstrIfEndOfRoad();

// 1) Program ::= Instruction; {Instruction;}
void Program() {
    if (!boolParserError) {
        Instruction();
        Expect(TERMINAL_SYMBOL_Semicolon);
        while(CurrentTokenInFirst(NT_Instruction)) {
            Instruction();
            Expect(TERMINAL_SYMBOL_Semicolon);
        }
    }
}

// 2) Instruction ::= InstrHorn | InstrDrift | InstrDrive | InstrIfEndOfRoad | InstrEngine | InstrLights
void Instruction() {
    if (!boolParserError) {
        if (CurrentTokenInFirst(NT_InstrHorn)) {
            InstrHorn();
        } else if (CurrentTokenInFirst(NT_InstrEngine)) {
            InstrEngine();
        } else if (CurrentTokenInFirst(NT_InstrLights)) {
            InstrLights();
        } else if (CurrentTokenInFirst(NT_InstrDrift)) {
            InstrDrift();
        } else if (CurrentTokenInFirst(NT_InstrDrive)) {
            InstrDrive();
        } else if (CurrentTokenInFirst(NT_InstrIfEndOfRoad)) {
            InstrIfEndOfRoad();
        }
    }
}

// 3) InstrEngine ::= "CRANK" | "DROWN"
void InstrEngine() {
    if (!boolParserError) {
        if (CurrentToken(TERMINAL_SYMBOL_CRANK)) {
            Expect(TERMINAL_SYMBOL_CRANK);
            GC(A_CRANK);
        } else {
            Expect(TERMINAL_SYMBOL_DROWN);
            GC(A_DROWN);
        }
    }
}

// 4) InstrHorn ::= "BEEP" | InstrHorn "BEEP"
void InstrHorn() {
    if (!boolParserError) {
        Expect(TERMINAL_SYMBOL_BEEP);
        GC(A_BEEP);
        while (CurrentToken(TERMINAL_SYMBOL_BEEP)) {
            Expect(TERMINAL_SYMBOL_BEEP);
            GC(A_BEEP);
        }
    }
}

// 5) InstrLights ::= "TURNON" | "TURNOFF"
void InstrLights() {
    if (!boolParserError) {
        if (CurrentToken(TERMINAL_SYMBOL_TURNON)) {
            Expect(TERMINAL_SYMBOL_TURNON);
            GC(A_TURNON);
        } else {
            Expect(TERMINAL_SYMBOL_TURNOFF);
            GC(A_TURNOFF);
        }
    }
}

// 6) InstrDrift ::= "DRIGHT" | "DLEFT"
void InstrDrift() {
    if (!boolParserError) {
        if (CurrentToken(TERMINAL_SYMBOL_DRIGHT)) {
            Expect(TERMINAL_SYMBOL_DRIGHT);
            GC(A_DRIGHT);
        } else {
            Expect(TERMINAL_SYMBOL_DLEFT);
            GC(A_DLEFT);
        }
    }
}

// 7) InstrDrive ::= "FORWARD" Num | "REVERSE" Num
void InstrDrive() {
    if (!boolParserError) {
        if (CurrentToken(TERMINAL_SYMBOL_FORWARD)) {
            Expect(TERMINAL_SYMBOL_FORWARD);
            signed short Num = (signed short)atoi(ptrCurrentToken->strTokenSourceCodeText);
            Expect(TERMINAL_SYMBOL_Numeric);
            GC(A_MOV); GC(AM_IMMEDT); GC(Num); GC(AM_DIRREG); GC(R_AC);
            signed short label = (signed short)PC;
            GC(A_MOV); GC(AM_DIRREG); GC(R_AC); GC(AM_DIRREG); GC(R_ACC);
            GC(A_FORWARD);
            GC(A_DEC);
            GC(A_MOV); GC(AM_DIRREG); GC(R_ACC); GC(AM_DIRREG); GC(R_AC);
            GC(A_JNZ); GC(label);
        } else {
            Expect(TERMINAL_SYMBOL_REVERSE);
            signed short Num = (signed short)atoi(ptrCurrentToken->strTokenSourceCodeText);
            Expect(TERMINAL_SYMBOL_Numeric);
            GC(A_MOV); GC(AM_IMMEDT); GC(Num); GC(AM_DIRREG); GC(R_AC);
            signed short label = (signed short)PC;
            GC(A_MOV); GC(AM_DIRREG); GC(R_AC); GC(AM_DIRREG); GC(R_ACC);
            GC(A_REVERSE);
            GC(A_DEC);
            GC(A_MOV); GC(AM_DIRREG); GC(R_ACC); GC(AM_DIRREG); GC(R_AC);
            GC(A_JNZ); GC(label);
        }
    }
}

// 8) InstrIfEndOfRoad ::= "IF_ENDOFROAD" Instruction  { ";" Instruction }
void InstrIfEndOfRoad() {
    if (!boolParserError) {
        Expect(TERMINAL_SYMBOL_IF_ENDOFROAD);
        // Check for crash by comparing CRC with 0
        GC(A_PUSH); GC(AM_DIRREG); GC(R_CRC);
        GC(A_PUSH); GC(AM_IMMEDT); GC(0);
        GC(A_CMP);
        // If equal to 0 (no crash), jump over the instructions block
        GC(A_JEZ); signed short LabelToBeSolved = (signed short)PC; GC(0);
        
        // Expect opening brace
        Expect(TERMINAL_SYMBOL_Lbrace);
        
        do {
            Instruction();
            if (CurrentToken(TERMINAL_SYMBOL_Semicolon)) {
                Expect(TERMINAL_SYMBOL_Semicolon);
            }
        } while (!CurrentToken(TERMINAL_SYMBOL_Rbrace));
        
        // Expect closing brace
        Expect(TERMINAL_SYMBOL_Rbrace);
        
        // Set jump destination to here (after the block)
        signed short Label = (signed short)PC;
        GC_AddToVectorOfAddressesToBeUpdated(LabelToBeSolved, Label);
    }
}

void GC(signed short sshByte) {
    if (!boolParserError) {
        size_t written = fwrite(&sshByte, sizeof(signed short), 1, ptrGCBinaryFile);
        if (written != 1) {
            printf("Error: Failed to write to binary file\n");
            boolParserError = TRUE;
            return;
        }
        PC++;
    }
}


void GC_AddToVectorOfAddressesToBeUpdated(int intPos, signed short Value) {
    GCPtr[intGCPtrNum].intPos = intPos;
    GCPtr[intGCPtrNum].sshValue = Value;
    intGCPtrNum++;
}

void GC_UpdatePendindAddressesToBeSolved() {
    for(int i=0; i<intGCPtrNum; i++) {
        fseek(ptrGCBinaryFile, (long)(GCPtr[i].intPos)*sizeof(signed short), SEEK_SET);
        fwrite(&(GCPtr[i].sshValue), sizeof(signed short), 1, ptrGCBinaryFile);
    }
}

void GC_VerifyGeneratedBinaryFile_BasicVesion(char *strGCBinaryFile) {
    signed short sshValue;
    int PC=0;

    ptrGCBinaryFile = fopen(strGCBinaryFile, "rb");

    printf("\n");
    while(fread(&sshValue, sizeof(signed short), 1, ptrGCBinaryFile) != 0) {
        printf("%d %d\n", PC++, sshValue);
    }

    fclose(ptrGCBinaryFile);
}

void GC_GetOpCode(signed short sshOpcode, char *buffer) {
    switch(sshOpcode) {
        case A_MOV: strcpy(buffer, "MOV"); break;
        case A_ADV: strcpy(buffer, "ADV"); break;
        case A_DEC: strcpy(buffer, "DEC"); break;
        case A_JNZ: strcpy(buffer, "JNZ"); break;
        case A_JEZ: strcpy(buffer, "JEZ"); break;
        case A_PUSH: strcpy(buffer, "PUSH"); break;
        case A_CMP: strcpy(buffer, "CMP"); break;
        case A_END: strcpy(buffer, "END"); break;
        case A_DRIGHT: strcpy(buffer, "DRIGHT"); break;
        case A_DLEFT: strcpy(buffer, "DLEFT"); break;
        case A_DROWN: strcpy(buffer, "DROWN"); break;
        case A_CRANK: strcpy(buffer, "CRANK"); break;
        case A_TURNON: strcpy(buffer, "TURNON"); break;
        case A_TURNOFF: strcpy(buffer, "TURNOFF"); break;
        case A_BEEP: strcpy(buffer, "BEEP"); break;
        case A_FORWARD: strcpy(buffer, "FORWARD"); break;
        case A_REVERSE: strcpy(buffer, "REVERSE"); break;
        default: strcpy(buffer, "ERR"); break;
    }
}

int GC_GetParameterNumber(signed short sshOpcode) {
    switch(sshOpcode) {
        case A_MOV: return 2;
        case A_ADV: return 0;
        case A_DEC: return 0;
        case A_JNZ: return 1;
        case A_JEZ: return 1;
        case A_PUSH: return 1;
        case A_CMP: return 0;
        case A_END: return 0;
        case A_DRIGHT: return 0;
        case A_DLEFT: return 0;
        case A_DROWN: return 0;
        case A_CRANK: return 0;
        case A_TURNON: return 0;
        case A_TURNOFF: return 0;
        case A_BEEP: return 0;
        case A_FORWARD: return 1;
        case A_REVERSE: return 1;
        default: return 0;
    }
}

int GC_GetIfUseAddressingMode(signed short sshOpcode) {
    switch(sshOpcode) {
        case A_MOV: return TRUE;
        case A_ADV: return FALSE;
        case A_DEC: return FALSE;
        case A_JNZ: return FALSE;
        case A_JEZ: return FALSE;
        case A_PUSH: return TRUE;
        case A_CMP: return FALSE;
        case A_END: return FALSE;
        case A_DRIGHT: return FALSE;
        case A_DLEFT: return FALSE;
        case A_DROWN: return FALSE;
        case A_CRANK: return FALSE;
        case A_TURNON: return FALSE;
        case A_TURNOFF: return FALSE;
        case A_BEEP: return FALSE;
        case A_FORWARD: return TRUE;
        case A_REVERSE: return TRUE;
        default: return FALSE;
    }
}

char *GC_GetVMRegister(int intRegisterNumber) {
    switch(intRegisterNumber) {
        case R_PC: return "PC";
        case R_IR1: return "IR1";
        case R_IR2: return "IR2";
        case R_SP: return "SP";
        case R_CRC: return "CRC";
        case R_AC: return "AC";
        case R_ACC: return "ACC";
        default: return "ERR";
    }
}

void GC_VerifyGeneratedBinaryFile(char *strGCBinaryFile) {
    signed short sshValor;
    int PC=0;
    int boolInstruction = TRUE;
    int intParameterNumber = 0;
    int intParameterCounter = 0;
    int boolAddressingModeUse;
    int boolVerifyAddressingMode;
    int boolVerifyOperand;
    int intAddressingMode;
    int boolPrintComma;
    char buffer[1000]; buffer[0]='\0';

    ptrGCBinaryFile = fopen(strGCBinaryFile,"rb");

    printf("================================\n");
    printf("ASSEMBLER\n");
    printf("--------------------------------\n");
    printf("Addr.\tInstr.\n");
    printf("-----\t------\n");
    while(fread(&sshValor,sizeof(signed short), 1, ptrGCBinaryFile) != 0) {
        if(boolInstruction) {
            GC_GetOpCode(sshValor, buffer);
            intParameterNumber = GC_GetParameterNumber(sshValor);
            intParameterCounter = 0;
            boolAddressingModeUse = GC_GetIfUseAddressingMode(sshValor);
            boolPrintComma=FALSE;
            if (boolAddressingModeUse) {
                boolVerifyAddressingMode = TRUE;
                boolVerifyOperand = FALSE;
            } else {
                boolVerifyAddressingMode = FALSE;
                boolVerifyOperand = TRUE;
            }
            printf("%d\t%s ",PC,buffer);
            if (intParameterNumber>0)
                boolInstruction = FALSE;
            else
                printf("\n");
        } else {
            if (boolAddressingModeUse) {
                if (boolVerifyAddressingMode) {
                    intAddressingMode = (int)sshValor;
                    boolVerifyAddressingMode = FALSE;
                    boolVerifyOperand = TRUE;
                    boolPrintComma = FALSE;
                } else {
                    switch(intAddressingMode) {
                        case AM_IMMEDT:
                            printf("%d",sshValor);
                            break;
                        case AM_DIRREG:
                            printf("%s",GC_GetVMRegister((int)sshValor));
                            break;
                        default:
                            printf("ERR(AM=%d,Valor=%d)",intAddressingMode,sshValor);
                            break;
                    }
                    intParameterCounter++;
                    boolVerifyAddressingMode = TRUE;
                    boolVerifyOperand = FALSE;
                    boolPrintComma=TRUE;
                }
            } else {
                printf("%d",sshValor);
                intParameterCounter++;
                boolPrintComma=TRUE;
            }

            if(intParameterCounter==intParameterNumber) {
                printf("\n");
                boolInstruction=TRUE;
            } else {
                if(boolPrintComma)
                    printf(", ");
            }
        }
        PC++;
    }
    printf("\n");
    fclose(ptrGCBinaryFile);
}

void parser_RDCP() {
    boolParserError = FALSE;
    ptrCurrentToken = ptrTokenList;

    ptrGCBinaryFile = fopen("../object.bin", "wb");
    if (ptrGCBinaryFile == NULL) {
        printf("Error: Could not open file for writing\n");
        return;
    }


    Program();
    GC(A_END);

    GC_UpdatePendindAddressesToBeSolved();

    fclose(ptrGCBinaryFile);

    GC_VerifyGeneratedBinaryFile("../object.bin");
}