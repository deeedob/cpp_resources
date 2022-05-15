#include <map>
#include <iostream>
#include <vector>

using namespace std;    // for simpler reading ...

enum class State {
    FirstState,
    SecondState,
    ThirdState
};

enum class Trigger {
    TriggerFirst,
    TriggerSecond,
    TriggerThird
};

/* some pretty printing */
inline ostream& operator<<( ostream& os, State& s) {
    switch (s) {
        case State::FirstState : os << "FirstState"; break;
        case State::SecondState : os << "SecondState"; break;
        case State::ThirdState : os << "ThirdState"; break;
    }
    return os;
}
inline ostream& operator<<(ostream& os, Trigger& t) {
    switch (t) {
        case Trigger::TriggerFirst: os << "TriggerFirst"; break;
        case Trigger::TriggerSecond: os << "TriggerSecond"; break;
        case Trigger::TriggerThird: os << "TriggerThird"; break;
    }
    return os;
}

class StateMachine {
public:
    StateMachine() {
        currentState = State::FirstState;
        /* go through the states : First <-> Second <-> Third */
        transitionTable[State::FirstState] = {
                {Trigger::TriggerSecond, State::SecondState },
        };
        transitionTable[State::SecondState] = {
                { Trigger::TriggerFirst, State::FirstState },
                { Trigger::TriggerThird, State::ThirdState }
        };
        transitionTable[State::ThirdState] = {
                {Trigger::TriggerSecond, State::SecondState }
        };
    }
    void listOptions() {
        u_int8_t cnt = 0;

        cout << currentState << " : " << endl;
        for( auto i : transitionTable[currentState]) {
            cout << toascii(cnt) << " :  " << i.first;
            cout << " ---> " << i.second << endl;
            cnt++;
        }
    }
    void setState(u_int8_t pos) {
        if ( pos > transitionTable[currentState].size()) {
            cout << "position is not correct ...\n" << endl;
            return;
        }
        currentState = transitionTable[currentState][pos].second;
    }

private:
    /* we essentially want a State corresponding to a linked
     * list of next States activated by a trigger
     */
    map<State, vector<pair<Trigger,State>>> transitionTable;
    State currentState;
};

int main() {
    StateMachine state;

    u_int32_t input;
    while(true) {
        state.listOptions();
        cout << "Choose : ";
        cin >> input;
        state.setState(input);
    }

    return 0;
}
