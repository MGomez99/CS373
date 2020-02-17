#ifndef NFA_H
#define NFA_H
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <set>
using namespace std;

struct node
{
    int state;
    bool isAccept;
    vector<pair<char, node>> adjacent_nodes;
    node() : state(-1), isAccept(false){}
    node(int i, bool b): state(i), isAccept(b){}
};

node STARTNODE;

unordered_map<int, node> parseInput(string inputfile){
    string line, condition1, condition2;
    bool start_found = false;
    int state_num = -1;
    int transition_num = -1;
    char symbol;
    ifstream infile(inputfile);
    unordered_map<int, node>  NFA; //NFA has the node number as the key and the node itself as values
    if(!infile){
        cout << "input file not found" << endl;
        return NFA;
    }
    int counter = 1;
    if(infile.is_open()){
        //while((!infile.eof()) && (infile.peek() != -1) && (infile.peek() != 10)){
        while((!infile.eof())){
            //STATE DEFINITION
            if(infile.peek() == 's' ){
                getline(infile, line);
                stringstream current_line(line);
                    //the format for a state defintion is 'state    [#]    [start/accept]    [start/accept]'
                string temp;
                current_line >> temp >> state_num >> condition1;
                
                if(!current_line.eof()){
                    current_line >> condition2;
                }
                //@DEBUG
                if(!current_line.eof()){
                    cout << "not EOL..."; 
                }
                //Now that we extracted the line contents, we have to make a node and add it to the NFA
                node n = node();
                n.state = state_num;
                    //check accept condition
                if(condition1 == "accept" || condition2 == "accept"){
                    n.isAccept = true;
                }
                    //there should only be 1 start node
                if(!start_found && (condition1 == "start" || condition2 == "start")){
                    start_found == true;
                    STARTNODE = n;
                }
                NFA[state_num] = n;
                //we'll deal with the adjacent nodes in a different check
                
            }
            //TRANSITION DEFINITION
            else if(infile.peek() == 't' ){

                //the format for a state defintion is 'transition    [starting]    [symbol]    [destination]'
                getline(infile, line);
                stringstream current_line(line);
                string temp;
                current_line >> temp >> state_num >> symbol >> transition_num;
                    //if the starting state of the transition does not exist, add it to the NFA
                if(NFA.find(state_num) == NFA.end()){
                    NFA[state_num] = node(state_num, false);
                }
                    //similarly for destination state
                if(NFA.find(transition_num) == NFA.end()){
                    NFA[transition_num] = node(transition_num, false);
                }
                    //add the node to the respective adjacency list
                vector<pair<char, node>>& current_list = NFA[state_num].adjacent_nodes;
                node target = NFA[transition_num];
                pair<char, node> transition = make_pair(symbol, target);
                current_list.push_back(transition);
                
             }

        }
    }
    infile.close();
    return NFA;

}
void isAccepted(string input, unordered_map<int, node> NFA){
    
    set<int> current_available_states;
    current_available_states.insert(STARTNODE.state);
    set<int> next_states;
    //iterate over the string
    for(int i = 0; i < input.length(); i++){
        char current_symbol = input[i];
        next_states.clear();
        //iterate over all current configurations
        for(int current_state: current_available_states){
            //iterate over all adjacencies  
            for(pair<char, node> p: NFA[current_state].adjacent_nodes){
                if(p.first == current_symbol){
                    next_states.insert(p.second.state);
                }
                //for each adjacency, add valid transitions to the vector of next states
                //we only added reachable nodes
                //we've generated the next list of states.
            }
        }
        current_available_states = next_states;
    }
    //we're now at the end of the string, and all of the current states are stored in current_available_states
    set<int> accept_states_reached;
    for(int state : current_available_states){
        if(NFA[state].isAccept == true){
            accept_states_reached.insert(state);
        }
    }
    if(!accept_states_reached.empty()){
        cout<< "accept";
        for(int state: accept_states_reached){
            cout<<" "<<state;
        }
        cout<<endl;
    }
    else{
        cout<<"reject";
        for(int i : current_available_states){
            cout<<" "<<i;
        }
        cout<<endl;
    }
    return;

}


#endif