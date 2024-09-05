#include <iostream>

using namespace std;

// States of the washing machine
enum class WashingMachineState {
    Idle,
    Filling,
    Washing,
    Draining,
    Spinning,
    Finished
};

// Class of the Washing Machine
class WashingMachine {
private:
    WashingMachineState currentState;

public:
    WashingMachine() : currentState(WashingMachineState::Idle) {}

    // Function of the transition 
    void transition(WashingMachineState nextState) {
        cout << "Transitioning from ";

        switch (currentState) {
            case WashingMachineState::Idle: cout << "Idle"; break;
            case WashingMachineState::Filling: cout << "Filling"; break;
            case WashingMachineState::Washing: cout << "Washing"; break;
            case WashingMachineState::Draining: cout << "Draining"; break;
            case WashingMachineState::Spinning: cout << "Spinning"; break;
            case WashingMachineState::Finished: cout << "Finished"; break;
        }

        cout << " to ";

        switch (nextState) {
            case WashingMachineState::Idle: cout << "Idle"; break;
            case WashingMachineState::Filling: cout << "Filling"; break;
            case WashingMachineState::Washing: cout << "Washing"; break;
            case WashingMachineState::Draining: cout << "Draining"; break;
            case WashingMachineState::Spinning: cout << "Spinning"; break;
            case WashingMachineState::Finished: cout << "Finished"; break;
        }

        cout << endl;

        currentState = nextState;
    }

    // start filling water
    void startFilling() {
        cout << "Starting to fill water." << endl;
        transition(WashingMachineState::Filling);
    }

    // start washing
    void startWashing() {
        cout << "Starting washing." << endl;
        transition(WashingMachineState::Washing);
    }

    // start draining water
    void startDraining() {
        cout << "Starting to drain water." << endl;
        transition(WashingMachineState::Draining);
    }

    // start spinning
    void startSpinning() {
        cout << "Starting spinning." << endl;
        transition(WashingMachineState::Spinning);
    }

    //  stop the machine
    void stop() {
        cout << "Stopping the machine." << endl;
        transition(WashingMachineState::Idle);
    }
};

int main() {
    WashingMachine washingMachine;

    washingMachine.startFilling();
    washingMachine.startWashing();
    washingMachine.startDraining();
    washingMachine.startSpinning();
    washingMachine.stop();

    return 0;
}
