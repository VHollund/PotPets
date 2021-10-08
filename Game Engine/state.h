#ifndef KJELEDYR_STATE_H
#define KJELEDYR_STATE_H

#include <memory>
#include <SFML/Graphics.hpp>

// An abstract base class for every state.

class StateMachine;

namespace Kjeledyr {

    class State {
    public:
        virtual void Init() = 0;
        virtual void HandleInput() = 0;
        virtual void Update(float delta) = 0;
        virtual void Draw(float delta) = 0;
        virtual void Pause() {}
        virtual void Resume() {}
    protected:
    };

}

#endif