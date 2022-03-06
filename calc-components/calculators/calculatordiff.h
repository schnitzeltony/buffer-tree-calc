#ifndef CALCULATORDIFF_H
#define CALCULATORDIFF_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

template <class T>
class CalculatorDiff : public CalculatorBase<T>
{
public:
    CalculatorDiff(CALC_PTR(T) minuent,
                   CALC_PTR(T) subtrahent,
                   BUFFER_PTR(T) output,
                   AbstractAccessStrategy::Ptr accessStrategy) :
        CalculatorBase<T>(std::vector<CalcInterface::Ptr> {minuent, subtrahent}, output, accessStrategy),
        m_minuentBuffer(minuent->getOutputBuffer()),
        m_subtrahentBuffer(subtrahent->getOutputBuffer())
    {}
    virtual void doCalc(int sampleCount) override
    {
        BUFFER_PTR(T) outBuff = CalculatorBase<T>::getOutputBuffer();
        for(int i=0, currSample = CalculatorBase<T>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff.at(currSample) = m_minuentBuffer.at(currSample) - m_subtrahentBuffer.at(currSample);
        }
    }
    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorDiff<T>> createWithOutBuffer(int bufferSize)
    {
        return std::make_shared<CalculatorDiff<T>>(std::make_shared<BufferTemplate<T>>(bufferSize),
                                                   createAccessStrategy<ACCESS_STRATEGY>());
    }
private:
    BUFFER_PTR(T) m_minuentBuffer;
    BUFFER_PTR(T) m_subtrahentBuffer;
};

#endif // CALCULATORDIFF_H
