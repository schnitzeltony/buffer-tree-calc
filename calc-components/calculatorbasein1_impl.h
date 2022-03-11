#ifndef CALCULATORBASEIN1_IMPL_H
#define CALCULATORBASEIN1_IMPL_H

#include "calculatorbasein1.h"

template <class TYPE_IN, class TYPE_OUT>
CalculatorBaseIn1<TYPE_IN, TYPE_OUT>::CalculatorBaseIn1(CALC_PTR(TYPE_IN) calcIn,
                                                        BUFFER_PTR(TYPE_OUT) buffOut,
                                                        AbstractAccessStrategy::Ptr accessStrategy) :
    CalculatorBase<TYPE_OUT>(std::vector<CalcInterface::Ptr> {calcIn}, buffOut, accessStrategy),
    m_inBuff(calcIn->getOutputBuffer())
{
}

template <class CONCRETE, class TYPE_IN, class TYPE_OUT, class ACCESS_STRATEGY>
CALC_PTR(TYPE_OUT) createCalcWithBufferIn1(CALC_PTR(TYPE_IN) calcIn, int bufferSize)
{
    return std::make_shared<CONCRETE>(calcIn,
                                      std::make_shared<BufferTemplate<TYPE_OUT>>(bufferSize),
                                      createAccessStrategy<ACCESS_STRATEGY>());
}

#endif // CALCULATORBASEIN1_IMPL_H
