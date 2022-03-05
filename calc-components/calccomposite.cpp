#include "calccomposite.h"

CalcComposite::CalcComposite(std::vector<Ptr> components) :
    m_components(components)
{
}

std::vector<CalcInterface::Ptr> CalcComposite::getComponents()
{
    return m_components;
}

bool CalcComposite::doCalc(int sampleCount)
{
    bool allDone = true;
    for(auto input : m_components) {
        if(!input->isDone()) {
            if(!input->tryStartCalc(sampleCount)) {
                allDone = false;
            }
        }
    }
    return allDone;
}

void CalcComposite::init()
{
    for(auto component : m_components) {
        component->init();
    }
}

void CalcComposite::destroy()
{
    for(auto component : m_components) {
        component->destroy();
    }
}

void CalcComposite::prepareCalc()
{
    for(auto component : m_components) {
        component->prepareCalc();
    }
}

bool CalcComposite::tryStartCalc(int sampleCount)
{
    return doCalc(sampleCount);
}

bool CalcComposite::isDone()
{
    bool done = true;
    for(auto component : m_components) {
        done &= component->isDone();
        if(!done) {
            break;
        }
    }
    return done;
}
