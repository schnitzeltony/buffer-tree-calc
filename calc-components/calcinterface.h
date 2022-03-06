#ifndef CALCINTERFACE_H
#define CALCINTERFACE_H

#include <memory>

class CalcInterface
{
public:
    typedef std::shared_ptr<CalcInterface> Ptr;
    virtual void init() = 0;
    virtual void destroy() = 0;

    virtual void prepareCalc() = 0;
    virtual bool tryStartCalc(int sampleCount) = 0;
    virtual bool isDone() const = 0;
protected:
    virtual void doCalc(int sampleCount) = 0;
};

#endif // CALCINTERFACE_H
