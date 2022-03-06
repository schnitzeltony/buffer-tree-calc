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
                   AbstractAccessStrategy::Ptr accessStrategy);
    virtual void init() override {}
    virtual void destroy() override {}

    virtual void prepareCalc() override final;
    virtual bool tryStartCalc(int sampleCount) override final;
    virtual bool isDone() const override final;

    BUFFER_PTR(T) getOutputBuffer() { return m_outputBuffer; }
    int getSampleOffset() const { return m_sampleOffset; }

protected:
    BUFFER_PTR(T) m_outputBuffer;
private:
    void doCalcCallback(int sampleCount);
    CalcComponent m_AccessComponent;
    CalcComposite m_inputsComposite;
    int m_sampleOffset = 0;
};

#include "calculatorbase_impl.h"

#endif // CALCULATORBASE_H
