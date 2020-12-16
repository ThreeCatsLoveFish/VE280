/**
 * @file call.cpp
 * @author Zhimin Sun
 * @brief Call Center Simulation
 * @date 2020-11-26
 * @course 2020FA VE280
 */
#include "dlist.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/* Const parameters for VIP information. */
static const char *VIP[] = {
    "platinum",
    "gold",
    "silver",
    "regular",
};
static const size_t VIPNUM = sizeof(VIP) / sizeof(char *);

class Call
{
private:
    struct Member
    {
        size_t timestamp;
        string name;
        size_t status;
        size_t duration;

        Member()
        {
            string vipLevel;

            cin >> timestamp >> name >> vipLevel >> duration;
            cin.get();
            for (size_t i = 0; i < VIPNUM; i++) {
                if (vipLevel == VIP[i]) {
                    status = i;
                    break;
                }
            }
        }
    };
    size_t        nowTime;
    Member *      serving;
    Dlist<Member> memberQueue;
    size_t        memberNum;

    void getVip(const size_t &level = 0)
    // EFFECTS: Find the available vip of this level
    //          Throw 0 if no member is found
    // REQUIRES: serving is not `nullptr`
    {
        assert(!serving);
        if (level == VIPNUM) {
            throw 0;
        }

        bool change = false;

        for (size_t i = 0; i < memberNum; i++) {
            Member *now;

            now = memberQueue.removeFront();
            memberQueue.insertBack(now);
            if (now->status == level && now->timestamp <= nowTime && !change) {
                change  = true;
                serving = now;
                continue;
            }
        }
        if (!change) {
            getVip(level + 1);
        }
    }

    void delCall()
    // EFFECTS: Delete the completed call
    // REQUIRES: serving is not `nullptr`
    // MODIFIES: memberNum, memberQueue
    {
        assert(serving);
        for (size_t i = 0; i < memberNum; i++) {
            Member *now;

            now = memberQueue.removeFront();
            if (now == serving) {
                delete now;
                serving = nullptr;
                continue;
            }
            memberQueue.insertBack(now);
        }
        memberNum--;
    }

    bool setCall()
    // EFFECTS: Update next serving member. If update return true, else false
    // MODIFIES: nowTime, serving
    {
        if (serving == nullptr) {
            try {
                getVip();
            } catch (...) {
                return false;
            }
            serving->timestamp = nowTime;
            return true;
        }
        if (serving->timestamp + serving->duration == nowTime) {
            try {
                delCall();
                getVip();
            } catch (...) {
                return false;
            }
            serving->timestamp = nowTime;
            return true;
        }
        return false;
    }

    void getCall()
    // EFFECTS: Get the calls at this time by traversing the queue.
    {
        for (size_t i = 0; i < memberNum; i++) {
            Member *now;

            now = memberQueue.removeFront();
            memberQueue.insertBack(now);
            if (now->timestamp == nowTime) {
                cout << "Call from " << now->name << " a " << VIP[now->status]
                     << " member" << endl;
            }
        }
    }

public:
    Call() : nowTime(0), serving(nullptr)
    {
        cin >> memberNum;
        for (size_t i = 0; i < memberNum; i++) {
            memberQueue.insertBack(new Member());
        }
        /* Boundary case! */
        if (memberNum == 0) {
            cout << "Starting tick #0" << endl;
        }
    }

    void start()
    // EFFECTS: Start the call center!
    {
        while (!memberQueue.isEmpty() && memberNum != 0) {
            cout << "Starting tick #" << nowTime << endl;
            getCall();
            if (setCall()) {
                cout << "Answering call from " << serving->name << endl;
            }
            nowTime++;
        }
    }
};

int
main(void)
{
    Call().start();
    return 0;
}
