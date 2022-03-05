#ifndef CALCNODE_H
#define CALCNODE_H

#include "calcinterface.h"
#include "access-strategies/abstractaccessstrategy.h"
#include <functional>

class CalcComponent : public CalcInterface
{
public:
    CalcComponent(std::function<bool(int)> doCalcHandler, AbstractAccessStrategy::Ptr accessStrategy);
    virtual void init() override { }
    virtual void destroy() override { }

    virtual void prepareCalc() override final;
    virtual bool tryStartCalc(int sampleCount) override final;
    virtual bool isDone() override final;
protected:
    virtual bool doCalc(int sampleCount) override final;
private:
    AbstractAccessStrategy::Ptr m_accessStrategy;
    std::function<bool(int)> m_doCalcHandler = nullptr;
};

#endif // CALCNODE_H
