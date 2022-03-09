#ifndef CONVERTINTEGERTOFLOATING_H
#define CONVERTINTEGERTOFLOATING_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbase.h"
#include <memory>
#include <limits>

template <class I_TYPE, class F_TYPE>
class ConvertIntegerToFloating : public CalculatorBase<F_TYPE>
{
public:
    ConvertIntegerToFloating(CALC_PTR(I_TYPE) input,
                             BUFFER_PTR(F_TYPE) output,
                             AbstractAccessStrategy::Ptr accessStrategy,
                             F_TYPE scalingFactor = m_defaultScalingFactor) :
        CalculatorBase<F_TYPE>(std::vector<CalcInterface::Ptr> {input}, output, accessStrategy),
        m_scalingFactor(scalingFactor),
        m_inBuff(input->getOutputBuffer())
    {
    };
    virtual void doCalc(int sampleCount) override
    {
        BUFFER_PTR(F_TYPE) outBuff = CalculatorBase<F_TYPE>::getOutputBuffer();
        for(int i=0, currSample = CalculatorBase<F_TYPE>::getSampleOffset();
                i<sampleCount;
                ++i, ++currSample) {
            outBuff->at(currSample) =
                    (F_TYPE)((double)m_inBuff->at(currSample) / (double)m_scalingFactor);
        }
    };

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<ConvertIntegerToFloating<I_TYPE, F_TYPE>> createWithOutBuffer(CALC_PTR(I_TYPE) floatIn, int bufferSize,
                                                                                         F_TYPE scalingFactor = m_defaultScalingFactor)
    {
        return std::make_shared<ConvertIntegerToFloating<I_TYPE, F_TYPE>>(floatIn,
                                                                std::make_shared<BufferTemplate<F_TYPE>>(bufferSize),
                                                                createAccessStrategy<ACCESS_STRATEGY>(),
                                                                scalingFactor);
    }

    static constexpr F_TYPE m_defaultScalingFactor = (F_TYPE)std::numeric_limits<I_TYPE>::max();

private:
    F_TYPE m_scalingFactor;
    BUFFER_PTR(I_TYPE) m_inBuff;
};

#endif // CONVERTINTEGERTOFLOATING_H
