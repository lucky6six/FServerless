#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>

#include "config.h"

#define node string // 以ip表示node

using namespace std;

// class Node{
//     public:
//         string ip;
// }

class NodeTable {
public:
    vector<node> nodeList;
    NodeTable();
    ~NodeTable();
    
    // when create the first entity for a function
    node selectNode();
};

#endif // __NODE_H__