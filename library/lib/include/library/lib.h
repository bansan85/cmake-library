#pragma once

#include <library/subfolder/helper.h>

namespace Lib {
class LibCalc {
public:
  LIBRARY_EXPORT LibCalc(double c);

  LIBRARY_EXPORT double Calc() const;

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

} // namespace Lib
