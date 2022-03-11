#ifndef CONVERTFLOATINGNUMBERTOINTEGER_H
#define CONVERTFLOATINGNUMBERTOINTEGER_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbasein1.h"
#include <memory>
#include <limits>

template <class F_TYPE, class I_TYPE>
class ConvertFloatingToInteger : public CalculatorBaseIn1<F_TYPE, I_TYPE>
{
public:
    ConvertFloatingToInteger(CALC_PTR(F_TYPE) input,
                             BUFFER_PTR(I_TYPE) output,
                             AbstractAccessStrategy::Ptr accessStrategy,
                             I_TYPE scalingFactor = m_defaultScalingFactor);
    virtual void doCalc(int sampleCount) override;

    static constexpr I_TYPE m_defaultScalingFactor = std::numeric_limits<I_TYPE>::max();

private:
    I_TYPE m_scalingFactor;
};

template <class F_TYPE, class I_TYPE>
CALC_PTR(I_TYPE) createCalcFloatingToInteger(CALC_PTR(F_TYPE) calcIn, int bufferSize);

#include "implementation-headers/convertfloatingtointeger_impl.h"

#endif // CONVERTFLOATINGNUMBERTOINTEGER_H
