#include <library2/lib.h>

int main() {
  Lib2::LibCalc calc(23.4);

  return static_cast<int>(calc.Calc()) - 23;
}
