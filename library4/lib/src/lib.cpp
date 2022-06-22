#include <library2/lib.h>
#include <library3/lib.h>
#include <library4/lib.h>

namespace Lib4 {
LibCalc::LibCalc(double c) : c_(c) {}

double LibCalc::Calc() const {
  Lib2::LibCalc tmp2(c_);
  Lib3::LibCalc tmp3(c_);
  return tmp2.Calc() + (tmp2.Calc() - tmp3.Calc());
}
} // namespace Lib4
