#ifndef BUFFERCALCBRAINSTORMING_H
#define BUFFERCALCBRAINSTORMING_H

#include "access-strategies/singlethreadedaccessstrategy.h"
#include "calc-composite/abstractcalculationcomponent.h"
#include "calc-strategies/abstractcalculationstrategy.h"
#include <memory>
#include <vector>



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





class FftStrategyFloat : AbstractCalculationStrategy
{
public:
    FftStrategyFloat(AbstractAccessStrategy::Ptr accessStrategy,
                     ConreteBufferFloatVectorPtr input,
                     ConreteBufferFloatVectorPtr output) :
        AbstractCalculationStrategy(accessStrategy, std::vector<AbstractCalculationComponent*>{input.get()}, output.get()),
        m_input(input),
        m_output(output)
    {
    }
    virtual void init() override;
    virtual void destroy() override;
    virtual bool doCalc(int subBufferNo) override;
private:
    ConreteBufferFloatVectorPtr m_input;
    ConreteBufferFloatVectorPtr m_output;
};




#endif // BUFFERCALCBRAINSTORMING_H
