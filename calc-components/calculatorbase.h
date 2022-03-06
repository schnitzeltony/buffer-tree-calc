#ifndef CALCULATORBASE_H
#define CALCULATORBASE_H

#include "calccomponent.h"
#include "calccomposite.h"
#include "buffers/buffertemplate.h"
#include <vector>

#define CALC_PTR(T) std::shared_ptr<CalculatorBase<T>>

template <class T>
class CalculatorBase : public CalcInterface
{
public:
    CalculatorBase(std::vector<CalcInterface::Ptr> inputCalculators,
                   BUFFER_PTR(T) outputBuffer,
                   AbstractAccessStrategy::Ptr accessStrategy) :
        m_AccessComponent([&](int sampleCount){doCalcCallback(sampleCount);}, accessStrategy),
        m_inputsComposite(inputCalculators),
        m_outputBuffer(outputBuffer)
    {
    }
    virtual void init() override {}
    virtual void destroy() override {}
    virtual void prepareCalc() override final
    {
        m_sampleOffset = 0;
        m_inputsComposite.prepareCalc();
        m_AccessComponent.prepareCalc();
    }
    virtual bool tryStartCalc(int sampleCount) override final
    {
        bool allDone = true;
        if(!m_inputsComposite.isDone()) {
            allDone = m_inputsComposite.tryStartCalc(sampleCount);
        }
        if(allDone && !m_AccessComponent.isDone()) {
            allDone = m_AccessComponent.tryStartCalc(sampleCount);
        }
        return allDone;
    }
    virtual bool isDone() const override final { return m_inputsComposite.isDone() && m_AccessComponent.isDone();}

    BUFFER_PTR(T) getOutputBuffer() { return m_outputBuffer; }
    int getSampleOffset() const {return m_sampleOffset; }

protected:
    BUFFER_PTR(T) m_outputBuffer;
private:
    void doCalcCallback(int sampleCount)
    {
        doCalc(sampleCount);
        m_sampleOffset += sampleCount;
    }
    CalcComponent m_AccessComponent;
    CalcComposite m_inputsComposite;
    int m_sampleOffset = 0;
};


#endif // CALCULATORBASE_H
