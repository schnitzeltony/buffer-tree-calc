#ifndef CONVERTINTEGERTOFLOATING_H
#define CONVERTINTEGERTOFLOATING_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbase.h"
#include <memory>
#include <limits>
#include <exception>

template <class I_TYPE, class F_TYPE>
class ConvertIntegerToFloating : public CalculatorBase<F_TYPE>
{
public:
    ConvertIntegerToFloating(CALC_PTR(I_TYPE) input,
                             BUFFER_PTR(F_TYPE) output,
                             AbstractAccessStrategy::Ptr accessStrategy,
                             F_TYPE scalingFactor = m_defaultScalingFactor);
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<ConvertIntegerToFloating<I_TYPE, F_TYPE>> createWithOutBuffer(CALC_PTR(I_TYPE) floatIn, int bufferSize,
                                                                                         F_TYPE scalingFactor = m_defaultScalingFactor);

    static constexpr F_TYPE m_defaultScalingFactor = (F_TYPE)std::numeric_limits<I_TYPE>::max();

private:
    F_TYPE m_scalingFactor;
    BUFFER_PTR(I_TYPE) m_inBuff;
};

#include "implementation-headers/convertintegertofloating_impl.h"

#endif // CONVERTINTEGERTOFLOATING_H
