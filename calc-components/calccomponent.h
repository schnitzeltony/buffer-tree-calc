#ifndef CALCNODE_H
#define CALCNODE_H

#include "calcinterface.h"
#include "access-strategies/abstractaccessstrategy.h"

class CalcComponent : public CalcInterface
{
public:
    CalcComponent(AbstractAccessStrategy::Ptr accessStrategy);
    virtual void init() override { }
    virtual void destroy() override { }

    virtual void prepareCalc() override final;
    virtual bool tryStartCalc(int sampleCount) override final;
    virtual bool isDone() override final;
private:
    AbstractAccessStrategy::Ptr m_accessStrategy;
};

#endif // CALCNODE_H
