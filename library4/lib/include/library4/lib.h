#pragma once

#include <library4/subfolder/helper.h>

namespace Lib4 {
class LibCalc {
public:
  LIBRARY4_EXPORT LibCalc(double c);

  LIBRARY4_EXPORT double Calc() const;

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
