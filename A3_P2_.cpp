#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<vector<pair<int,int>>> adjList;
vector<ll> nodeMaxDistance;
vector<bool> isKeyCampsite;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int numNodes, numKeyCampsites;
    cin >> numNodes >> numKeyCampsites;
    adjList.resize(numNodes + 1);
    nodeMaxDistance.resize(numNodes + 1, -1);
    isKeyCampsite.resize(numNodes + 1, false);
    vector<int> keyCampsites(numKeyCampsites);
    for (int i = 0; i < numKeyCampsites; i++){
        cin >> keyCampsites[i];
        isKeyCampsite[keyCampsites[i]] = true;
    }
    for (int i = 1; i <= numNodes - 1; i++){
        int parentNode, edgeWeight;
        cin >> parentNode >> edgeWeight;
        int childNode = i + 1;
        adjList[parentNode].push_back({childNode, edgeWeight});
        adjList[childNode].push_back({parentNode, edgeWeight});
    }
    

    vector<int> parentNode(numNodes + 1, -1), dfsOrder;
    vector<bool> visited(numNodes + 1, false);
    {
        stack<int> traversalStack;
        traversalStack.push(1);
        parentNode[1] = -1;
        visited[1] = true;
        while(!traversalStack.empty()){
            int currNode = traversalStack.top();
            traversalStack.pop();
            dfsOrder.push_back(currNode);
            for(auto &edge : adjList[currNode]){
                int neighbor = edge.first;
                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    parentNode[neighbor] = currNode;
                    traversalStack.push(neighbor);
                }
            }
        }
    }
    

    vector<ll> maxDownDistance(numNodes + 1, -1);
    for (int i = dfsOrder.size() - 1; i >= 0; i--){
        int currNode = dfsOrder[i];
        maxDownDistance[currNode] = (isKeyCampsite[currNode] ? 0 : -1);
        for(auto &edge : adjList[currNode]){
            int neighbor = edge.first, edgeWeight = edge.second;
            if(neighbor == parentNode[currNode]) continue;
            if(maxDownDistance[neighbor] != -1){
                ll candidateDistance = maxDownDistance[neighbor] + edgeWeight;
                if(candidateDistance > maxDownDistance[currNode])
                    maxDownDistance[currNode] = candidateDistance;
            }
        }
    }
    
    struct DFSState{
        int node, parent;
        ll maxUpDistance;
    };
    stack<DFSState> stateStack;
    stateStack.push({1, -1, -1});
    while(!stateStack.empty()){
        DFSState currentState = stateStack.top();
        stateStack.pop();
        int currNode = currentState.node;
        ll parentMaxDistance = currentState.maxUpDistance;
        ll overallMaxDistance = max(parentMaxDistance, maxDownDistance[currNode]);
        nodeMaxDistance[currNode] = overallMaxDistance;
        
        vector<int> childNodes;
        vector<ll> childCandidate;
        vector<int> childEdgeWeight;
        for(auto &edge : adjList[currNode]){
            int neighbor = edge.first, weight = edge.second;
            if(neighbor == currentState.parent) continue;
            childNodes.push_back(neighbor);
            ll candidate = (maxDownDistance[neighbor] == -1 ? -1 : maxDownDistance[neighbor] + weight);
            childCandidate.push_back(candidate);
            childEdgeWeight.push_back(weight);
        }
        
        int numChildren = childNodes.size();
        if(numChildren == 0) continue;
        vector<ll> prefixMax(numChildren), suffixMax(numChildren);
        prefixMax[0] = childCandidate[0];
        for (int i = 1; i < numChildren; i++){
            prefixMax[i] = max(prefixMax[i - 1], childCandidate[i]);
        }
        suffixMax[numChildren - 1] = childCandidate[numChildren - 1];
        for (int i = numChildren - 2; i >= 0; i--){
            suffixMax[i] = max(suffixMax[i + 1], childCandidate[i]);
        }
        ll baseCandidate = max(parentMaxDistance, (isKeyCampsite[currNode] ? 0LL : -1LL));
        for (int i = 0; i < numChildren; i++){
            ll siblingMax = -1;
            if(i > 0)
                siblingMax = max(siblingMax, prefixMax[i - 1]);
            if(i < numChildren - 1)
                siblingMax = max(siblingMax, suffixMax[i + 1]);
            ll candidateForChild = max(baseCandidate, siblingMax);
            ll newParentDistance = (candidateForChild == -1 ? -1 : candidateForChild + childEdgeWeight[i]);
            stateStack.push({childNodes[i], currNode, newParentDistance});
        }
    }
    
    for (int i = 1; i <= numNodes; i++){
        cout << nodeMaxDistance[i] << "\n";
    }
    return 0;
}