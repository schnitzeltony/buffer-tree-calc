#include "singlethreadedaccessstrategy.h"

bool SingleThreadedAccessStrategy::tryMakeBusy()
{
    if(m_busy) {
        return false;
    }
    m_busy = true;
    return true;
}

void SingleThreadedAccessStrategy::setDone(bool done)
{
    m_done = done;
}

bool SingleThreadedAccessStrategy::isDone()
{
    return m_done;
}

void SingleThreadedAccessStrategy::reset()
{
    m_busy = false;
    m_done = false;
}
