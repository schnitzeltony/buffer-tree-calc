#ifndef CALCULATORFFTW_H
#define CALCULATORFFTW_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

#define CALC_PTR_FFTW(T) std::shared_ptr<CalculatorFftw<T>>

template <class T>
class CalculatorFftw : public CalculatorBase<T>
{
public:
    CalculatorFftw(CALC_PTR(T) in,
                        BUFFER_PTR(T) out,
                        AbstractAccessStrategy::Ptr accessStrategy,
                        bool inverseFft) :
        CalculatorBase<T>({in}, out, accessStrategy),
        m_inBuffer(in->getOutputBuffer()),
        m_inverseFft(inverseFft)
    {}
    T getFftRe(int order) { return getFftVal(order*2); }
    T getFftIm(int order) { return getFftVal(order*2+1); }
protected:
    BUFFER_PTR(T) m_inBuffer;
    bool m_inverseFft;
private:
    T getFftVal(int idx) { return !m_inverseFft ? CalculatorBase<T>::m_outputBuffer->at(idx) : m_inBuffer->at(idx); }
};

#endif // CALCULATORFFTW_H
