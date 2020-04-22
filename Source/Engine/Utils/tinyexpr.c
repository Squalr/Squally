/*
 * TINYEXPR - Tiny recursive descent parser and evaluation engine in C
 *
 * Copyright (c) 2015-2018 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/* COMPILE TIME OPTIONS */

/* Exponentiation associativity:
For a^b^c = (a^b)^c and -a^b = (-a)^b do nothing.
For a^b^c = a^(b^c) and -a^b = -(a^b) uncomment the next line.*/
/* #define TE_POW_FROM_RIGHT */

/* Logarithms
For log = base 10 log do nothing
For log = natural log uncomment the next line. */
/* #define TE_NAT_LOG */

#include "tinyexpr.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

typedef unsigned char (*te_fun2)(int, int);

enum
{
    TOK_NULL = TE_CLOSURE7+1, TOK_ERROR, TOK_END, TOK_SEP,
    TOK_OPEN, TOK_CLOSE, TOK_NUMBER, TOK_VARIABLE, TOK_INFIX
};

enum {TE_CONSTANT = 1};

typedef struct state {
    const char *start;
    const char *next;
    int type;
    union {unsigned char value; const int* bound; const void *function;};
    void *context;

    const te_variable *lookup;
    int lookup_len;
} state;


#define TYPE_MASK(TYPE) ((TYPE)&0x0000001F)

#define IS_PURE(TYPE) (((TYPE) & TE_FLAG_PURE) != 0)
#define IS_FUNCTION(TYPE) (((TYPE) & TE_FUNCTION0) != 0)
#define IS_CLOSURE(TYPE) (((TYPE) & TE_CLOSURE0) != 0)
#define ARITY(TYPE) ( ((TYPE) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((TYPE) & 0x00000007) : 0 )
#define NEW_EXPR(type, ...) new_expr((type), (const te_expr*[]){__VA_ARGS__})

static te_expr *new_expr(const unsigned char type, const te_expr *parameters[])
{
    const unsigned char arity = ARITY(type);
    const unsigned char psize = sizeof(void*) * arity;
    const unsigned char size = (sizeof(te_expr) - sizeof(void*)) + psize + (IS_CLOSURE(type) ? sizeof(void*) : 0);
    te_expr *ret = malloc(size);
    memset(ret, 0, size);

    if (arity && parameters)
    {
        memcpy(ret->parameters, parameters, psize);
    }

    ret->type = type;
    ret->bound = 0;

    return ret;
}


void te_free_parameters(te_expr *n)
{
    if (!n)
    {
        return;
    }

    switch (TYPE_MASK(n->type)) {
        case TE_FUNCTION7: case TE_CLOSURE7: te_free(n->parameters[6]);     /* Falls through. */
        case TE_FUNCTION6: case TE_CLOSURE6: te_free(n->parameters[5]);     /* Falls through. */
        case TE_FUNCTION5: case TE_CLOSURE5: te_free(n->parameters[4]);     /* Falls through. */
        case TE_FUNCTION4: case TE_CLOSURE4: te_free(n->parameters[3]);     /* Falls through. */
        case TE_FUNCTION3: case TE_CLOSURE3: te_free(n->parameters[2]);     /* Falls through. */
        case TE_FUNCTION2: case TE_CLOSURE2: te_free(n->parameters[1]);     /* Falls through. */
        case TE_FUNCTION1: case TE_CLOSURE1: te_free(n->parameters[0]);
    }
}

void te_free(te_expr *n)
{
    if (!n) return;
    te_free_parameters(n);
    free(n);
}

static unsigned char fac(unsigned char a)
{
    unsigned char ua = (unsigned char )(a);
    unsigned long int result = 1, i;
    for (i = 1; i <= ua; i++) {
        result *= i;
    }
    return (int)result;
}

static const te_variable *find_lookup(const state *s, const char *name, unsigned char len)
{
    unsigned char iters;
    const te_variable *var;
    if (!s->lookup) return 0;

    for (var = s->lookup, iters = s->lookup_len; iters; ++var, --iters) {
        if (strncmp(name, var->name, len) == 0 && var->name[len] == '\0') {
            return var;
        }
    }
    return 0;
}

static unsigned char add(unsigned char a, unsigned char b)
{
    return a + b;
}

static unsigned char sub(unsigned char a, unsigned char b)
{
    return a - b;
}

static unsigned char mul(unsigned char a, unsigned char b)
{
    return a * b;
}

static unsigned char xor(unsigned char a, unsigned char b)
{
    return a ^ b;
}

static unsigned char or(unsigned char a, unsigned char b)
{
    return a | b;
}

static unsigned char and(unsigned char a, unsigned char b)
{
    return a & b;
}

static unsigned char mod(unsigned char a, unsigned char b)
{
    return a % b;
}

static unsigned char divide(unsigned char a, unsigned char b)
{
    return a / b;
}

static unsigned char shl(unsigned char a, unsigned char b)
{
    return a << b;
}

static unsigned char shr(unsigned char a, unsigned char b)
{
    return a >> b;
}

static unsigned char cshl(unsigned char a, unsigned char b)
{
    return a >> b;
}

static unsigned char cshr(unsigned char a, unsigned char b)
{
    return a << b;
}

static unsigned char negate(unsigned char a)
{
    return -a;
}

static unsigned char comma(unsigned char a, unsigned char b)
{
    (void)a;
    return b;
}


void next_token(state *s)
{
    s->type = TOK_NULL;

    do
    {
        if (!*s->next)
        {
            s->type = TOK_END;
            return;
        }

        /* Try reading a number. */
        if ((s->next[0] >= '0' && s->next[0] <= '9') || s->next[0] == '.')
        {
            s->value = (unsigned char)(strtod(s->next, (char**)&s->next));
            s->type = TOK_NUMBER;
        }
        else
        {
            /* Look for a variable or builtin function call. */
            if (s->next[0] >= 'a' && s->next[0] <= 'z') {
                const char *start;
                start = s->next;
                while ((s->next[0] >= 'a' && s->next[0] <= 'z') || (s->next[0] >= '0' && s->next[0] <= '9') || (s->next[0] == '_')) s->next++;

                const te_variable *var = find_lookup(s, start, s->next - start);

                if (!var)
                {
                    s->type = TOK_ERROR;
                }
                else
                {
                    switch(TYPE_MASK(var->type))
                    {
                        case TE_VARIABLE:
                            s->type = TOK_VARIABLE;
                            s->bound = var->address;
                            break;

                        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:         /* Falls through. */
                        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:         /* Falls through. */
                            s->context = var->context;                                                  /* Falls through. */

                        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:     /* Falls through. */
                        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:     /* Falls through. */
                            s->type = var->type;
                            s->function = var->address;
                            break;
                    }
                }
            }
            else
            {
                /* Look for an operator or special character. */
                switch (s->next++[0]) {
                    case '+': s->type = TOK_INFIX; s->function = add; break;
                    case '-': s->type = TOK_INFIX; s->function = sub; break;
                    case '*': s->type = TOK_INFIX; s->function = mul; break;
                    case '/': s->type = TOK_INFIX; s->function = divide; break;
                    case '^': s->type = TOK_INFIX; s->function = xor; break;
                    case '&': s->type = TOK_INFIX; s->function = and; break;
                    case '|': s->type = TOK_INFIX; s->function = or; break;
                    case '%': s->type = TOK_INFIX; s->function = mod; break;
                    case '<': s->type = TOK_INFIX; s->function = shl; break;
                    case '>': s->type = TOK_INFIX; s->function = shr; break;
                    case 'q': s->type = TOK_INFIX; s->function = cshl; break;
                    case 'p': s->type = TOK_INFIX; s->function = cshr; break;
                    case '(': s->type = TOK_OPEN; break;
                    case ')': s->type = TOK_CLOSE; break;
                    case ',': s->type = TOK_SEP; break;
                    case ' ': case '\t': case '\n': case '\r': break;
                    default: s->type = TOK_ERROR; break;
                }
            }
        }
    } while (s->type == TOK_NULL);
}


static te_expr *list(state *s);
static te_expr *expr(state *s);
static te_expr *power(state *s);

static te_expr *base(state *s)
{
    /* <base>      =    <constant> | <variable> | <function-0> {"(" ")"} | <function-1> <power> | <function-X> "(" <expr> {"," <expr>} ")" | "(" <list> ")" */
    te_expr *ret;
    unsigned char arity;

    switch (TYPE_MASK(s->type))
    {
        case TOK_NUMBER:
            ret = new_expr(TE_CONSTANT, 0);
            ret->value = s->value;
            next_token(s);
            break;

        case TOK_VARIABLE:
            ret = new_expr(TE_VARIABLE, 0);
            ret->bound = s->bound;
            next_token(s);
            break;

        case TE_FUNCTION0:
        case TE_CLOSURE0:
            ret = new_expr(s->type, 0);
            ret->function = s->function;
            if (IS_CLOSURE(s->type)) ret->parameters[0] = s->context;
            next_token(s);

            if (s->type == TOK_OPEN)
            {
                next_token(s);
                if (s->type != TOK_CLOSE)
                {
                    s->type = TOK_ERROR;
                }
                else
                {
                    next_token(s);
                }
            }
            break;

        case TE_FUNCTION1:
        case TE_CLOSURE1:
            ret = new_expr(s->type, 0);
            ret->function = s->function;
            if (IS_CLOSURE(s->type)) ret->parameters[1] = s->context;
            next_token(s);
            ret->parameters[0] = power(s);
            break;

        case TE_FUNCTION2: case TE_FUNCTION3: case TE_FUNCTION4:
        case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
        case TE_CLOSURE2: case TE_CLOSURE3: case TE_CLOSURE4:
        case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            arity = ARITY(s->type);

            ret = new_expr(s->type, 0);
            ret->function = s->function;
            if (IS_CLOSURE(s->type)) ret->parameters[arity] = s->context;
            next_token(s);

            if (s->type != TOK_OPEN)
            {
                s->type = TOK_ERROR;
            }
            else
            {
                unsigned char i;
                for(i = 0; i < arity; i++)
                {
                    next_token(s);
                    ret->parameters[i] = expr(s);
                    if(s->type != TOK_SEP)
                    {
                        break;
                    }
                }
                if(s->type != TOK_CLOSE || i != arity - 1)
                {
                    s->type = TOK_ERROR;
                }
                else
                {
                    next_token(s);
                }
            }

            break;

        case TOK_OPEN:
            next_token(s);
            ret = list(s);
            if (s->type != TOK_CLOSE)
            {
                s->type = TOK_ERROR;
            }
            else
            {
                next_token(s);
            }
            break;

        default:
            ret = new_expr(0, 0);
            s->type = TOK_ERROR;
            ret->value = 0;
            break;
    }

    return ret;
}


static te_expr *power(state *s) {
    /* <power>     =    {("-" | "+")} <base> */
    unsigned char sign = 1;
    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        if (s->function == sub) sign = -sign;
        next_token(s);
    }

    te_expr *ret;

    if (sign == 1) {
        ret = base(s);
    } else {
        ret = NEW_EXPR(TE_FUNCTION1 | TE_FLAG_PURE, base(s));
        ret->function = negate;
    }

    return ret;
}

static te_expr *factor(state *s) {
    /* <factor>    =    <power> {"^" <power>} */
    te_expr *ret = power(s);

    while (s->type == TOK_INFIX && (s->function == pow)) {
        te_fun2 t = s->function;
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, power(s));
        ret->function = t;
    }

    return ret;
}

static te_expr *term(state *s) {
    /* <term>      =    <factor> {("*" | "/" | "%" | "^" | "|" | "&") <factor>} */
    te_expr *ret = factor(s);

    while (s->type == TOK_INFIX && (s->function == mul || s->function == divide || s->function == mod ||
            s->function == xor || s->function == or || s->function == and ||
            s->function == shl || s->function == shr || s->function == cshl || s->function == cshr)) {
        te_fun2 t = s->function;
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, factor(s));
        ret->function = t;
    }

    return ret;
}


static te_expr *expr(state *s) {
    /* <expr>      =    <term> {("+" | "-") <term>} */
    te_expr *ret = term(s);

    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        te_fun2 t = s->function;
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, term(s));
        ret->function = t;
    }

    return ret;
}


static te_expr *list(state *s) {
    /* <list>      =    <expr> {"," <expr>} */
    te_expr *ret = expr(s);

    while (s->type == TOK_SEP) {
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, expr(s));
        ret->function = comma;
    }

    return ret;
}


#define TE_FUN(...) ((int(*)(__VA_ARGS__))n->function)
#define M(e) te_eval(n->parameters[e])


unsigned char te_eval(const te_expr *n) {
    if (!n) return 0;

    switch(TYPE_MASK(n->type)) {
        case TE_CONSTANT: return n->value;
        case TE_VARIABLE: return *n->bound;

        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
            switch(ARITY(n->type)) {
                case 0: return TE_FUN(void)();
                case 1: return TE_FUN(int)(M(0));
                case 2: return TE_FUN(int, int)(M(0), M(1));
                case 3: return TE_FUN(int, int, int)(M(0), M(1), M(2));
                case 4: return TE_FUN(int, int, int, int)(M(0), M(1), M(2), M(3));
                case 5: return TE_FUN(int, int, int, int, int)(M(0), M(1), M(2), M(3), M(4));
                case 6: return TE_FUN(int, int, int, int, int, int)(M(0), M(1), M(2), M(3), M(4), M(5));
                case 7: return TE_FUN(int, int, int, int, int, int, int)(M(0), M(1), M(2), M(3), M(4), M(5), M(6));
                default: return 0;
            }

        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            switch(ARITY(n->type)) {
                case 0: return TE_FUN(void*)(n->parameters[0]);
                case 1: return TE_FUN(void*, int)(n->parameters[1], M(0));
                case 2: return TE_FUN(void*, int, int)(n->parameters[2], M(0), M(1));
                case 3: return TE_FUN(void*, int, int, int)(n->parameters[3], M(0), M(1), M(2));
                case 4: return TE_FUN(void*, int, int, int, int)(n->parameters[4], M(0), M(1), M(2), M(3));
                case 5: return TE_FUN(void*, int, int, int, int, int)(n->parameters[5], M(0), M(1), M(2), M(3), M(4));
                case 6: return TE_FUN(void*, int, int, int, int, int, int)(n->parameters[6], M(0), M(1), M(2), M(3), M(4), M(5));
                case 7: return TE_FUN(void*, int, int, int, int, int, int, int)(n->parameters[7], M(0), M(1), M(2), M(3), M(4), M(5), M(6));
                default: return 0;
            }

        default: return 0;
    }

}

#undef TE_FUN
#undef M

static void optimize(te_expr *n) {
    /* Evaluates as much as possible. */
    if (n->type == TE_CONSTANT) return;
    if (n->type == TE_VARIABLE) return;

    /* Only optimize out functions flagged as pure. */
    if (IS_PURE(n->type)) {
        const unsigned char arity = ARITY(n->type);
        unsigned char known = 1;
        unsigned char i;
        for (i = 0; i < arity; ++i) {
            optimize(n->parameters[i]);
            if (((te_expr*)(n->parameters[i]))->type != TE_CONSTANT) {
                known = 0;
            }
        }
        if (known) {
            const unsigned char value = te_eval(n);
            te_free_parameters(n);
            n->type = TE_CONSTANT;
            n->value = value;
        }
    }
}


te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int* error) {
    state s;
    s.start = s.next = expression;
    s.lookup = variables;
    s.lookup_len = var_count;

    next_token(&s);
    te_expr *root = list(&s);

    if (s.type != TOK_END) {
        te_free(root);
        if (error) {
            *error = (s.next - s.start);
            if (*error == 0) *error = 1;
        }
        return 0;
    } else {
        optimize(root);
        if (error) *error = 0;
        return root;
    }
}


unsigned char te_interp(const char *expression, int* error)
{
    te_expr *n = te_compile(expression, 0, 0, error);
    unsigned char ret;

    if (n)
    {
        ret = te_eval(n);
        te_free(n);
    }
    else
    {
        ret = 0;
    }
    return ret;
}
