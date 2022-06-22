#include <library3/lib.h>

int main() {
  Lib3::LibCalc calc(23.4);

  return static_cast<int>(calc.Calc()) - 23;
}
