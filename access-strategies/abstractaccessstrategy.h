#ifndef ABSTRACTACCESSSTRATEGY_H
#define ABSTRACTACCESSSTRATEGY_H

#include <memory>

class AbstractAccessStrategy
{
public:
    typedef std::shared_ptr<AbstractAccessStrategy> Ptr;
    virtual bool tryMakeBusy() = 0;
    virtual void setDone(bool done) = 0;
    virtual bool isDone() = 0;
    virtual void reset() = 0;
};

#endif // ABSTRACTACCESSSTRATEGY_H
