#ifndef BUFFERCALCBRAINSTORMING_H
#define BUFFERCALCBRAINSTORMING_H

#include <memory>
#include <vector>

class AbstractCalculationComponent
{
public:
    typedef std::shared_ptr<AbstractCalculationComponent> Ptr;
    virtual void prepareCalc() {}
    virtual void startCalc(int subBufferNo) = 0;
    virtual bool calcDone() = 0;
};


class AbstractCalculationBuffer: public AbstractCalculationComponent
{
public:
    AbstractCalculationBuffer(int size);
    int getSize();
    virtual void prepareCalc() override  { m_calcDone = false; }
    virtual void startCalc(int subBufferNo = 0) override { (void)subBufferNo; m_calcDone = true; }
    virtual bool calcDone() override { return m_calcDone; }
private:
    bool m_calcDone = false;
};

class ConreteBufferFloatBare: public AbstractCalculationBuffer
{
public:
    float *getBuffer();
};

class ConreteBufferFloatVector: public AbstractCalculationBuffer
{
public:
    std::vector<float> getBuffer();
};


class AbstractCalculationStrategy
{
public:
    typedef std::shared_ptr<AbstractCalculationStrategy> Ptr;
    virtual void doCalc() = 0;
};

class CalculationNode: public AbstractCalculationComponent
{
public:
    virtual std::vector<AbstractCalculationComponent::Ptr> getInputComponents() = 0;
    virtual AbstractCalculationComponent::Ptr getOutputBuffer();
    virtual void startCalc(int subBufferNo) override
    {
        for(auto input : getInputComponents()) {
            if(!input->calcDone()) {
                input->startCalc(subBufferNo);
            }
        }
    }
    virtual bool calcDone() override
    {
        return getOutputBuffer()->calcDone();
    }
private:
    AbstractCalculationStrategy::Ptr m_outCalcStrategy;
};


#endif // BUFFERCALCBRAINSTORMING_H
