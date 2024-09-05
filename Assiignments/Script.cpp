#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Define the structure for states
struct State {
    string id;
    string name;
    vector<pair<string, string>> properties;
};

// Define the structure for transitions
struct Transition {
    string id;
    string name;
    string source;
    string target;
    vector<string> events;
    vector<string> actions;
};


string createStatesXML(const vector<State>& states) {
    stringstream xml;
    xml << "<states>\n";
    for (const State& state : states) {
        xml << "    <state id=\"" << state.id << "\" name=\"" << state.name << "\">\n";
        xml << "        <properties>\n";
        for (const auto& property : state.properties) {
            xml << "            <property name=\"" << property.first << "\" value=\"" << property.second << "\"/>\n";
        }
        xml << "        </properties>\n";
        xml << "    </state>\n";
    }
    xml << "</states>\n";
    return xml.str();
}


string createTransitionsXML(const vector<Transition>& transitions) {
    stringstream xml;
    xml << "<transitions>\n";
    for (const Transition& transition : transitions) {
        xml << "    <transition id=\"" << transition.id << "\" name=\"" << transition.name << "\" source=\"" << transition.source << "\" target=\"" << transition.target << "\">\n";
        xml << "        <events>\n";
        for (const string& event : transition.events) {
            xml << "            <event name=\"" << event << "\"/>\n";
        }
        xml << "        </events>\n";
        xml << "        <actions>\n";
        for (const string& action : transition.actions) {
            xml << "            <action name=\"" << action << "\"/>\n";
        }
        xml << "        </actions>\n";
        xml << "    </transition>\n";
    }
    xml << "</transitions>\n";
    return xml.str();
}

int main() {
    
    vector<State> washingMachineStates = {
        {"Idle", "Idle", {{"Power", "Off"}}},
        {"Filling", "Filling", {{"WaterLevel", "Low"}}},
        {"Washing", "Washing", {{"Cycle", "Normal"}}},
        {"Draining", "Draining", {{"WaterLevel", "Empty"}}},
        {"Spinning", "Spinning", {{"Speed", "High"}}},
        {"Finished", "Finished", {{"Power", "Off"}}}
    };

    vector<Transition> washingMachineTransitions = {
        {"1", "Start Filling", "Idle", "Filling", {"StartButtonPressed"}, {"StartFilling"}},
        {"2", "Start Washing", "Filling", "Washing", {"WaterFilled"}, {"StartWashing"}},
        {"3", "Start Draining", "Washing", "Draining", {"WashingCompleted"}, {"StartDraining"}},
        {"4", "Start Spinning", "Draining", "Spinning", {"WaterDrained"}, {"StartSpinning"}},
        {"5", "Finish", "Spinning", "Finished", {"SpinningCompleted"}, {"Stop"}}
    };

    
    vector<State> coffeeMakerStates = {
        {"Idle", "Idle", {{"CoffeeLevel", "Empty"}}},
        {"Brewing", "Brewing", {{"CoffeeLevel", "Full"}}},
        {"Finished", "Finished", {{"Power", "Off"}}}
    };

    vector<Transition> coffeeMakerTransitions = {
        {"1", "Start Brewing", "Idle", "Brewing", {"StartButtonPressed"}, {"StartBrewing"}},
        {"2", "Finish", "Brewing", "Finished", {"BrewingCompleted"}, {"Finish"}}
    };

    
    string washingMachineXML = createStatesXML(washingMachineStates) + createTransitionsXML(washingMachineTransitions);
    string coffeeMakerXML = createStatesXML(coffeeMakerStates) + createTransitionsXML(coffeeMakerTransitions);

    
    ofstream washingMachineFile("WashingMachine.xml");
    washingMachineFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<washing_machine>\n" << washingMachineXML << "</washing_machine>";
    washingMachineFile.close();

    ofstream coffeeMakerFile("CoffeeMaker.xml");
    coffeeMakerFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<coffee_maker>\n" << coffeeMakerXML << "</coffee_maker>";
    coffeeMakerFile.close();

    cout << "XML files generated for Washing Machine and Coffee Maker." << endl;

    return 0;
}
