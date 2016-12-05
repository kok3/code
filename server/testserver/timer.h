#ifndef __TIMER_HEAD__
#define __TIMER_HEAD__

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "type_mogo.h"
#include "lua.hpp"

namespace mogo
{

enum{
	TIMER_TICK_COUNT_PER_SECOND = 2,     //1秒=n tick
	TIMER_INTERVAL_USEC = 1000000 / TIMER_TICK_COUNT_PER_SECOND,   //定时器间隔*微秒 = (1秒/每秒的tick数)
	TIME_SAVE_TICKS = 5 * TIMER_TICK_COUNT_PER_SECOND,             //每5秒触发一次定时存盘
	TIME_ENTITY_MOVE = 1,      //移动间隔
};

using namespace std;


struct TimerData
{
    TimerData(unsigned int nStart, int nInterval, unsigned int nTimerId, 
        TENTITYID nId, int nUserData)
        : m_unNextTick(nStart), m_nInterval(nInterval), m_nTimerId(nTimerId), 
        m_nEntityId(nId), m_nUserData(nUserData)
    {
    }

    unsigned int m_nTimerId;
    int m_nInterval;
    unsigned long m_unNextTick;
    TENTITYID m_nEntityId;
    int m_nUserData;
};

class world;

class CTimerHeap
{
public:
    CTimerHeap();
    ~CTimerHeap();

public:
    int AddTimer(unsigned int nStart, int nInterval, TENTITYID nId, int nUserData);
   // void OnTick(lua_State* L, world& the_world, uint32_t unTick);
    //void onTick(uint32_t unTick);
/*
private:
    bool OnEntityTick(lua_State* L, world& the_world, TimerData* p);
*/
private:
    struct TimerDataOp
    {
        bool operator()(TimerData* p1, TimerData* p2)
        {
            return p1->m_unNextTick > p2->m_unNextTick;
        }
    };

private:
    uint32_t m_nNextTimerId;
    uint32_t m_unTick;
    priority_queue<TimerData*, vector<TimerData*>, TimerDataOp> m_queue;

};


}


#endif

