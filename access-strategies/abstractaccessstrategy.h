#ifndef ABSTRACTACCESSSTRATEGY_H
#define ABSTRACTACCESSSTRATEGY_H

#include <memory>
#include <exception>

class double_done_exception : public std::exception
{
    virtual const char* what() const throw() override
    {
        return "setDone called twice without reset";
    }
};


class AbstractAccessStrategy
{
public:
    typedef std::shared_ptr<AbstractAccessStrategy> Ptr;
    virtual bool tryMakeBusy() = 0;
    virtual void setDone() = 0;
    virtual bool isDone() const = 0;
    virtual void reset() = 0;
};

template <typename T>
std::shared_ptr<T> createAccessStrategy() { return std::make_shared<T>(); }

#endif // ABSTRACTACCESSSTRATEGY_H
