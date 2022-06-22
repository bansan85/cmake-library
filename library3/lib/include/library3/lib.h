#pragma once

#include <library3/subfolder/helper.h>

namespace Lib3 {
class libtest3_PUBLIC LibCalc {
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
