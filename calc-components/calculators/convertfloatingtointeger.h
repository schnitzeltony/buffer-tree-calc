#ifndef CONVERTFLOATINGNUMBERTOINTEGER_H
#define CONVERTFLOATINGNUMBERTOINTEGER_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbase.h"
#include <memory>
#include <limits>

template <class F_TYPE, class I_TYPE>
class ConvertFloatingToInteger : public CalculatorBase<I_TYPE>
{
public:
    ConvertFloatingToInteger(CALC_PTR(F_TYPE) input,
                             BUFFER_PTR(I_TYPE) output,
                             AbstractAccessStrategy::Ptr accessStrategy,
                             I_TYPE scalingFactor = m_defaultScalingFactor);

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<ConvertFloatingToInteger<F_TYPE, I_TYPE>> createWithOutBuffer(CALC_PTR(F_TYPE) floatIn, int bufferSize,
                                                                                         I_TYPE scalingFactor = m_defaultScalingFactor);

    static constexpr I_TYPE m_defaultScalingFactor = std::numeric_limits<I_TYPE>::max();

private:
    void doCalc(int sampleCount);
    I_TYPE m_scalingFactor;
    BUFFER_PTR(F_TYPE) m_inBuff;
};

#include "implementation-headers/convertfloatingtointeger_impl.h"

#endif // CONVERTFLOATINGNUMBERTOINTEGER_H
