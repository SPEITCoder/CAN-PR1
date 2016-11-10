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
  // TODO: implement
}

// add two binary numbers and an input carry, returning the sum (s) and
// carry (c)
void full_adder(char a, char b, char c_in, char *s, char *c)
{
  // TODO: implement
}

// perform an addition of two unsigned N-bit binary numbers, represented as
// strings
void addition(char *a, char *b, char *s)
{
  // TODO: implement
}

// perform an addition of two signed N-bit binary numbers, represented as
// strings, and perform an overflow check.
void addition_signed(char *a, char *b, char *s)
{
  // TODO: implement
}

// negate the given N-bit binary number, represented as strings. The negated
// value is returned through parameter n.
void negate(char *a, char *n)
{
  // TODO: implement
}

// perform a subtraction of two N-bit binary numbers A and B.
void subtraction(char *a, char *b, char *s)
{
  // TODO: implement
}

// convert an input binary number represented as string to a fixed-width binary
// number of length N.
//
// in case the input string is not to long or is not a binary numnber, an error
// is signaled.
void to_binary(char *str, char *bin)
{
  unsigned int l = strlen(str);
  int error = 0;

  for(unsigned int i = 0; i < l; i++)
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

  // perform the addition
  addition(a, b, c);

  // TODO: call addition_signed, negate (for b), and  subtraction

  // print result
  printf("a:   %s\n", a);
  printf("b: + %s\n", b);
  printf("c:   %s\n", c);

  // TODO: print results of addition_signed, negate, and subtraction

  return 0;
}
