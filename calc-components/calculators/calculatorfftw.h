#ifndef CALCULATORFFTW_H
#define CALCULATORFFTW_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"
#include <complex>
#include <functional>

template <class T>
class CalculatorFftw : public CalculatorBase<std::complex<T>>
{
public:
    CalculatorFftw(CALC_PTR(T) inReal,
                   BUFFER_PTR(std::complex<T>) outFft,
                   std::function<void(int)> doCalcHandler,
                   AbstractAccessStrategy::Ptr accessStrategy) :
        CalculatorBase<std::complex<T>>({inReal}, outFft, doCalcHandler, accessStrategy),
        m_inBuff(inReal->getOutputBuffer())
    {}
protected:
    BUFFER_PTR(T) m_inBuff;
};

#endif // CALCULATORFFTW_H
