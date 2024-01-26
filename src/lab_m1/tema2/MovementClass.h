#include <iostream>
#include <cstdlib>
#include <ctime>

enum class State {
    IDLE,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class MoveObject {

    public:
    
    MoveObject() : currentState(State::IDLE){}

    void Update() {
        switch (currentState) {
        case State::IDLE:
            // std::cout << "Object is idle.\n";
            currentState = GetRandomState();
            break;

        case State::FORWARD:
            // std::cout << "Object is moving forward.\n";
            currentState = GetRandomState();
            break;

        case State::BACKWARD:
            // std::cout << "Object is moving backward.\n";
            currentState = GetRandomState();
            break;

        case State::LEFT:
            // std::cout << "Object is moving left.\n";
            currentState = GetRandomState();
            break;

        case State::RIGHT:
            // std::cout << "Object is moving right.\n";
            currentState = GetRandomState();
            break;    
        }
    }

    State GetState() {
        return currentState;
    }

private:
    
    State currentState;
    
    State GetRandomState() {
        int random = rand() % 5;

        switch (random) {
        case 0:
            return State::IDLE;

        case 1:
            return State::FORWARD;

        case 2:
            return State::BACKWARD;

        case 3:
            return State::LEFT;

        case 4:
            return State::RIGHT;
        }
    }
};