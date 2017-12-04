#define DOLOADING(Side) getc (load);\
    getc (load);\
\
    char* t_##Side = new char [MaxString];\
    assert (t_##Side);\
\
    number = -1;\
\
    fscanf (load, "%[^0-9.\"]%n", t_##Side, &number);\
\
    if (number == -1)\
    {\
        double num##Side = POISON;\
\
        fscanf (load, "%lf", &num##Side);\
        \
        if (abs (num##Side - POISON) > 1e-6)\
            data->Push##Side (parent, NUM, num##Side);\
            getc (load);\
    }\
\
    else if (number == 1 && !strcmp (t_##Side, "x"))\
    {\
        data->Push##Side (parent, VAR, -1);\
        getc (load);\
    }\
\
    else\
    {   LOADING(Side, +,   ADD)\
        LOADING(Side, -,   SUB)\
        LOADING(Side, *,   MUL)\
        LOADING(Side, /,   DIV)\
        LOADING(Side, sin, SIN)\
        LOADING(Side, cos, COS)\
        LOADING(Side, tg,  TAN)\
        LOADING(Side, ctg, COT)\
        LOADING(Side, e^,  EXP)\
        LOADING(Side, ^,   POW)\
        LOADING(Side, ln,  LN)\
        LOADING(Side, lg,  LG)\
        LOADING(Side, log, LOG)\
        {\
            printf ("UNKNOWN COMMAND\n");\
            assert (0);\
        }\
\
        getc (load);


#define LOADING(side, filename, name) if (!strcmp (t_##side, #filename))\
            data->Push##side (parent, OPERATOR, name);\
\
        else

#define dL Derivate (current->left)
#define dR Derivate (current->right)
#define cL CopyNode (current->left)
#define cR CopyNode (current->right)

#define NUMERIC(number)        MakeNode (NUM, number)
#define   VARIA()              MakeNode (VAR, -1)

#define ISNUM(node) node ->key == NUM
#define ISVAR(node) node ->key == VAR

#define      PLUS(left, right) MakeNode (OPERATOR, ADD, left, right)
#define     MINUS(left, right) MakeNode (OPERATOR, SUB, left, right)
#define    MULTIP(left, right) MakeNode (OPERATOR, MUL, left, right)
#define     DIVIS(left, right) MakeNode (OPERATOR, DIV, left, right)
#define     POWER(left, right) MakeNode (OPERATOR, POW, left, right)
#define     EQUAL(left, right) MakeNode (OPERATOR, EQU, left, right)
#define LOGARITHM(left, right) MakeNode (OPERATOR, LOG, left, right)
#define     SINUS(current)     MakeNode (OPERATOR, SIN, current, nullptr)
#define   COSINUS(current)     MakeNode (OPERATOR, COS, current, nullptr)
#define   TANGENT(current)     MakeNode (OPERATOR, TAN, current, nullptr)
#define COTANGENT(current)     MakeNode (OPERATOR, COT, current, nullptr)

#define      EPOW(current)     MakeNode (OPERATOR, EXP, current, nullptr)
#define       LNE(current)     MakeNode (OPERATOR, LN , current, nullptr)
#define       L10(current)     MakeNode (OPERATOR, LG , current, nullptr)

#define SIMPIFYING(operator){\
if (ISNUM(current->left) && ISNUM(current->right))\
{\
    double number = current->left->value operator current->right->value;\
    if (side == 1)\
        data->PushRight (parent, NUMERIC(number));\
    else\
        data->PushLeft (parent, NUMERIC(number));\
    return 1;\
}\
break;\
}

#define OPTIMISING(number, node, side_)\
if ((current -> side_ -> value < 1e-4 || current -> side_ -> value > 0) && current -> side_ -> value - (double) number < 1e-3 && (double) number - current -> side_ -> value < 1e-3)\
{\
    if (side == 1)\
        data->PushRight (parent, node);\
    else\
        data->PushLeft (parent, node);\
    return 1;\
}

#define OPENBR fprintf (file, "\\left( ");

#define CLOSEBR fprintf (file, "\\right) ");

#define TOPOWER if (power)\
                {\
                    fprintf (file, " ^ { ");\
                    MakeTex (power, file, 0, 0);\
                    fprintf (file, " }");\
                }

#define MULMODE(side) mode = 0;\
                if (current-> side ->key == OPERATOR && ((int) current-> side ->value == ADD || (int) current-> side ->value == SUB))\
                    mode = 1;\
\
                if (mode)\
                    MakeTex (current-> side, file, 0, 1);\
                else\
                    MakeTex (current-> side, file, 0, 0);\

#define DIFICFUNC(name) fprintf (file, "\\");\
                fprintf (file, #name);\
                TOPOWER\
                OPENBR\
                MakeTex (current->left, file, 0, 0);\
                CLOSEBR\


#define LETSSIMPLIFYTHEFUNCTION(data) number_of_optimising = 0;\
\
    while (true)\
    {\
        bool flag = Optimise (& data, data .First (), 0, 0);\
        flag += Simplify (& data, data .First (), 0, 0);\
        number_of_optimising++;\
        if (!flag) break;\
        CreateFormulaTex (data .First (), MESSAGES[rand () % Number_of_mess]);\
    }\
\
    if (number_of_optimising > 1)\
        CreateFormulaTex (data .First (), YESSIMPLIER_MESSAGE);\
    else\
        CreateFormulaTex (0, NOSIMPLIER_MESSAGE);

enum types
{
    NUM = 1,
    VAR = 2,
    OPERATOR = 3
};

enum operators
{
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    SIN = 5,
    COS = 6,
    TAN = 7,
    COT = 8,
    EXP = 9,
    POW = 10,
    LN  = 11,
    LG  = 12,
    LOG = 13,
    EQU = 14
};

