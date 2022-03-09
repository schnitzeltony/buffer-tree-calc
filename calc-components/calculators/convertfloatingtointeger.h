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
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<ConvertFloatingToInteger<F_TYPE, I_TYPE>> createWithOutBuffer(CALC_PTR(F_TYPE) floatIn, int bufferSize,
                                                                                         I_TYPE scalingFactor = m_defaultScalingFactor)
    {
        return std::make_shared<ConvertFloatingToInteger<F_TYPE, I_TYPE>>(floatIn,
                                                                std::make_shared<BufferTemplate<I_TYPE>>(bufferSize),
                                                                createAccessStrategy<ACCESS_STRATEGY>(),
                                                                scalingFactor);
    }

    static constexpr I_TYPE m_defaultScalingFactor = std::numeric_limits<I_TYPE>::max();

private:
    I_TYPE m_scalingFactor;
    BUFFER_PTR(F_TYPE) m_inBuff;
};

#include "convertfloatingtointeger_impl.h"

#endif // CONVERTFLOATINGNUMBERTOINTEGER_H
