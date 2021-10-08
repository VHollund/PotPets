#ifndef KJELEDYR_STATEMACHINE_H
#define KJELEDYR_STATEMACHINE_H

#include <stack>
#include <map>

#include "state.h"

namespace Kjeledyr {

    typedef std::unique_ptr<State> StateRef;

    class StateMachine {
    public:
        StateMachine() {}
        ~StateMachine() {}

        void AddState(StateRef newState, bool isReplacing = true);
        void RemoveState();
        void ProcessStateChanges();
        StateRef &GetActiveState();

    protected:
        std::stack<StateRef> states;
        StateRef newState;

        // Our state handling variables
        bool isAdding;
        bool isRemoving;
        bool isReplacing;

    };

}

#endif