#ifndef CALCINTERFACE_H
#define CALCINTERFACE_H

#include <memory>
#include <functional>

class CalcInterface
{
public:
    typedef std::shared_ptr<CalcInterface> Ptr;

    virtual void prepareNextCalc() = 0;
    virtual bool tryStartCalc(int sampleCount) = 0;
    virtual bool isDone() const = 0;
};

#endif // CALCINTERFACE_H
