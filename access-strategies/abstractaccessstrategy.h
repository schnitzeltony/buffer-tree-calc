#ifndef ABSTRACTACCESSSTRATEGY_H
#define ABSTRACTACCESSSTRATEGY_H

#include <memory>

class AbstractAccessStrategy
{
public:
    typedef std::shared_ptr<AbstractAccessStrategy> Ptr;
    virtual bool tryMakeBusy() = 0;
    virtual void setDone() = 0;
    virtual bool isDone() = 0;
    virtual void reset() = 0;
};

template <typename T>
std::shared_ptr<T> createAccessStrategy() { return std::make_shared<T>(); }

#endif // ABSTRACTACCESSSTRATEGY_H
