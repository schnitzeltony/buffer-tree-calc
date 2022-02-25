#ifndef BUFFERCALCBRAINSTORMING_H
#define BUFFERCALCBRAINSTORMING_H

#include <memory>
#include <vector>

class AbstractAccessStrategy
{
public:
    typedef std::shared_ptr<AbstractAccessStrategy> Ptr;
    virtual bool tryMakeBusy() = 0;
    virtual void setDone(bool done) = 0;
    virtual bool isDone() = 0;
    virtual void reset() = 0;
};

class SingleThreadedBusyController : public AbstractAccessStrategy
{
public:
    virtual bool tryMakeBusy() override
    {
        if(m_busy) {
            return false;
        }
        m_busy = true;
        return true;
    }
    virtual void setDone(bool done) override
    {
        m_done = done;
    }
    virtual bool isDone() override
    {
        return m_done;
    }
    virtual void reset() override
    {
        m_busy = false;
        m_done = false;
    }

protected:
    bool m_busy = false;
    bool m_done = false;
};


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


class AbstractCalculationStrategy : public AbstractCalculationComponent
{
public:
    AbstractCalculationStrategy(std::vector<AbstractCalculationComponentPtr> inputComponents,
                                AbstractCalculationComponentPtr outComponent);

    virtual std::vector<AbstractCalculationComponentPtr> getInputComponents();
    virtual AbstractCalculationComponentPtr getOutputBuffer();

private:
    std::vector<AbstractCalculationComponentPtr> m_inputComponents;
    AbstractCalculationComponentPtr m_outComponent;
};

typedef std::shared_ptr<AbstractCalculationStrategy> AbstractCalculationStrategyPtr;


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
