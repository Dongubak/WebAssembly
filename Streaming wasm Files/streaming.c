#include <emscripten.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int idiv(int a, int b);

EMSCRIPTEN_KEEPALIVE
int sumOfNInts(int n)
{
  return idiv(mul(n, add(n, 1)), 2);
}
