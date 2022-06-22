#pragma once

#include <library4/subfolder/helper.h>

namespace Lib4 {
class libtest4_PUBLIC LibCalc {
public:
  LibCalc(double c);

  double Calc() const;

private:
  double c_;
};

template <typename T> class LibCalcT {
public:
  LibCalcT(T c) : c_(c) {}

  T Calc() const { return c_; }

private:
  T c_;
};

} // namespace Lib3
