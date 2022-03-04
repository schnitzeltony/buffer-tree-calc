#ifndef CALCINTERFACE_H
#define CALCINTERFACE_H

#include <memory>

class CalcInteface
{
public:
    typedef std::shared_ptr<CalcInteface> Ptr;

    virtual void init() = 0;
    virtual void destroy() = 0;

    virtual void prepareCalc() = 0;
    virtual bool tryStartCalc(int sampleCount) = 0;
    virtual bool isDone() = 0;
    virtual void setDone() = 0;
protected:
    virtual bool doCalc(int sampleCount) = 0;
};

#endif // CALCINTERFACE_H
