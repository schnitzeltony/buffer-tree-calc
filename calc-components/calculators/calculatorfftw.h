#ifndef CALCULATORFFTW_H
#define CALCULATORFFTW_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"
#include <complex>

template <class T>
class CalculatorFftw : public CalculatorBase<std::complex<T>>
{
public:
    CalculatorFftw(CALC_PTR(T) inReal,
                   BUFFER_PTR(std::complex<T>) outFft,
                   AbstractAccessStrategy::Ptr accessStrategy) :
        CalculatorBase<std::complex<T>>({inReal}, outFft, accessStrategy),
        m_inBuff(inReal->getOutputBuffer())
    {}
protected:
    BUFFER_PTR(T) m_inBuff;
};

#endif // CALCULATORFFTW_H
