#ifndef BUFFERCALCBRAINSTORMING_H
#define BUFFERCALCBRAINSTORMING_H

#include "access-strategies/singlethreadedaccessstrategy.h"

#include <memory>
#include <vector>





class AbstractCalculationComponent
{
public:
    AbstractCalculationComponent(AbstractAccessStrategy::Ptr busyState);

    virtual void init() {}
    virtual void prepareCalc() {}
    bool startCalc(int subBufferNo)
    {
        bool calcDoneByMe = m_busyState->tryMakeBusy();
        if(calcDoneByMe) {
            doCalc(subBufferNo);
            m_busyState->setDone(true);
        }
        return calcDoneByMe;
    }
    bool calcDone()
    {
        return m_busyState->isDone();
    }
    void setDone(bool done) {
        m_busyState->setDone(done);
    }
    virtual void destroy() {}
protected:
    virtual bool doCalc(int subBufferNo) = 0;

    AbstractAccessStrategy::Ptr m_busyState;
};

typedef std::shared_ptr<AbstractCalculationComponent> AbstractCalculationComponentPtr;



class AbstractCalculationBuffer: public AbstractCalculationComponent
{
public:
    AbstractCalculationBuffer(AbstractAccessStrategy::Ptr busyStrategy,int size);
    int getSize();
private:
};

class ConreteBufferFloatBareSingle: public AbstractCalculationBuffer
{
public:
    float *getBuffer();
};

class ConreteBufferFloatVector: public AbstractCalculationBuffer
{
public:
    std::vector<float> &getBuffer();
};
typedef std::shared_ptr<ConreteBufferFloatVector> ConreteBufferFloatVectorPtr;



class AbstractCalculationStrategy : public AbstractCalculationComponent
{
public:
    AbstractCalculationStrategy(std::vector<AbstractCalculationComponent*> inputComponents,
                                AbstractCalculationComponent* outComponent);

    virtual std::vector<AbstractCalculationComponent*> getInputComponents();
    virtual AbstractCalculationComponent* getOutputBuffer();

private:
    std::vector<AbstractCalculationComponent*> m_inputComponents;
    AbstractCalculationComponent *m_outComponent;
};

typedef std::shared_ptr<AbstractCalculationStrategy> AbstractCalculationStrategyPtr;


class FftStrategyFloat : AbstractCalculationStrategy
{
public:
    FftStrategyFloat(ConreteBufferFloatVectorPtr input, ConreteBufferFloatVectorPtr output) :
        AbstractCalculationStrategy(std::vector<AbstractCalculationComponent*> {input.get()}, output.get()),
        m_input(input),
        m_output(output)
    {
    }
private:
    ConreteBufferFloatVectorPtr m_input;
    ConreteBufferFloatVectorPtr m_output;
};


class CalculationNode: public AbstractCalculationComponent
{
public:
    virtual bool doCalc(int subBufferNo) override
    {
        bool allWorkDone = true;
        for(auto input : m_outCalcStrategy->getInputComponents()) {
            if(!input->calcDone()) {
                bool started = input->startCalc(subBufferNo);
                if(!started) {
                    allWorkDone = false;
                }
            }
        }
        if(allWorkDone && !m_outCalcStrategy->calcDone()) {
            bool started = m_outCalcStrategy->startCalc(subBufferNo);
            if(!started) {
                allWorkDone = false;
            }
        }
        if(allWorkDone) {
            m_outCalcStrategy->setDone(true);
        }
        return allWorkDone;
    }
    virtual void init() override
    {
        for(auto input : m_outCalcStrategy->getInputComponents()) {
            input->init();
        }
        m_outCalcStrategy->getOutputBuffer()->init();
    }
    virtual void destroy() override
    {

    }

private:
    AbstractCalculationStrategyPtr m_outCalcStrategy;
};


#endif // BUFFERCALCBRAINSTORMING_H
