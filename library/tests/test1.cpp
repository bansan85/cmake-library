#include <lib.h>

int main() {
  Lib::LibCalc calc(23.4);

  return static_cast<int>(calc.Calc()) - 23;
}
