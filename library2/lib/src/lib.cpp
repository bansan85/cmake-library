#include <library/lib.h>
#include <library2/lib.h>

namespace Lib2 {
LibCalc::LibCalc(double c) : c_(c) {}

double LibCalc::Calc() const {
  Lib::LibCalc tmp(c_);
  return tmp.Calc();
}
} // namespace Lib2
