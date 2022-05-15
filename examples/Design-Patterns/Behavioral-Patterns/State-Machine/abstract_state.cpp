#pragma once
#include <iostream>
using namespace std;

class StateMachine; // resolve dependency

/* interface for implementing new States */
class AbstractState {
public:
    virtual void enter( StateMachine* state ) = 0;
    virtual void action( StateMachine* state ) = 0;
    virtual void exit( StateMachine* state ) = 0;
    virtual ~AbstractState() {}
};

class StateMachine {
public:
    explicit StateMachine(AbstractState* state) {
        currentState = state;
        currentState->enter(this);
    };
    inline AbstractState* getCurrentState() const { return currentState; }
    /* when changing states call these functions in the given order */
    void setState(AbstractState& newState) {
        currentState->exit(this);
        currentState = &newState;
        currentState->enter(this);
    }
    void action() {
        currentState->action(this);
    }
private:
    AbstractState* currentState;
};
/* implementation of a new State.
 * Quick and Easy Singleton. For production delete the constructors
 */
class StateOne : AbstractState {
public:
    static AbstractState& getInstance() {
        static StateOne singleton;
        return singleton;
    }

    void action( StateMachine *state ) override {
        cout << "StateOne : action" << endl;
    }
private:
    void enter( StateMachine *state ) override {
        cout << "StateOne : enter" << endl;
    }

    void exit( StateMachine *state ) override {
        cout << "StateOne : exit\n" << endl;
    }
};

class StateTwo : AbstractState {
public:
    static AbstractState& getInstance() {
        static StateTwo singleton;
        return singleton;
    }

    void action( StateMachine *state ) override {
        cout << "StateTwo : action" << endl;
    }
private:
    void enter( StateMachine *state ) override {
        cout << "StateTwo : enter" << endl;
    }

    void exit( StateMachine *state ) override {
        cout << "StateTwo : exit\n" << endl;
    }
};

int main() {
    StateMachine state(&StateOne::getInstance());
    state.action();

    state.setState(StateTwo::getInstance());
    state.action();
    state.action();

    state.setState(StateOne::getInstance());

    return 0;
}