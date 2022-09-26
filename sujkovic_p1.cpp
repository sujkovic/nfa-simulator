#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;
#include "Parser.h"

//             State Class            //

class State {
    public:
        State();
        void setStateNumber(string number);
        void setIsStartState(bool state);
        void setIsAcceptState(bool state);
        void setIsNormalState(bool state);
        string getStateNumber();
        bool getIsStartState();
        bool getIsAcceptState();
        bool getIsNormalState();
    private:
        string stateNumber = "";
        bool isStartState = false;
        bool isAcceptState = false;
        bool isNormalState = false;
};

//  Constructor
State::State() {
    stateNumber = "";
    isStartState = false;
    isAcceptState = false;
    isNormalState = false;
}
//  Setters
void State::setStateNumber(string number) {stateNumber = number;}
void State::setIsStartState(bool state) {isStartState = state;}
void State::setIsAcceptState(bool state) {isAcceptState = state;}
void State::setIsNormalState(bool state) {isNormalState = state;}
//  Getters
string State::getStateNumber() {return stateNumber;}
bool State::getIsStartState() {return isStartState;}
bool State::getIsAcceptState() {return isAcceptState;}
bool State::getIsNormalState() {return isNormalState;}

//          Transition Class            //

class Transition {
    public:
        Transition();
        void setStartState(string state);
        void setTransitionType(string type);
        void setEndState(string state);
        string getStartState();
        string getTransitionType();
        string getEndState();
    private:
        string startState = "";
        string transitionType = "";
        string endState = "";
};

//  Constructor
Transition::Transition() {
    startState = "";
    transitionType = "";
    endState = "";
}
//  Setters
void Transition::setStartState(string state) {startState = state;}
void Transition::setTransitionType(string type) {transitionType = type;}
void Transition::setEndState(string state) {endState = state;}
//  Getters
string Transition::getStartState() {return startState;}
string Transition::getTransitionType() {return transitionType;}
string Transition::getEndState() {return endState;}

//          Global Vars             //

string line;
State globalState;
Transition globalTransition;
vector<State> statesVec;
vector<Transition> transitionsVec;
vector<string> configurations(1000000, "");
vector<State> acceptStatesVec;
vector<State> finalAcceptStates;
vector<State> finalRejectStates;


//          Functions           //

bool doesStateExist(string state) {
    for (unsigned int i = 0; i < statesVec.size(); i++) {
        if (statesVec[i].getStateNumber() == state) {
            return true;
        }
    }
    return false;
}

//  For debugging
void showStatesVec() {
    for (unsigned int i = 0; i < statesVec.size(); i++) {
        cout << "State " << statesVec[i].getStateNumber() << " ";
        if (statesVec[i].getIsStartState() == true) { cout << "Start "; }
        if (statesVec[i].getIsAcceptState() == true) { cout << "Accept "; }
        if (statesVec[i].getIsNormalState() == true) { cout << "Normal "; }
        cout << endl; 
    }
}
//  Also for debugging
void showTransitionsVec() {
    for (unsigned int i = 0; i < transitionsVec.size(); i++) {
        string start = transitionsVec[i].getStartState();
        string trans = transitionsVec[i].getTransitionType();
        string end = transitionsVec[i].getEndState();
        cout << "Transition " << start << " " << trans << " " << end << endl; 
    }
}
//also for debugging
void showAcceptStatesVec() {
    for (unsigned int i = 0; i < transitionsVec.size(); i++) {
        string start = transitionsVec[i].getStartState();
        string trans = transitionsVec[i].getTransitionType();
        string end = transitionsVec[i].getEndState();
        cout << "Transition " << start << " " << trans << " " << end << endl; 
    }
}

State &getStartState() {
    for (unsigned int i = 0; i < statesVec.size(); i++) {
        if (statesVec[i].getIsStartState()) {
            return statesVec[i];
        }
    }
}

//  The magical function

void runFA(string currentString) {
    //  make vector of accept states
    for (unsigned int k = 0; k < statesVec.size(); k++) {
        if (statesVec[k].getIsAcceptState()) {
            acceptStatesVec.push_back(statesVec[k]);
        }
    }


    vector<State> curStates;
    curStates.push_back(getStartState());
    string currentTransitionType = "";
    //  Loop through input string
    while (currentString != "") {
        vector<State> nextState;
        
        for (unsigned int i = 0; i < curStates.size(); i++) {
            for (unsigned int j = 0; j < transitionsVec.size(); j++) {
                if (transitionsVec[j].getStartState() == curStates[i].getStateNumber() && transitionsVec[j].getTransitionType() == string(1, currentString[0])) {
                    for (unsigned int m = 0; m < statesVec.size(); m++) {
                        if (statesVec[m].getStateNumber() == transitionsVec[j].getEndState()) {
                            nextState.push_back(statesVec[m]);
                        }
                    }
                }
            }
        }

        curStates = nextState;

        //  get all final accept states
        for (unsigned int i = 0; i < curStates.size(); i++) {
            for (unsigned int j = 0; j < acceptStatesVec.size(); j++) {
                if (curStates[i].getStateNumber() == acceptStatesVec[j].getStateNumber()) {
                    bool doesStateAlreadyExist = false;
                    for (unsigned int k = 0; k < finalAcceptStates.size(); k++) {
                        if (curStates[i].getStateNumber() == finalAcceptStates[k].getStateNumber()) {
                            doesStateAlreadyExist = true;
                        }
                    }
                    if (!doesStateAlreadyExist) {
                        finalAcceptStates.push_back(curStates[i]);
                    }
                    doesStateAlreadyExist = false;
                }
            }
        }
        
        //  Delete first letter/number of input string
        if (currentString.length() > 1) {
            currentString = currentString.substr(1, currentString.length() - 1);
        }
        else if (currentString.length() == 1) {
            currentString = "";
        }
    }

    if (finalAcceptStates.size() > 0) {
            cout << "accept ";
            for (unsigned int j = 0; j < finalAcceptStates.size(); j++) {
                cout << finalAcceptStates[j].getStateNumber() << " ";
            }
            cout << endl;
        }
        else {
            cout << "reject ";
            for (unsigned int k = 0; k < curStates.size(); k++) {
                cout << curStates[k].getStateNumber() << " ";
            }
            cout << endl;
        }
    
}


//              Main               //

int main(int argc, char **argv)
{
    ifstream inputFile;

    if (argc != 3) {
        cout << "Incorrect input. Correct format: ./sujkovic_p1 <input-file> <input-string>" << endl;
        return 1;
    }

    string inputString = argv[2];

    //  Read in input
    inputFile.open(argv[1]);
    while(!inputFile.eof()) {
        //  Reset globalState object
        globalState.setIsStartState(false);
        globalState.setIsAcceptState(false);
        globalState.setIsNormalState(false);
        //  Read current line to parser
        getline(inputFile, line);
        Parser command(line);
        //  Check what type of state is being read then add it to statesVec
        if (command.getOperation() == "state") {
            globalState.setStateNumber(command.getArg1());
            if (command.numArgs() == 2) {
                if (command.getArg2() == "accept") {
                    globalState.setIsAcceptState(true);
                }
                else if (command.getArg2() == "start") {
                    globalState.setIsStartState(true);
                }
            }
            else if (command.numArgs() == 3) {
                if (command.getArg2() == "accept" && command.getArg3() == "start") {
                    globalState.setIsAcceptState(true);
                    globalState.setIsStartState(true);
                }
                else if (command.getArg2() == "accept" && command.getArg3() == "start") {
                    globalState.setIsAcceptState(true);
                    globalState.setIsStartState(true);
                }
            }
            statesVec.push_back(globalState);
        }
        //  Add normal states to statesVec
        else if (command.getOperation() == "transition") {
            //  Check if starting state of transition exists. 
            //  If it doesn't, add to states vec.
            if (!doesStateExist(command.getArg1())) {
                globalState.setStateNumber(command.getArg1());
                globalState.setIsNormalState(true);
                statesVec.push_back(globalState);
            }
            //  Check if ending state of transition exists.
            //  If it doesn't, add to states vec.
            if (!doesStateExist(command.getArg3())) {
                globalState.setStateNumber(command.getArg3());
                globalState.setIsNormalState(true);
                statesVec.push_back(globalState);
            }
            //  Add transition to transitionsVec
            globalTransition.setStartState(command.getArg1());
            globalTransition.setTransitionType(command.getArg2());
            globalTransition.setEndState(command.getArg3());
            transitionsVec.push_back(globalTransition);
        }
    }
    inputFile.close();

    //showStatesVec();
    //showTransitionsVec();

    runFA(inputString);
    
    return 1;
}


//  initialize vector to 1 million, each to -1
//  


//  3 newsted loops
// outer most reads input string, next is configrations, final is all transitions




/*          backup 
string curState = getStartState();
    string currentTransitionType = "";
    //  Loop through input string
    while (currentString != "") {
        //  Loop through current configurations
        while (configurations[i] != "" || i == 0) {
            
        }

        currentTransitionType = currentString[0];
        for (unsigned int i = 0; i < transitionsVec.size(); i++) {
            if (transitionsVec[i].getStartState() == curState && transitionsVec[i].getTransitionType() == currentTransitionType) {

            }
        }

        //  Delete first letter/number of input string
        if (currentString.length() > 1) {
            currentString = currentString.substr(1, currentString.length() - 1);
        }
        else if (currentString.length() == 1) {
            currentString = "";
        }
    }
*/