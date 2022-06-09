#include <lib.h>

namespace Lib {
LibCalc::LibCalc(double c) : c_(c) {}

double LibCalc::Calc() const { return c_; }
} // namespace Lib
