#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct node
{
    int state;
    bool isAccept;
    vector<pair<node, char>> adjacent_nodes;
    node() : state(-1), isAccept(false){}
};

