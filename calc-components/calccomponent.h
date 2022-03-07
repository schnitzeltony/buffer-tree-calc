#ifndef CALCNODE_H
#define CALCNODE_H

#include "calcinterface.h"
#include "access-strategies/abstractaccessstrategy.h"
#include <functional>

class CalcComponent : public CalcInterface
{
public:
    CalcComponent(std::function<void(int)> doCalcHandler, AbstractAccessStrategy::Ptr accessStrategy);
    virtual void prepareNextCalc() override final;
    virtual bool tryStartCalc(int sampleCount) override final;
    virtual bool isDone() const override final;
protected:
    virtual void doCalc(int sampleCount) override final;
private:
    AbstractAccessStrategy::Ptr m_accessStrategy;
    std::function<void(int)> m_doCalcHandler = nullptr;
};

#endif // CALCNODE_H
