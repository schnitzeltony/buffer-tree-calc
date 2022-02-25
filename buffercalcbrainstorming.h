#ifndef BUFFERCALCBRAINSTORMING_H
#define BUFFERCALCBRAINSTORMING_H

#include "access-strategies/singlethreadedaccessstrategy.h"
#include "calc-composite/calculationnode.h"
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









#endif // BUFFERCALCBRAINSTORMING_H
