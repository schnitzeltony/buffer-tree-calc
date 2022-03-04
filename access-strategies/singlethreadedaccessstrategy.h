#ifndef SINGLETHREADEDACCESSSTRATEGY_H
#define SINGLETHREADEDACCESSSTRATEGY_H

#include "abstractaccessstrategy.h"

class SingleThreadedAccessStrategy : public AbstractAccessStrategy
{
public:
    virtual bool tryMakeBusy() override;
    virtual void setDone() override;
    virtual bool isDone() override;
    virtual void reset() override;
protected:
    bool m_busy = false;
    bool m_done = false;
};

#endif // SINGLETHREADEDACCESSSTRATEGY_H
