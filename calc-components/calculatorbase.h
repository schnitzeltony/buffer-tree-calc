#ifndef CALCULATORBASE_H
#define CALCULATORBASE_H

#include "calccomponent.h"
#include "calccomposite.h"
#include "buffers/buffertemplate.h"
#include <vector>
#include <functional>

#define CALC_PTR(T) std::shared_ptr<CalculatorBase<T>>

// consider CalculatorBase as another composite
template <class T>
class CalculatorBase : public CalcInterface
{
public:
    CalculatorBase(std::vector<CalcInterface::Ptr> inputCalculators,
                   BUFFER_PTR(T) outputBuffer,
                   std::function<void(int)> doCalcHandler,
                   AbstractAccessStrategy::Ptr accessStrategy);
    virtual void prepareNextCalc() override final;
    virtual bool tryStartCalc(int sampleCount) override final;
    virtual bool isDone() const override final;

    BUFFER_PTR(T) getOutputBuffer() { return m_outputBuffer; }
    int getSampleOffset() const { return m_sampleOffset; }
    void keepSampleOffsetOnNextTryStart(bool keep) { m_keepSampleOffsetOnNextTryStart = keep; }
    // ideas for dynamic sequencing: synced to next doCalc
    // * change inputs??
    // * inject doCalc handler (e.g bypass / mute)
    // * two toggling outputs
protected:
    BUFFER_PTR(T) m_outputBuffer;
private:
    void doCalcCallback(int sampleCount);
    CalcComponent m_AccessComponent;
    CalcComposite m_inputsComposite;
    std::function<void(int)> m_doCalcHandler = nullptr;
    int m_sampleOffset = 0;
    bool m_keepSampleOffsetOnNextTryStart = false;
};

#include "calculatorbase_impl.h"

#endif // CALCULATORBASE_H
