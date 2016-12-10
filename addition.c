#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// define the bit width of the binary numbers that can be processed.
#define N 5

// string representing the name of the currently running program
char *program = NULL;

// check whether the charater is a '0' or a '1'
int is_binary(char a)
{
    return a == '1' || a == '0';
}

// perform a logical and of the binary numbers a and b
char and(char a, char b)
{
    assert(is_binary(a) && is_binary(b));
    if (a == '0' || b  == '0')
        return '0';
    else
        return '1';
}

// perform a logical or of the binary numbers a and b
char or(char a, char b)
{
    assert(is_binary(a) && is_binary(b));
    if (a == '1' || b  == '1')
        return '1';
    else
        return '0';
}

// perform a logical xor of the binary numbers a and b
char xor(char a, char b)
{
    assert(is_binary(a) && is_binary(b));
    if (a == b)
        return '0';
    else
        return '1';
}

// add two binary numbers, returning the sum (s) and carry (c)
void half_adder(char a, char b, char *s, char *c)
{
    *s = xor(a, b);     // xor operation to get the sum result of the current bit
    *c = and(a, b);     // and operation to get the carry to the next bit
}

// add two binary numbers and an input carry, returning the sum (s) and
// carry (c)
void full_adder(char a, char b, char c_in, char *s, char *c)
{
    char s1 = xor(a, b);
    *s = xor(c_in, s1);
    *c = or(and(a, b), and(c_in, s1));
}

// perform an addition of two unsigned N-bit binary numbers, represented as
// strings
void addition(char *a, char *b, char *s)
{
    char cin[N+2] = "000000";   // to store the carries
    for(int i = N - 1; i >= 0; i--)
        full_adder(a[i], b[i], cin[i+1], &s[i], &cin[i]);
    // printf("addtion:\n");
}

// perform an addition of two signed N-bit binary numbers, represented as
// strings, and perform an overflow check.
void addition_signed(char *a, char *b, char *s)
{
    addition(a, b, s);
    
    // Only if the two addends have the same sign, overflow occurs
    if(a[0] == b[0]){
        // Negative overflow
        if ((a[0] == 0) && (s[0] == 1)){
            fprintf(stderr, "overflow detected: %s\n",s);
            exit(2);
        }
        // Positive overflow
        if((a[0] == 1) && (s[0] = 0)){
            fprintf(stderr, "overflow detected: %s\n",s);
            exit(2);
        }
    }
}

// negate the given N-bit binary number, represented as strings. The negated
// value is returned through parameter n.
void negate(char *a, char *n)
{
    char a_copy[N+1];
    for(int i = 0; i < N+1; i++)
        a_copy[i] = a[i];
    if(!strcmp(a, "10000")){
        fprintf(stderr, "Positive overflow\n");
        exit(2);
    }     // Negate "10000" will overflow
    
    else{
        // turn all '1'(or '0') into '0'(or '1')
        for(int i = 0; i < N; i++)
            switch (a_copy[i]) {
                case '1':
                    a_copy[i] = '0';
                    break;
                    
                case '0':
                    a_copy[i] = '1';
                    break;
            }
        // added by 1
        char u[N+1] = "00001";
        addition(a_copy,u,n);
    }
}

// perform a subtraction of two N-bit binary numbers A and B.
void subtraction(char *a, char *b, char *s)
{
    char nb[N+1] = "00000";
    negate(b, nb);
   // printf("The temporal negate result is: %s\n",nb);
    addition_signed(a, nb, s);
}

// convert an input binary number represented as string to a fixed-width binary
// number of length N.
//
// in case the input string is not to long or is not a binary numnber, an error
// is signaled.
void to_binary(char *str, char *bin)
{
    size_t l = strlen(str);
    int error = 0;
    
    for(size_t i = 0; i < l; i++)
    {
        if (str[i] != '1' && str[i] != '0')
        {
            error = 1;
            break;
        }
    }
    if (l > N || error)
    {
        fprintf(stderr, "%s: invalid unsigned number: \"%s\"\n", program, str);
        exit(1);
    }
    
    memcpy(&bin[N - l], str, l);
}

// retrieve two input numbers from the command line arguments, perform an
// unsigned addition, and print the result.
int main(int argc, char **argv)
{
    // store name of currently running program
    program = argv[0];
    
    // check number of command line arguments, and signal an error.
    if (argc != 3)
    {
        fprintf(stderr, "%s: expecting two unsigned integer values as command line "
                "arguments.\n", program);
        return 2;
    }
    
    // get and initialize two input binary numbers
    char a[N + 1];
    char b[N + 1];
    memset(a, '0', N); a[N] = '\0';
    memset(b, '0', N); b[N] = '\0';
    to_binary(argv[1], &a[0]);
    to_binary(argv[2], &b[0]);
    
    // initialize the result binary number
    char c[N + 1];
    memset(c, '0', N); c[N] = '\0';
    char d[N + 1];
    memset(d, '0', N); d[N] = '\0';
    char n[N + 1];
    memset(n, '0', N); n[N] = '\0';
    char f[N + 1];
    memset(f, '0', N); f[N] = '\0';
    // perform the addition
    addition(a, b, c);
    

    // call addition_signed, negate (for b), and subtraction
    addition_signed(a, b, d);
    negate(b, n);
    subtraction(a, b, f);
    
    // print result of addition
    printf("addition:\n");
    printf("a:   %s\n", a);
    printf("b: + %s\n", b);
    printf("c:   %s\n", c);
    
    // print results of addition_signed
    printf("addition_signed:\n");
    printf("a:   %s\n", a);
    printf("b: + %s\n", b);
    printf("c:   %s\n", d);
    
    // print results of negate
    printf("negate:\n");
    printf("b: - %s\n", b);
    printf("n:   %s\n", n);

    // print results of subtraction
    printf("subtraction:\n");
    printf("a:   %s\n", a);
    printf("b: - %s\n", b);
    printf("c:   %s\n", f);

    
    return 0;
}