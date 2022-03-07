#ifndef CALCCOMPOSITE_H
#define CALCCOMPOSITE_H

#include "calcinterface.h"
#include <vector>

class CalcComposite : public CalcInterface
{
public:
    CalcComposite(std::vector<Ptr> components);

    virtual void prepareNextCalc() override final;
    virtual bool tryStartCalc(int sampleCount) override final;
    virtual bool isDone() const override final;
protected:
    virtual void doCalc(int sampleCount) override final;
private:
    std::vector<Ptr> m_components;
};

#endif // CALCCOMPOSITE_H
