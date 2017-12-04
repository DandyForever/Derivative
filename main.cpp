#include <iostream>
#include "Tree_t.h"
#include <assert.h>
#include "messages.h"
#include "commands.h"

void LoadNode (FILE* load, Node* parent, Tree_t* data);
void LoadFile (const char* filename, Tree_t* data);
Node* CopyNode (const Node* current);
Node* MakeNode (const int type, const double value);
Node* MakeNode (const int type, const double value, Node* Left, Node* Right);
Node* diffsin (Node* current);
Node* diffcos (Node* current);
Node* difftan (Node* current);
Node* diffcot (Node* current);
Node* diffexp (Node* current);
Node* diffln (Node* current);
Node* difflg (Node* current);
Node* difflog (Node* current);
Node* Diffpow (Node* current);
Node* Diffunc (Node* current, Node* differ (Node*));
Node* Derivate (Node* current);
void MakeTex (const Node* current, FILE* file, const Node* power, const int brackets);
void CreateTheBeginningOfTex ();
void CreateFormulaTex (const Node* current, const char* message);
void CreateTheEndOfTex ();
bool Optimise (Tree_t* data, Node* current, Node* parent, const int side);
bool Simplify (Tree_t* data, Node* current, Node* parent, const int side);

typedef Node* Exp_type;

double   GetN ();
Exp_type GetE ();
Exp_type GetP ();
Exp_type GetT ();
Exp_type GetG (const char* expression);

const int MaxString = 300;
const double POISON = 666.666;
const char* Expression = nullptr;
int Index = 0;

int main()
{
    Tree_t data_inp;
    Tree_t data;
    /*tree.PushFirst (1, 10);
    tree.PushLeft (tree.First (), 2, 20);
    tree.PushRight (tree.First (), 3, 30);
    printf ("%d\n", tree.NodeSize (tree.CopyNode (tree.First ())));
    tree.PushRight (tree.First()->right, tree.CopyNode (tree.First()));*/
    char* expression = new char [1000] {};
    assert (expression);

    scanf ("%s", expression);
    //printf ("%f", GetG (expression));
    //LoadFile ("test.txt", &data_inp);
    data_inp.PushFirst (GetG (expression));
    CreateTheBeginningOfTex ();
    CreateFormulaTex (data_inp.First (), FIRST_MESSAGE);
    CreateFormulaTex (0, SIMPLE_MESSAGE);

    int number_of_optimising = 0;

    LETSSIMPLIFYTHEFUNCTION (data_inp)

    data.PushFirst (Derivate (data_inp.First ()));
    data_inp.DeleteNode (data_inp.First ());

    CreateFormulaTex (data.First (), SIMPLIFY_DERIVATIVE_MESSAGE);

    LETSSIMPLIFYTHEFUNCTION(data)

    CreateTheEndOfTex();

    data.Dump ();
    return 0;
}


void LoadFile (const char* filename, Tree_t* data)
{
    FILE* load = fopen (filename, "rb");
    assert (load);

    Node* parent = data->First ();

    int number = -1;

    DOLOADING(Left)

        LoadNode (load, data->First (), data);
    }
}

void LoadNode (FILE* load, Node* parent, Tree_t* data)
{
    int number = -1;

    DOLOADING(Left)

        LoadNode (load, parent->left, data);
    }

    DOLOADING(Right)

        LoadNode (load, parent->right, data);
    }

    getc (load);
}

Node* Derivate (Node* current)
{
    Node* madenode = new Node;
    assert (madenode);

    if (ISNUM(current))
    {
        madenode = NUMERIC(0);
        CreateFormulaTex (0, NUM_DERIVATING_MESSAGE);
    }

    else if (ISVAR(current))
    {
        madenode = NUMERIC(1);
        CreateFormulaTex (0, VAR_DERIVATING_MESSAGE);
    }

    else
    {
        switch ((int) current->value)
        {
        case ADD:
            madenode = PLUS(dL, dR);
            CreateFormulaTex (0, ADD_DERIVATING_MESSAGE);
            break;

        case SUB:
            madenode = MINUS(dL, dR);
            CreateFormulaTex (0, SUB_DERIVATING_MESSAGE);
            break;

        case MUL:
            madenode = PLUS(MULTIP(dL, cR), MULTIP(dR, cL));
            CreateFormulaTex (0, MUL_DERIVATING_MESSAGE);
            break;

        case DIV:
            madenode = DIVIS(MINUS(MULTIP(dL, cR), MULTIP(dR, cL)), POWER(cR, NUMERIC(2)));
            CreateFormulaTex (0, DIV_DERIVATING_MESSAGE);
            break;

        case SIN:
            madenode = Diffunc (current, diffsin);
            CreateFormulaTex (0, SIN_DERIVATING_MESSAGE);
            break;

        case COS:
            madenode = Diffunc (current, diffcos);
            CreateFormulaTex (0, COS_DERIVATING_MESSAGE);
            break;

        case TAN:
            madenode = Diffunc (current, difftan);
            CreateFormulaTex (0, TAN_DERIVATING_MESSAGE);
            break;

        case COT:
            madenode = Diffunc (current, diffcot);
            CreateFormulaTex (0, COT_DERIVATING_MESSAGE);
            break;

        case EXP:
            madenode = Diffunc (current, diffexp);
            CreateFormulaTex (0, EXP_DERIVATING_MESSAGE);
            break;

        case LN:
            madenode = Diffunc (current, diffln);
            CreateFormulaTex (0, LN_DERIVATING_MESSAGE);
            break;

        case LG:
            madenode = Diffunc (current, difflg);
            CreateFormulaTex (0, LG_DERIVATING_MESSAGE);
            break;

        case LOG:
            madenode = Diffunc (current, difflog);
            break;

        case POW:
            madenode = Diffpow (current);
            break;
        }
    }

    CreateFormulaTex (EQUAL(current, madenode), MESSAGES[rand () % Number_of_mess]);
    return madenode;
}

Node* MakeNode (const int type, const double value)
{
    Node* node = new Node;
    assert (node);

    node->key = type;
    node->value = value;

    node->left = nullptr;
    node->right = nullptr;

    return node;
}

Node* MakeNode (const int type, const double value, Node* Left, Node* Right)
{
    Node* node = new Node;
    assert (node);

    node->key = type;
    node->value = value;

    node->left = Left;
    node->right = Right;

    return node;
}

Node* CopyNode (const Node* current)
{
    Node* copynode = new Node;

    copynode->key = current->key;
    copynode->value = current->value;
    copynode->first = current->first;

    if (current->left)
        copynode->left = cL;

    else
        copynode->left = nullptr;

    if (current->right)
        copynode->right = cR;

    else
        copynode->right = nullptr;

    return copynode;
}

Node* Diffunc (Node* current, Node* differ (Node*))
{
    return MULTIP(differ (current), Derivate (current->left));
}

Node* diffsin (Node* current)
{
    return COSINUS(cL);
}

Node* diffcos (Node* current)
{
    return MULTIP(NUMERIC(-1), SINUS(cL));
}

Node* difftan (Node* current)
{
    return DIVIS(NUMERIC(1), POWER(COSINUS(cL), NUMERIC(2)));
}

Node* diffcot (Node* current)
{
    return DIVIS(NUMERIC(-1), POWER(SINUS(cL), NUMERIC(2)));
}

Node* diffexp (Node* current)
{
    return EPOW(cL);
}

Node* diffln (Node* current)
{
    return DIVIS(NUMERIC(1), cL);
}

Node* difflg (Node* current)
{
    return DIVIS(NUMERIC(1), MULTIP(cL, LNE(NUMERIC(10))));
}

Node* difflog (Node* current)
{
    Node* node = new Node;
    assert (node);

    if (ISNUM(current->right))
    {
        node = DIVIS(NUMERIC(1), MULTIP(cL, LNE(cR)));
        CreateFormulaTex (0, LOG_EASY_DERIVATING_MESSAGE);
    }
    else
    {
        node = Derivate(DIVIS(LNE(current->right), LNE(current->left)));
        CreateFormulaTex (0, LOG_DIFF_DERIVATING_MESSAGE);
    }

    return node;
}

Node* Diffpow (Node* current)
{
    Node* node = new Node;
    assert (node);

    if (ISNUM(current->right))
    {
        node = MULTIP(MULTIP(NUMERIC(current->right->value), POWER(cL, NUMERIC(current->right->value - 1))),
                       Derivate (current->left));
        CreateFormulaTex (0, POW_FUNC_DERIVATING_MESSAGE);
    }

    else if (ISNUM(current->left))
    {

        node = MULTIP(MULTIP(POWER(NUMERIC(current->left->value), cR), LNE(NUMERIC(current->left->value))),
                       Derivate (current->right));
        CreateFormulaTex (0, POW_NUM_DERIVATING_MESSAGE);
    }
    else
    {
        node = MULTIP(CopyNode(current), PLUS(MULTIP(dL, DIVIS(cR, cL)), MULTIP(dR, LNE(cL))));
        CreateFormulaTex (0, POW_DIFF_DERIVATING_MESSAGE);
    }

    return node;
}

void CreateTheBeginningOfTex ()
{
    FILE* tex = fopen ("derivative.tex", "w");
    assert (tex);

    fprintf (tex, "\\documentclass[a4paper,12pt]{article}\n\n");
    fprintf (tex, "\\usepackage[T2A]{fontenc}\n");
    fprintf (tex, "\\usepackage[utf8]{inputenc}\n");
    fprintf (tex, "\\usepackage[english,russian]{babel}\n");
    fprintf (tex, "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n");
    fprintf (tex, "\\usepackage{wasysym}\n");
    fprintf (tex, "\\author{Khaidukov Danila}\n");
    fprintf (tex, "\\title{Derivatives in \\LaTeX{}}\n");
    fprintf (tex, "\\date{\\today}\n\n");
    fprintf (tex, "\\begin{document}\n\n");
    fprintf (tex, "\\maketitle\n");
    fprintf (tex, "\\newpage\n\n");

    fclose (tex);
}

void CreateTheEndOfTex ()
{
    FILE* tex = fopen ("derivative.tex", "a");
    assert (tex);

    fprintf (tex, "Derivatives are really easy!\n\n");
    fprintf (tex, "\\end{document}\n");

    fclose (tex);

    system("pdflatex.exe -synctex=1 -interaction=nonstopmode derivative.tex");
    system("start derivative.pdf");
}

void CreateFormulaTex (const Node* current, const char* message)
{
    FILE* tex = fopen ("derivative.tex", "a");
    assert (tex);

    fprintf (tex, "%s\n", message);

    if (current)
    {
        fprintf (tex, "\\[ ");

        MakeTex (current, tex, 0, 0);

        fprintf (tex, " \\]\n");
    }

    fprintf (tex, "\n");

    fclose (tex);
}

void MakeTex (const Node* current, FILE* file, const Node* power, const int brackets)
{
    if (ISNUM(current))
    {
        if (current->value > 0 && current->value - (int) current->value < 1e-6 || current->value < 0 && (int) current->value - current->value < 1e-6)
            fprintf (file, "%d", (int) current->value);

        else
            fprintf (file, "%g", current->value);
        //printf ("%d %d\n", current->value > 0 && current->value - (int) current->value < 1e-6, current->value < 0 && (int) current->value - current->value < 1e-6);
        TOPOWER
    }

    else if (ISVAR(current))
    {
        fprintf (file, "x");
        TOPOWER
    }

    else
    {
        switch ((int) current->value)
        {
        case ADD:
            {
                if (brackets)
                    OPENBR
                MakeTex (current->left, file, 0, 0);
                fprintf (file, " + ");
                MakeTex (current->right, file, 0, 0);
                if (brackets)
                    CLOSEBR
                TOPOWER
                break;
            }

        case SUB:
            {
                if (brackets)
                    OPENBR
                MakeTex (current->left, file, 0, 0);
                fprintf (file, " - ");
                MakeTex (current->right, file, 0, 0);
                if (brackets)
                    CLOSEBR
                TOPOWER
                break;
            }

        case MUL:
            {
                if (ISNUM(current->left) && ISVAR(current->right))
                {
                    MakeTex (current->left, file, 0, 0);
                    MakeTex (current->right, file, 0, 0);
                }
                else if (ISNUM(current->left) && ISVAR(current->right))
                {
                    MakeTex (current->right, file, 0, 0);
                    MakeTex (current->left, file, 0, 0);
                }

                else
                {
                    int mode = 0;
                    MULMODE(left)

                    fprintf (file, " \\cdot ");

                    MULMODE(right)
                }
                break;
            }

        case DIV:
            {
                if (power)
                    fprintf (file, "\\left( ");

                fprintf (file, "\\frac{ ");
                MakeTex (current->left, file, 0, 0);
                fprintf (file, " }{ ");
                MakeTex (current->right, file, 0, 0);
                fprintf (file, " }");

                if (power)
                    fprintf (file, "\\right)");
                TOPOWER
                break;
            }

        case SIN:
            {
                DIFICFUNC(sin)
                break;
            }

        case COS:
            {
                DIFICFUNC(cos)
                break;
            }

        case TAN:
            {
                DIFICFUNC(tg)
                break;
            }

        case COT:
            {
                DIFICFUNC(ctg)
                break;
            }

        case EXP:
            {
                fprintf (file, "e ^ { ");
                MakeTex (current->left, file, 0, 0);
                fprintf (file, " }");
                break;
            }

        case LN:
            {
                DIFICFUNC(ln)
                break;
            }

        case LG:
            {
                DIFICFUNC(lg)
                break;
            }

        case LOG:
            {
                fprintf (file, "log");
                TOPOWER

                fprintf (file, "_{ ");
                if (!ISNUM(current->right) || !ISVAR(current->right))
                    OPENBR
                MakeTex (current->right, file, 0, 0);
                if (!ISNUM(current->right) || !ISVAR(current->right))
                    CLOSEBR
                fprintf (file, " }{ ");
                OPENBR
                MakeTex (current->left, file, 0, 0);
                CLOSEBR
                fprintf (file, " }");
                break;
            }

        case POW:
            {
                MakeTex (current->left, file, current->right, 1);
                break;
            }

        case EQU:
            {
                fprintf (file, "\\left(");
                MakeTex (current->left, file, 0, 0);
                fprintf (file, "\\right)' = ");
                MakeTex (current->right, file, 0, 0);
                break;
            }
        }
    }
}

bool Optimise (Tree_t* data, Node* current, Node* parent, const int side)
{
    bool status = 0;

    if (current->key == OPERATOR)
    {
        switch ((int) current->value)
        {
        case MUL:
            {
                if (ISNUM(current->left))
                {
                    OPTIMISING(0, NUMERIC(0), left)

                    else

                    OPTIMISING(1, cR, left)
                }

                if (ISNUM(current->right))
                {
                    OPTIMISING(0, NUMERIC(0), right)

                    else

                    OPTIMISING(1, cL, right)
                }

                break;
            }

        case ADD:
            {
                if (ISNUM(current->left))
                    OPTIMISING(0, cR, left)

                if (ISNUM(current->right))
                    OPTIMISING(0, cL, right)

                break;
            }
        case DIV:
            {
                if (ISNUM(current->left))
                {
                    OPTIMISING(0, cR, left)
                    if (current->right->key == OPERATOR && (int) current->right->value == DIV)
                    {
                        OPTIMISING(1, DIVIS(CopyNode(current->right->right), CopyNode(current->right->left)), left)
                    }
                }
                if (ISVAR(current->left) && ISVAR(current->right))
                {
                    OPTIMISING(-1, NUMERIC(1), left)
                }

                else if (ISNUM(current->right))
                {
                    if ((int) current->right->value == 0)
                    {
                        printf ("BAD INPUT\n");
                        assert (0);
                    }
                    else

                    OPTIMISING(1, cL, right)
                }
                break;
            }
        case SUB:
            {
                if (ISNUM(current->left))
                {
                    OPTIMISING(0, MULTIP(NUMERIC(-1), cR), left)
                }

                else if (ISNUM(current->right))
                {
                    OPTIMISING(0, cL, right)
                }
                break;
            }
        case POW:
            {
                if (ISNUM(current->right))
                {
                    OPTIMISING(1, cL, right)
                }
                break;
            }
        }
    }
    if (current->left)
        status = Optimise (data, current->left, current, -1);

    if (status)
        return 1;

    if (current->right)
        status = Optimise (data, current->right, current, 1);

    if (status)
        return 1;

    return 0;
}


bool Simplify (Tree_t* data, Node* current, Node* parent, const int side)
{
    bool status = 0;

    if (current->key == OPERATOR)
    {
        switch ((int) current->value)
        {
        case MUL:
            SIMPIFYING(*)
        case ADD:
            SIMPIFYING(+)
        case DIV:
            SIMPIFYING(/)
        case SUB:
            SIMPIFYING(-)
        }
    }
    if (current->left)
        status = Simplify (data, current->left, current, -1);

    if (status)
        return 1;

    if (current->right)
        status = Simplify (data, current->right, current, 1);

    if (status)
        return 1;

    return 0;
}

const char** Messages ()
{
    const char** messages = new const char* [Number_of_mess] {};
    assert (messages);

    messages[0] = "Easy:";
    messages[1] = "Elementary:";
    messages[2] = "Clearly:";
    messages[3] = "As you can see:";
    messages[4] = "It's really easy to see:";
    messages[5] = "You can see:";
    messages[6] = "It's clear that:";
    messages[7] = "So:";
    messages[8] = "Then:";
    messages[9] = "In that case:";

    return messages;
}

Exp_type GetG (const char* expression)
{
    Expression = expression;
    Index = 0;

    Exp_type value = GetE ();

    assert (Expression[Index] == '\0');

    return value;
}

Exp_type GetE ()
{
    Exp_type value = GetT ();

    while (Expression[Index] == '+' || Expression[Index] == '-')
    {
        const char operation = Expression[Index];
        Index++;

        int ind_cop = Index;

        Exp_type next_value = GetT ();

        assert (ind_cop != Index);

        if (operation == '+')
            value = PLUS(value, next_value);

        else
            value = MINUS(value, next_value);
    }

    return value;
}

Exp_type GetT ()
{
    Exp_type value = GetP ();

    while (Expression[Index] == '*' || Expression[Index] == '/')
    {
        const char operation = Expression[Index++];

        int ind_cop = Index;

        Exp_type next_value = GetP ();

        assert (ind_cop != Index);

        if (operation == '*')
            value = MULTIP(value, next_value);

        else
            value = DIVIS(value, next_value);
    }

    return value;
}

Exp_type GetP ()
{
    Exp_type value = 0, value_ = 0;

    if (Expression[Index] == '(')
    {
        Index++;

        value = GetE ();

        assert (Expression[Index++] == ')');

        if (Expression[Index] == '^')
        {
            Index++;

            value_ = GetP ();

            value = POWER(value, value_);
        }

        return value;
    }

    else if (Expression[Index] == 's' && Expression[Index + 1] == 'i' && Expression[Index + 2] == 'n')
    {
        Index += 3;

        if (Expression[Index] == '^')
        {
            Index++;

            value_ = GetP ();
        }

        value = SINUS(GetP ());

        if (value_)
            value = POWER(value, value_);
    }

    else if (Expression[Index] == 'c' && Expression[Index + 1] == 'o' && Expression[Index + 2] == 's')
    {
        Index += 3;

        if (Expression[Index] == '^')
        {
            Index++;

            value_ = GetP ();
        }

        value = COSINUS(GetP ());

        if (value_)
            value = POWER(value, value_);
    }

    else if (Expression[Index] == 'c' && Expression[Index + 1] == 't' && Expression[Index + 2] == 'g')
    {
        Index += 3;

        if (Expression[Index] == '^')
        {
            Index++;

            value_ = GetP ();
        }

        value = COTANGENT(GetP ());

        if (value_)
            value = POWER(value, value_);
    }

    else if (Expression[Index] == 't' && Expression[Index + 1] == 'g')
    {
        Index += 2;

        if (Expression[Index] == '^')
        {
            Index++;

            value_ = GetP ();
        }

        value = TANGENT(GetP ());

        if (value_)
            value = POWER(value, value_);
    }

    else if (Expression[Index] == 'l' && Expression[Index + 1] == 'n')
    {
        Index += 2;

        if (Expression[Index] == '^')
        {
            Index++;

            value_ = GetP ();
        }

        value = LNE(GetP ());

        if (value_)
            value = POWER(value, value_);
    }
    else if (Expression[Index] == 'l' && Expression[Index + 1] == 'g')
    {
        Index += 2;

        if (Expression[Index] == '^')
        {
            Index++;

            value_ = GetP ();
        }

        value = L10(GetP ());

        if (value_)
            value = POWER(value, value_);
    }

    else if (Expression[Index] == 'e' && Expression[Index + 1] == '^')
    {
        Index += 2;

        value = EPOW(GetP ());
    }

    else if (Expression[Index] == 'l' && Expression[Index + 1] == 'o' && Expression[Index + 2] == 'g')
    {
        Index += 3;

        Exp_type value_pow = 0;

        if (Expression[Index] == '^')
        {
            Index++;

            value_pow = GetP ();
        }

        assert (Expression[Index++] == '(');

        value = GetE ();

        assert (Expression[Index++] == ',');

        value_ = GetE ();

        assert (Expression[Index++] == ')');

        if (value_pow)
            value = POWER(LOGARITHM(value_, value), value_pow);

        value = LOGARITHM(value_, value);
    }

    else if (Expression[Index] >= '0' && Expression[Index] <= '9')
    {
        value = NUMERIC(GetN ());
    }

    else
    {
        Index++;

        value = VARIA();

        assert (!isalpha (Expression[Index]));
    }

    if (Expression[Index] == '^')
    {
        Index++;

        value_ = GetP ();

        value = POWER(value, value_);
    }

    return value;
}

double GetN ()
{
    double value = 0;

    while (Expression[Index] >= '0' && Expression[Index] <= '9')
    {
        value = value * 10 + Expression[Index] - '0';
        Index++;
    }

    if (Expression[Index] == '.')
    {
        Index++;

        int power = 10;

        while (Expression[Index] >= '0' && Expression[Index] <= '9')
        {
            value = value + (double) (Expression[Index] - '0') / power;
            power *= 10;

            Index++;
        }
    }

    return value;
}

///("e^"("+"("^"("x" "2") "*"("5" "x")) ""))
///("log"("ctg"("^"("2" "x") "") "5"))
///("^"("/"("5" "x") "6"))
///("sin"("/"("2" "x") ""))
///("^"("+"("^"("x" "2") "*"("5" "x")) "4"))
///("ln"("/"("2" "x") ""))
///("^"("sin"("x" "") "3"))
///("^"("sin"("^"("2" "x") "") "3"))
///("^"("sin"("^"("x" "2") "") "3"))
///("^"("x" "x"))
///("log"("+"("2" "x") "x"))
///("/"("1" "+"("1" "^"("x" "2"))))
