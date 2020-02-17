#include "gomez_p1.h"
using namespace std;

int main(int argc, char *argv[]){

    if(argc < 3){
        if(argc == 1){
            cout <<"Please provide an input file to create the NFA. Usage: './gomez_p1 [input file] [string to test]"<<endl;
            return -1;
        }
        else{
            cout<< "Warning: test string not specified. Printing out created NFA instead..."<<endl;
            
        }
    }   

    string filename = argv[1];
    unordered_map<int, node> NFA = parseInput(filename);
    vector<int> keys;
    vector<int> accept_states;
    
    //allocate memory for the keys (node/state #s)
    for(auto kv : NFA){
        keys.push_back(kv.first);
        if(kv.second.isAccept) accept_states.push_back(kv.first);
    }

    //NO TEST STRING PROVIDED
    if(argc == 2){
        cout<< "Start State: " << STARTNODE.state <<endl;
        for(int i = 0; i < keys.size(); i++){
            cout << "State " << keys[i];
            if(NFA[keys[i]].isAccept) cout << "\t*ACCEPT*\tTransitions(Symbol, State):\t";
            else cout <<"\t\t\tTransitions(Symbol, State):\t";
            vector<pair<char, node>> v = NFA[keys[i]].adjacent_nodes;
            for(int j = 0; j < v.size(); j++){
                cout << "("<< v[j].first <<"," << v[j].second.state << ")\t";
            }
            cout<<endl;
        }
        return 0;
    }
    //SEE IF TEST STRING IS ACCEPTED OR REJECTED
    string s = argv[2];
    isAccepted(s, NFA);
    return 0;
    
}