#ifndef CONVERTINTEGERTOFLOATING_IMPL_H
#define CONVERTINTEGERTOFLOATING_IMPL_H

#include "convertintegertofloating.h"


template <class I_TYPE, class F_TYPE>
ConvertIntegerToFloating<I_TYPE, F_TYPE>::ConvertIntegerToFloating(CALC_PTR(I_TYPE) input,
                                                                   BUFFER_PTR(F_TYPE) output,
                                                                   AbstractAccessStrategy::Ptr accessStrategy,
                                                                   F_TYPE scalingFactor) :
    CalculatorBase<F_TYPE>(std::vector<CalcInterface::Ptr> {input}, output, accessStrategy),
    m_inBuff(input->getOutputBuffer())
{
    if(!scalingFactor) {
        throw division_by_zero_exception();
    }
    m_scalingFactor = scalingFactor;
}

template <class I_TYPE, class F_TYPE>
void ConvertIntegerToFloating<I_TYPE, F_TYPE>::doCalc(int sampleCount)
{
    BUFFER_PTR(F_TYPE) outBuff = CalculatorBase<F_TYPE>::getOutputBuffer();
    for(int i=0, currSample = CalculatorBase<F_TYPE>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
        outBuff->at(currSample) =
                ((F_TYPE)m_inBuff->at(currSample) / (F_TYPE)m_scalingFactor);
    }
}

template <class I_TYPE, class F_TYPE>
template <typename ACCESS_STRATEGY>
std::shared_ptr<ConvertIntegerToFloating<I_TYPE, F_TYPE>> ConvertIntegerToFloating<I_TYPE, F_TYPE>::createWithOutBuffer(CALC_PTR(I_TYPE) floatIn,
                                                                                                                        int bufferSize,
                                                                                                                        F_TYPE scalingFactor)
{
    return std::make_shared<ConvertIntegerToFloating<I_TYPE, F_TYPE>>(floatIn,
                                                            std::make_shared<BufferTemplate<F_TYPE>>(bufferSize),
                                                            createAccessStrategy<ACCESS_STRATEGY>(),
                                                            scalingFactor);
}

#endif // CONVERTINTEGERTOFLOATING_IMPL_H
