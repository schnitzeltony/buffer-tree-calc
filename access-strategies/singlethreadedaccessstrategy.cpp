#include "singlethreadedaccessstrategy.h"

bool SingleThreadedAccessStrategy::tryMakeBusy()
{
    if(m_busy) {
        return false;
    }
    m_busy = true;
    return true;
}

void SingleThreadedAccessStrategy::setDone()
{
    m_done = true;
}

bool SingleThreadedAccessStrategy::isDone() const
{
    return m_done;
}

void SingleThreadedAccessStrategy::reset()
{
    m_busy = false;
    m_done = false;
}
