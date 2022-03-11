#ifndef CALCULATORBASEIN1_H
#define CALCULATORBASEIN1_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbase.h"
#include <memory>

template <class TYPE_IN, class TYPE_OUT>
class CalculatorBaseIn1 : public CalculatorBase<TYPE_OUT>
{
public:
    CalculatorBaseIn1(CALC_PTR(TYPE_IN) calcIn,
                      BUFFER_PTR(TYPE_OUT) buffOut,
                      AbstractAccessStrategy::Ptr accessStrategy);

    //template <class ACCESS_STRATEGY>
    //static CALC_PTR(TYPE_OUT) createWithOutBuffer(CALC_PTR(TYPE_IN) calcIn, int bufferSize);

protected:
    BUFFER_PTR(TYPE_IN) m_inBuff;
};

template <class CONCRETE, class TYPE_IN, class TYPE_OUT, class ACCESS_STRATEGY>
static CALC_PTR(TYPE_OUT) createCalcWithBufferIn1(CALC_PTR(TYPE_IN) calcIn, int bufferSize);


#include "calculatorbasein1_impl.h"

#endif // CALCULATORBASEIN1_H
