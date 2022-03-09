#ifndef CONVERTFLOATINGTOINTEGER_IMPL_H
#define CONVERTFLOATINGTOINTEGER_IMPL_H

#include "calc-components/calculators/convertfloatingtointeger.h"

template <class F_TYPE, class I_TYPE>
ConvertFloatingToInteger<F_TYPE, I_TYPE>::ConvertFloatingToInteger(CALC_PTR(F_TYPE) input,
                                                                   BUFFER_PTR(I_TYPE) output,
                                                                   AbstractAccessStrategy::Ptr accessStrategy,
                                                                   I_TYPE scalingFactor) :
    CalculatorBase<I_TYPE>(std::vector<CalcInterface::Ptr> {input}, output, accessStrategy),
    m_scalingFactor(scalingFactor),
    m_inBuff(input->getOutputBuffer())
{
}

template <class F_TYPE, class I_TYPE>
void ConvertFloatingToInteger<F_TYPE, I_TYPE>::doCalc(int sampleCount)
{
    BUFFER_PTR(I_TYPE) outBuff = CalculatorBase<I_TYPE>::getOutputBuffer();
    for(int i=0, currSample = CalculatorBase<I_TYPE>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
        outBuff->at(currSample) =
                (I_TYPE)((double)m_inBuff->at(currSample) * (double)m_scalingFactor);
    }
}

template <class F_TYPE, class I_TYPE>
template <typename ACCESS_STRATEGY>
std::shared_ptr<ConvertFloatingToInteger<F_TYPE, I_TYPE>> ConvertFloatingToInteger<F_TYPE, I_TYPE>::createWithOutBuffer(CALC_PTR(F_TYPE) floatIn,
                                                                                                                        int bufferSize,
                                                                                                                        I_TYPE scalingFactor)
{
    return std::make_shared<ConvertFloatingToInteger<F_TYPE, I_TYPE>>(floatIn,
                                                                      std::make_shared<BufferTemplate<I_TYPE>>(bufferSize),
                                                                      createAccessStrategy<ACCESS_STRATEGY>(),
                                                                      scalingFactor);
}

#endif // CONVERTFLOATINGTOINTEGER_IMPL_H
