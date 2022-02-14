#ifndef BUFFERCALCBRAINSTORMING_H
#define BUFFERCALCBRAINSTORMING_H


#include <memory>
#include <vector>

class AbstractBuffer;
typedef std::shared_ptr<AbstractBuffer> AbstractBufferPtr;

class AbstractBufferCalcStrategy;
typedef std::shared_ptr<AbstractBufferCalcStrategy> AbstractBufferCalcStrategyPtr;



class AbstractBuffer
{
public:
    AbstractBuffer(int size);
    int getSize();
    void setInvalid();
    bool isAboutToBeValid();
    AbstractBufferCalcStrategyPtr getMyCalcStrategy();
    void setMyCalcStrategy(AbstractBufferCalcStrategyPtr calcStrategy);
private:
    int m_bufferSize;
    AbstractBufferCalcStrategyPtr m_myCalcStategy;
};

class ConcreteBufferFloat : public AbstractBuffer
{
public:
    ConcreteBufferFloat(int size);
    float *getBuffer();
private:
    float *m_buffer;
};


class AbstractBufferCalcStrategy
{
public:
    virtual void prepare() {}
    virtual void calculate() = 0;
    virtual void cleanup() {}
    virtual std::vector<AbstractBufferPtr> getInputBuffers() = 0;
    virtual AbstractBufferPtr getOutputBuffer();
};




class MagicBufferCalc
{
public:
    MagicBufferCalc(AbstractBufferCalcStrategyPtr strategy);
    void prepare();
    bool calculate();
    void cleanup();
private:
    AbstractBufferCalcStrategyPtr m_strategy;
};



#endif // BUFFERCALCBRAINSTORMING_H
