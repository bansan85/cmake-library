#pragma once

#include <library2/subfolder/helper.h>

namespace Lib2 {
class LibCalc {
public:
  LIBRARY2_EXPORT LibCalc(double c);

  LIBRARY2_EXPORT double Calc() const;

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

} // namespace Lib2
