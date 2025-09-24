using System;
using System.IO;
using UnityEngine;
using UnityEngine.Rendering;

public class VirtualMachine
{
    // ... (todo el código de la máquina virtual que proporcionaste)
    // Nota: Es posible que necesites hacer algunos ajustes menores para que funcione
    public const int TRUE = -1;
    public const int FALSE = 0;

    //Assembly Instructions
    public const int A_MOV = 1; //Move a value
    public const int A_ADV = 2; //Advance 1 location
    public const int A_DEC = 3; //Decrement Accumulator by 1
    public const int A_JNZ = 4; //Jump if Not equal to Zero
    public const int A_JEZ = 5; //Jump if Equal to Zero
    public const int A_PUSH = 6; //Push to Stack
    public const int A_CMP = 7; //Compare 2 popped values from Stack, it will sustract them,
    //Change condition flags <0 >0 =0
    public const int A_END = 8; //Ends the program
    public const int A_TRIGHT = 9; //Turn to Right
    public const int A_TLEFT = 10; //Turn to Left
    public const int A_DROWN = 11; //DROWN engine
    public const int A_REV = 12; //CRANK engine
    public const int A_LIGHTON = 13; //Lights on
    public const int A_LIGHTOFF = 14; //Lights oFF
    public const int A_HONK = 15; //HONK
    public const int A_FRWRD = 16; //Forward
    public const int A_BACK = 17; //Back

    //Processor Registers
    public const int R_PC = 1;  //Program Counter
    public const int R_IR1 = 2; //Instruction Register 1
    public const int R_IR2 = 3; //Instruction Register 2
    public const int R_SP = 4;  //Stack Pointer
    public const int R_CRC = 5; //Crash Counter
    public const int R_AC = 6;  //Advance Counter
    public const int R_ACC = 7; //Accumulator

    //Addressing Modes
    public const int AM_IMMEDT = 1; //Immediate Addressing Mode
    public const int AM_DIRREG = 2; //Direct to Register Addressing Mode

    //Processor Registers
    public int PC { get; set; } = 0;    //Program Counter
    private int _IR1 = 0;
    public int IR1
    {
        set
        {
            this._IR1 = value;
        }
        get
        {
            return this._IR1;
        }
    }    //Instruction Register 1
    public int IR2 = 0;    //Instruction Register 2
    public int SP = 0;    //Stack Pointer
    public int CRC = 0;    //Crash Counter
    public int AC = 0;     //Advance Counter
    public int ACC = 0;    //Accumulator

    public const int MEMORY_MAX_SIZE = 511;
    public int[] mem = new int[MEMORY_MAX_SIZE];

    public const int STACK_MAX_SIZE = 128;
    public int[] stack = new int[STACK_MAX_SIZE];

    public bool FLAG_EQUAL_TO_ZERO = false;
    public bool FLAG_GREATER_THAN_ZERO = false;
    public bool FLAG_LESS_THAN_ZERO = false;

    public class t_pos
    {
        public int x, y;
    };
    //typedef struct s_pos t_pos;

    public const int TAXI_STATUS_INACTIVE = 0;
    public const int TAXI_STATUS_ACTIVE = 1;
    
    public const int LIGHT_STATUS_INACTIVE = 0;
    public const int LIGHT_STATUS_ACTIVE = 1;
    
    public const int TAXI_DIRECTION_FORWARD = 0;
    public const int TAXI_DIRECTION_BACKWARD = 1;

    public const int D_EAST = 0;
    public const int D_WEST = 1;
    public const int D_NORTH = 2;
    public const int D_SOUTH = 3;

    public class t_taxi
    {
        public t_pos pos = new t_pos();
        public int status;
        public int orient;
        public int light;
        public int direction;
    };
    //typedef struct s_taxi t_taxi;

    public t_taxi taxi = new t_taxi();

    public const int OS_GROUND = 1;
    public const int OS_LIFTED = 2;

    //Maximum number of obstacles on the board
    public const int OBST_MAX_NUM = 10;
    t_pos[] obst = new t_pos[OBST_MAX_NUM];
    int obst_num = 0;

    public const int BOARD_SIZE = 5;
    public int[][] board = new int[BOARD_SIZE][];

    public const int CRASH_TYPE_OBSTACLE = 1;
    public const int CRASH_TYPE_WALL = 2;

    char keypressed;

    //Crash context
    public class t_crash_context
    {
        public bool flag_crash; //indicates if there exist a crash
        public int crash_type; //obstacle or wall
        public int orient; //orientation
        public t_pos pos = new t_pos();
    };
    //typedef struct s_crash_context t_crash_context;

    t_crash_context previous_crash_context = new t_crash_context(), //1st time taxi crashes
        next_crash_context = new t_crash_context(); //2nd time taxi crashes
    //If 1st and 2nd are equal,
    //it has crashed with the same object;

    bool boolSystemError = false;
    bool boolSystemSuccess = false;
    bool boolSystemSuccessInNextAdvance = false;
    //Indicates if taxi exits from board in next advance.

    public int GetNextValue()
    {
        int intRes = 0;

        switch (mem[PC++])
        {
            case AM_IMMEDT:
                intRes = mem[PC++];
                break;
            case AM_DIRREG:
                switch (mem[PC++])
                {
                    case R_PC: //Program Counter
                        intRes = PC;
                        break;
                    case R_IR1: //Instruction Register 1
                        intRes = IR1;
                        break;
                    case R_IR2: //Instruction Register 2
                        intRes = IR2;
                        break;
                    case R_SP:  //Stack Pointer
                        intRes = SP;
                        break;
                    case R_CRC: //Crash Counter
                        intRes = CRC;
                        break;
                    case R_AC:  //Advance Counter
                        intRes = AC;
                        break;
                    case R_ACC: //Accumulator
                        intRes = ACC;
                        break;
                }//switch
                break;
        }//switch
        return intRes;
    }//GetNextValue

    public void PutValue(int intSource)
    {
        switch (mem[PC++])
        {
            case AM_IMMEDT:
                break;
            case AM_DIRREG:
                switch (mem[PC++])
                {
                    case R_PC: //Program Counter
                        PC = intSource;
                        break;
                    case R_IR1: //Instruction Register 1
                        IR1 = intSource;
                        break;
                    case R_IR2: //Instruction Register 2
                        IR2 = intSource;
                        break;
                    case R_SP:  //Stack Pointer
                        SP = intSource;
                        break;
                    case R_CRC: //Crash Counter
                        CRC = intSource;
                        break;
                    case R_AC:  //Advance Counter
                        AC = intSource;
                        break;
                    case R_ACC: //Accumulator
                        ACC = intSource;
                        break;
                }//switch
                break;
        }//switch
    }//PutValue

    public void i_mov()
    {
        int intSource = GetNextValue();
        PutValue(intSource);
    }//i_mov

    public bool crash_with_obs(int x, int y)
    {
        bool boolRes = false;

        for (int i = 0; i < obst_num; i++)
        {
            if ((obst[i].x == x) && (obst[i].y == y))
            {//taxi crashes with this obstacle
                boolRes = true;
                break;
            }//if
        }//for

        return boolRes;
    }//crash_with_obs

    public bool GetNextAdvancePosition(t_crash_context c_ctx)
    {
        int x = taxi.pos.x;
        int y = taxi.pos.y;
        bool boolResObst = false; //taxi crashes with obstcle
        bool boolResWall = false; //taxi crashes with wall
        bool boolRes = false; //taxi crashes with either obst or wall
        int intCrashType = 0;

        switch (taxi.orient)
        {
            case D_EAST:
                if (taxi.direction == TAXI_DIRECTION_FORWARD)
                {
                    //if taxi doesn't crash with wall
                    if (y < (BOARD_SIZE - 1))
                    {
                        //taxi can advance to right
                        if (!crash_with_obs(x, y + 1))
                        {
                            //if taxi doesn't crash with obstacle
                            y++;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else
                }
                else
                {
                    if (y > 0)
                    {
                        //taxi can advance to left
                        if (!crash_with_obs(x, y - 1))
                        {
                            //if taxi doesn't crash with obstacle
                            y--;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else

                }
                break;

            case D_WEST:
                if (taxi.direction == TAXI_DIRECTION_FORWARD)
                {
                    if (y > 0)
                    {
                        //taxi can advance to left
                        if (!crash_with_obs(x, y - 1))
                        {
                            //if taxi doesn't crash with obstacle
                            y--;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else
                }
                else
                {
                    if (y < (BOARD_SIZE - 1))
                    {
                        //taxi can advance to right
                        if (!crash_with_obs(x, y + 1))
                        {
                            //if taxi doesn't crash with obstacle
                            y++;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else
                }
                break;

            case D_NORTH:
                if (taxi.direction == TAXI_DIRECTION_FORWARD)
                {
                    if (x > 0)
                    {
                        //taxi can advance up
                        if (!crash_with_obs(x - 1, y))
                        {
                            //if taxi doesn't crash with obstacle
                            x--;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else
                }
                else
                {
                    if (x < (BOARD_SIZE - 1))
                    {
                        //taxi can advance down
                        if (!crash_with_obs(x + 1, y))
                        {
                            //if taxi doesn't crash with obstacle
                            x++;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else
                }
                break;

            case D_SOUTH:
                if (taxi.direction == TAXI_DIRECTION_FORWARD)
                {
                    if (x < (BOARD_SIZE - 1))
                    {
                        //taxi can advance down
                        if (!crash_with_obs(x + 1, y))
                        {
                            //if taxi doesn't crash with obstacle
                            x++;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else
                }
                else
                {
                    if (x > 0)
                    {
                        //taxi can advance up
                        if (!crash_with_obs(x - 1, y))
                        {
                            //if taxi doesn't crash with obstacle
                            x--;
                        } //if
                        else
                        {
                            //taxi has crash with obstacle
                            boolResObst = true;
                            intCrashType = CRASH_TYPE_OBSTACLE;
                        } //else
                    } //if
                    else //Possibility to crash with wall
                    {
                        boolResWall = true;
                        intCrashType = CRASH_TYPE_WALL;
                    } //else
                }
                break;
        }

        if ((boolResObst) || (boolResWall))
            boolRes = true;

        c_ctx.flag_crash = boolRes;
        c_ctx.crash_type = intCrashType;
        c_ctx.pos.x = x;
        c_ctx.pos.y = y;
        c_ctx.orient = taxi.orient;

        return boolRes;
    }//GetNextAdvancePosition

    public void GetConditionsFromNextAdvance()
    {
        GetNextAdvancePosition(next_crash_context);
    }//GetConditionsFromNextAdvance

    public bool crashes_with_same_object()
    {
        bool boolRes = false;

        //if the previous_crash_context is equal to next_crash_context
        //it has crash the same object
        if ((previous_crash_context.flag_crash == next_crash_context.flag_crash)
            && (previous_crash_context.crash_type == next_crash_context.crash_type)
            && (previous_crash_context.pos.x == next_crash_context.pos.x)
            && (previous_crash_context.pos.y == next_crash_context.pos.y)
            && (previous_crash_context.orient == next_crash_context.orient)
           )
        {
            boolRes = true;
        }//if

        return boolRes;
    }//crashes_with_same_object

    public void blank_crash_context(t_crash_context c_ctx)
    {
        c_ctx.flag_crash = false;
        c_ctx.crash_type = 0;
        c_ctx.pos.x = -1;
        c_ctx.pos.y = -1;
        c_ctx.orient = 0;
    }//blank_crash_context

    public void i_adv()
    {
        if (taxi.status == TAXI_STATUS_ACTIVE)
        {
            if(taxi.direction == TAXI_DIRECTION_FORWARD)
            Debug.Log("active and Advancing");
            if(taxi.direction == TAXI_DIRECTION_BACKWARD)
                Debug.Log("active and Backwards");
            GetConditionsFromNextAdvance();

            //If in next advance taxi crashes, it can't advance
            if (next_crash_context.flag_crash == true)
            {
                //Increment Crash Counter
                if (CRC == 0) //taxi hasn't before
                {
                    CRC++;
                    previous_crash_context.flag_crash = next_crash_context.flag_crash;
                    previous_crash_context.crash_type = next_crash_context.crash_type;
                    previous_crash_context.pos.x = next_crash_context.pos.x;
                    previous_crash_context.pos.y = next_crash_context.pos.y;
                    previous_crash_context.orient = next_crash_context.orient;
                } //if
                else if (CRC > 0)
                {
                    //If taxi crashes more than 1 time with same object
                    //It'll be destroyed
                    if (crashes_with_same_object())
                    {
                        //taxi is destroyed
                       // taxi.status = TAXI_STATUS_INACTIVE;
                        boolSystemError = true;
                    } //if
                } //else if
            } //if
            else //Normal Advance, there is not a crash
            {
                taxi.pos.x = next_crash_context.pos.x;
                taxi.pos.y = next_crash_context.pos.y;
                blank_crash_context(previous_crash_context);
                CRC = 0;
            } //else

            blank_crash_context(next_crash_context);
        }
        else
        {
            Debug.Log("inactive.");
            return;
        }
    }

    public void ReviewACCFlags()
    {
        FLAG_EQUAL_TO_ZERO = (ACC == 0) ? true : false;
        FLAG_GREATER_THAN_ZERO = (ACC > 0) ? true : false;
        FLAG_LESS_THAN_ZERO = (ACC < 0) ? true : false;
    }//ReviewACCFlags

    public void i_dec()
    {
        ACC--;
        ReviewACCFlags();
    }//i_dec

    public void i_jnz()
    {
        int intNextAddress = mem[PC++];
        if ((FLAG_GREATER_THAN_ZERO) || (FLAG_LESS_THAN_ZERO))
        {
            PC = intNextAddress;
        }//if
    }//i_jnz

    public void i_jez()
    {
        int intNextAddress = mem[PC++];
        if (FLAG_EQUAL_TO_ZERO)
        {
            PC = intNextAddress;
        }//if
    }//i_jez

    public void i_push()
    {
        stack[SP++] = GetNextValue();
    }//i_push

    public void i_cmp()
    { //Compare 2 popped values from Stack, it will substract them,
        //Change condition flags <0 >0 =0
        int intMinuend = stack[--SP];
        int intSubstraend = stack[--SP];

        ACC = intSubstraend - intMinuend;
        ReviewACCFlags();
    }//i_cmp

    public void i_end()
    {

    }//i_end

    public void i_tright()
    {
        if (taxi.status == TAXI_STATUS_ACTIVE)
        {
            Debug.Log("active and turning right");
            switch (taxi.orient)
            {
                case D_EAST:
                    taxi.orient = D_SOUTH;
                    break;
                case D_WEST:
                    taxi.orient = D_NORTH;
                    break;
                case D_NORTH:
                    taxi.orient = D_EAST;
                    break;
                case D_SOUTH:
                    taxi.orient = D_WEST;
                    break;
            }//switch
        }
    }//i_tright

    public void i_tleft()
    {
        if (taxi.status == TAXI_STATUS_ACTIVE)
        {
            Debug.Log("active and turning left");
            switch (taxi.orient)
            {
                case D_EAST:
                    taxi.orient = D_NORTH;
                    break;
                case D_WEST:
                    taxi.orient = D_SOUTH;
                    break;
                case D_NORTH:
                    taxi.orient = D_WEST;
                    break;
                case D_SOUTH:
                    taxi.orient = D_EAST;
                    break;
            }//switch
        }
    }//i_tleft

    public void i_drown()
    {
        Debug.Log("drowning");
        taxi.status = TAXI_STATUS_INACTIVE;
    }//i_pickup

    public void i_rev()
    {
        Debug.Log("reving");
        taxi.status = TAXI_STATUS_ACTIVE;
    }//i_puntdown

    public void LoadProgramInMemory(string strBinaryFile)
    {
        //    FILE* ptrBinaryFile;
        //    signed short sshValue;
        //    int PCLocal = 0;
        //    ptrBinaryFile = fopen(strBinaryFile, "rb");

        //    if (ptrBinaryFile != NULL)
        //    {
        //        while (fread(&sshValue, sizeof(signed short), 1, ptrBinaryFile) != 0)
        //{
        //            mem[PCLocal++] = (int)sshValue;
        //        }//while
        //    }//if
        //    else
        //        printf("Object Code File Not Found!\n");

        //    fclose(ptrBinaryFile);
        int PCLocal = 0;

        try
        {
            using (FileStream fs = new FileStream(strBinaryFile,
                       FileMode.Open, FileAccess.Read))
            using (BinaryReader lector = new BinaryReader(fs))
            {
                while (lector.BaseStream.Position <
                       lector.BaseStream.Length)
                {
                    short sshValue = lector.ReadInt16();
                    mem[PCLocal++] = (int)sshValue;
                    Debug.Log($"Read value: {sshValue}");
                }//while
            }//using
        }//try
        catch (FileNotFoundException)
        {
            Debug.Log("File not found.\n");
        }
        catch (EndOfStreamException)
        {
            Debug.Log("Unexpected EOF.\n");
        }
        catch (Exception)
        {
            Debug.Log("Error in object code file.\n");
        }

    }//LoadProgramInMemory

    public void InitialConditions()
    {
       

        obst_num = 1;
        t_pos obst1 = new t_pos();
        obst1.x = 2;
        obst1.y = 2;
        obst[obst_num - 1] = obst1;

       

        taxi.pos.x = 0;
        taxi.pos.y = 0;
        taxi.orient = D_EAST;
        taxi.status = TAXI_STATUS_INACTIVE;
        taxi.direction = TAXI_DIRECTION_FORWARD;
        taxi.light = LIGHT_STATUS_INACTIVE;

    }//InitialConditions


    public void reset()
    {
        InitialConditions();
        //graphBoard_DrawExecutionContext();
    }//reset

    public int execute()
    {

        PC = 0;

        reset();

        LoadProgramInMemory("object.bin");

        do
        {
            IR1 = mem[PC++];
            switch (IR1)
            {
                case A_MOV: //Move a value
                    i_mov();
                    break;
                case A_ADV: //Advance 1 location
                    i_adv();
                    break;
                case A_DEC: //Decrement Accumulator by 1
                    i_dec();
                    break;
                case A_JNZ: //Jump if Not equal to Zero
                    i_jnz();
                    break;
                case A_JEZ: //Jump if Equal to Zero
                    i_jez();
                    break;
                case A_PUSH://Push to Stack
                    i_push();
                    break;
                case A_CMP: //Compare 2 popped values from Stack, it will sustract them,
                    //Change condition flags <0 >0 =0
                    i_cmp();
                    break;
                case A_END: //Ends the program
                    i_end();
                    break;
                case A_TRIGHT:  //Turn to Right
                    i_tright();
                    break;
                case A_TLEFT:   //Turn to Left
                    i_tleft();
                    break;
                case A_DROWN:  //Pickup Object
                    i_drown();
                    break;
                case A_REV: //Put down Object
                    i_rev();
                    break;
                case A_LIGHTON:
                    i_lighton();
                    break;
                case A_LIGHTOFF:
                    i_lightoff();
                    break;
                case A_HONK:
                    i_honk();
                    break;
                case A_FRWRD:
                    i_frwd();
                    break;
                case A_BACK:
                    i_back();
                    break;
            }//switch
 
            //graphBoard_DrawExecutionContext();

        } while ((mem[PC] != A_END)
                 && (!boolSystemError)
                 && (!boolSystemSuccess)
                 && (keypressed != 'q')   //q=quit
                );

        Debug.Log("Terminated Program!\n");
        return 0;
    }

    
    //VirtualMachine

    internal class Program
    {
        static void Main(string[] args)
        {
            VirtualMachine vm = new VirtualMachine();
            vm.execute();
            Debug.Log("Hello World!");
        }
    }
    public void i_lighton()
    {
        Debug.Log("lights on.");
        taxi.light = LIGHT_STATUS_ACTIVE;
    }

    public void i_lightoff()
    {
        Debug.Log("lights off.");
        taxi.light = LIGHT_STATUS_INACTIVE;
    }
    
    public void i_honk()
    {
        Debug.Log("HONK");
    }

    public void i_frwd()
    {
        taxi.direction = TAXI_DIRECTION_FORWARD;
        i_adv();
    }

    public void i_back()
    {
        taxi.direction = TAXI_DIRECTION_BACKWARD;
        i_adv();
    }
}