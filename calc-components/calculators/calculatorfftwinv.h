#ifndef CALCULATORFFTWINV_H
#define CALCULATORFFTWINV_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"
#include <complex>

template <class T>
class CalculatorFftwInv : public CalculatorBase<T>
{
public:
    CalculatorFftwInv(CALC_PTR(std::complex<T>) inFft,
                      BUFFER_PTR(T) outReal,
                      std::function<void(int)> doCalcHandler,
                      AbstractAccessStrategy::Ptr accessStrategy) :
        CalculatorBase<T>({inFft}, outReal, doCalcHandler, accessStrategy),
        m_inBuff(inFft->getOutputBuffer())
    {}
protected:
    BUFFER_PTR(std::complex<T>) m_inBuff;
};


#endif // CALCULATORFFTWINV_H
