#ifndef CALCFORTEST_H
#define CALCFORTEST_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbase.h"

template <class T>
class CalcForTest : public CalculatorBase<T>
{
public:
    CalcForTest(CALC_PTR(T) in,
                BUFFER_PTR(T) out,
                AbstractAccessStrategy::Ptr accessStrategy) :
        CalculatorBase<T>(
            std::vector<CalcInterface::Ptr> {in},
            out,
            [&](int sampleCount){doCalc(sampleCount);},
            accessStrategy),
        m_inBuffer(in->getOutputBuffer())
    {}
    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalcForTest<T>> createWithOutBuffer(CALC_PTR(T) in, int bufferSize)
    {
        return std::make_shared<CalcForTest<T>>(in,
                                                std::make_shared<BufferTemplate<T>>(bufferSize),
                                                createAccessStrategy<ACCESS_STRATEGY>());
    }
private:
    void doCalc(int sampleCount)
    {
        BUFFER_PTR(T) outBuff = CalculatorBase<T>::getOutputBuffer();
        for(int i=0, currSample = CalculatorBase<T>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff->at(currSample) = m_inBuffer->at(currSample);
        }
    };
    BUFFER_PTR(T) m_inBuffer;
};


#endif // CALCFORTEST_H
