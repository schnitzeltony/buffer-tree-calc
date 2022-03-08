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
                             I_TYPE scalingFactor = m_defaultScalingFactor) :
        CalculatorBase<I_TYPE>(std::vector<CalcInterface::Ptr> {input}, output, accessStrategy),
        m_scalingFactor(scalingFactor),
        m_inBuff(input->getOutputBuffer())
    {
    };
    virtual void doCalc(int sampleCount) override
    {
        BUFFER_PTR(I_TYPE) outBuff = CalculatorBase<I_TYPE>::getOutputBuffer();
        for(int i=0, currSample = CalculatorBase<I_TYPE>::getSampleOffset();
                i<sampleCount;
                ++i, ++currSample) {
            F_TYPE temp = (m_inBuff->at(currSample) * (F_TYPE)m_scalingFactor);
            outBuff->at(currSample) =
                    (I_TYPE)(m_inBuff->at(currSample) * (F_TYPE)m_scalingFactor);
        }
    };

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


#endif // CONVERTFLOATINGNUMBERTOINTEGER_H
