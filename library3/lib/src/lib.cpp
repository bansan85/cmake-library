#include <library/lib.h>
#include <library3/lib.h>

namespace Lib3 {
LibCalc::LibCalc(double c) : c_(c) {}

double LibCalc::Calc() const {
  Lib::LibCalc tmp(c_);
  return tmp.Calc();
}
} // namespace Lib3
