#define FIRST_MESSAGE "So, we're going to find the derivative of that interesting function:"
#define SIMPLE_MESSAGE "But first of all lets try to simplify it!"
#define OPTIMISING_MESSAGE "WOW!!! It has become easier, look at this"
#define DERIVATI_MESSAGE "Now we're going to find the derivative of this part of our function:"
#define NOSIMPLIER_MESSAGE "LOL! No more easy"
#define YESSIMPLIER_MESSAGE "EEEE! That looks like really easy nice"
#define SIMPLIFY_DERIVATIVE_MESSAGE "Lets try to simplify our REALLY BIG derivative"
#define DERIVATING_MESSAGE "As you can see, that equalation is right!"

#define NUM_DERIVATING_MESSAGE "Only a fool does not know that the derivative of NUMBER is 0!"
#define VAR_DERIVATING_MESSAGE "It's as easy as a breathe to understand that the derivative of VARIABLE is 1!"
#define ADD_DERIVATING_MESSAGE "As we know the derivative of ADDITION is ADDITION of derivatives!"
#define SUB_DERIVATING_MESSAGE "Everybody knows that the derivative of SUBTRACT is SUBTRACT of derivatives!"
#define MUL_DERIVATING_MESSAGE "It's clear that the derivative of MULTIPLICATION is given by formula\\
                                \\[(f(x) \\cdot g(x))' = f'(x) \\cdot g(x) + g'(x) \\cdot f(x)\\]"
#define DIV_DERIVATING_MESSAGE "Not difficult to notice that the derivative of DIVISION is given by formula\\
                                \\[\\left( \\frac {f(x)}{g(x)} \\right)' = \\frac {f'(x) \\cdot g(x) - g'(x) \\cdot f(x)} {g ^ 2(x)}\\]"
#define SIN_DERIVATING_MESSAGE "SINUS is really difficult function that's why we should use formula\\
                                \\[(\\sin(f(x))' = \\cos(f(x)) \\cdot f'(x) \\]"
#define COS_DERIVATING_MESSAGE "COSINUS is not very simple function, we'd use special formula\\
                                \\[(\\cos(f(x))' = -\\sin(f(x)) \\cdot f'(x) \\]"
#define TAN_DERIVATING_MESSAGE "TANGENT... Difficult... We'd better to use formula\\
                                \\[(\\tg(f(x))' = \\frac{1}{\\cos ^2 (f(x))} \\cdot f'(x) \\]"
#define COT_DERIVATING_MESSAGE "COTANGENT - useless shit because we can use $\\frac{1}{tg(f(x))}$! Howewer\\
                                \\[(\\ctg(f(x))' = \\frac{-1}{\\sin ^2 (f(x))} \\cdot f'(x) \\]"
#define EXP_DERIVATING_MESSAGE "EXPONENT is mystery function because\\
                                \\[(e^{f(x)})' = e^{f(x)} \\cdot f'(x) \\]"
#define LN_DERIVATING_MESSAGE "NATURAL LOGARITHM is conceited function because it's just LOGARITHM\nof base e but\\
                                \\[(\\ln(f(x)))' = \\frac{1}{f(x)} \\cdot f'(x) \\]"
#define LG_DERIVATING_MESSAGE "DECIMAL LOGARITHM is the best LOGARITHM because it's used for stellar magnetudes and decibels. So\\
                                \\[(\\lg(f(x)))' = \\frac{1}{f(x) \\cdot ln(10)} \\cdot f'(x) \\]"
#define LOG_EASY_DERIVATING_MESSAGE "LOGARITHM with numeric base is not wery difficult because\\
                                    \\[(\\log_{a}{(f(x))})' = \\frac{1}{f(x) \\cdot ln(a)} \\cdot f'(x) \\]"
#define LOG_DIFF_DERIVATING_MESSAGE "LOGARITHM with functional base is stupid because\\
                                    \\[(\\log_{g(x)}{f(x)})' =\\left(\\frac{ln(f(x))}{ln(g(x))}\\right)'\\]"
#define POW_NUM_DERIVATING_MESSAGE "Number to the POWER of function has a really strange derivative\\
                                    \\[\\left(a^{f(x)}\\right)' = a^{f(x)} \\cdot ln(a) \\cdot f'(x)\\]"
#define POW_FUNC_DERIVATING_MESSAGE "Function to the POWER of number is interesting\\
                                        \\[\\left(f^a(x)\\right)' = a \\cdot f^{a - 1}(x) \\cdot f'(x)\\]"
#define POW_DIFF_DERIVATING_MESSAGE "FUNCTION TO THE POWER OF FUNCTION!!! Are you crazy?! It's actually\\
                                    \\[\\left(f^{g(x)}(x)\\right)' = f^{g(x)}(x) \\cdot \\left(f'(x)\\
                                    \\cdot \\frac{g(x)}{f(x)} + g'(x) \\cdot \\ln(f(x))\\right) \\]"
const char** Messages ();
const int Number_of_mess = 10;
const char** MESSAGES = Messages ();
