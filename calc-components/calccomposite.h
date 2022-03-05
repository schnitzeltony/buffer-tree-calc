#ifndef CALCCOMPOSITE_H
#define CALCCOMPOSITE_H

#include "calcinterface.h"
#include <vector>

class CalcComposite : public CalcInterface
{
public:
    CalcComposite(std::vector<Ptr> components);
    virtual void init() override final;
    virtual void destroy() override final;

    virtual void prepareCalc() override final;
    virtual bool tryStartCalc(int sampleCount) override final;
    virtual bool isDone() override final;
    virtual void setDone() override final;
protected:
    virtual bool doCalc(int sampleCount) override final;

private:
    std::vector<Ptr> m_components;
};

#endif // CALCCOMPOSITE_H
