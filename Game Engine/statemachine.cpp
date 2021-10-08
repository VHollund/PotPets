#include <plog/Log.h>
#include "statemachine.h"

namespace Kjeledyr {

    /**
     * Preps the state handling variables to push a state to the stack
     * next time ProcessStateChanges() runs.
     *
     * @param newState The state to be pushed
     * @param isReplacing A bool that is always true
     * @see ProcessStateChanges()
     */
    void StateMachine::AddState(StateRef newState, bool isReplacing) {
        LOGI << "Adding state";
        this->isAdding = true;
        LOGE_IF(!isAdding) << "Failed to set isAdding to true!";
        this->isReplacing = isReplacing;
        this->newState = std::move(newState);
    }

    /**
     * Preps the state handling variables to pop a state from the stack
     * next time ProcessStateChanges() runs.
     *
     * @see ProcessStateChanges()
     */
    void StateMachine::RemoveState() {
        LOGI << "Removing state";
        this->isRemoving = true;
        LOGE_IF(!isRemoving) << "Failed to set isRemoving to true!";
    }

    /**
     * Checks for every game loop if the state handling variables has been updated.
     * If the stack isn't empty, it:
     * adds a state if _isAdding = true,
     * removes a state if _isRemoving = true,
     * returns if they are both false.
     */
    void StateMachine::ProcessStateChanges() {
        if (this->isRemoving && !this->states.empty()) {
            this->states.pop();

            if (!this->states.empty()) {
                this->states.top()->Resume();
            }

            this->isRemoving = false;
        }

        if (this->isAdding) {
            if(!this->states.empty()) {
                if (this->isReplacing) {
                    this->states.pop();
                } else {
                    this->states.top()->Pause();
                }
            }

            this->states.push(std::move(this->newState));
            this->GetActiveState()->Init();
            this->isAdding = false;
        }
    }

    /**
     * Gets a reference to the active state.
     * Because stack is a LIFO-container, the active state is the topmost layer,
     * in other words the last state we added to the stack.
     *
     * @return The topmost state from the stack.
     */
    StateRef &StateMachine::GetActiveState() {
        return this->states.top();
    }
}