#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;

struct State {
    int x, y;
    double g, h, f;
    bool solved;
    bool isMaxNode; 
    vector<State*> children;
    
    State(int x, int y, double g, bool isMax) : x(x), y(y), g(g), h(0), f(0), solved(false), isMaxNode(isMax) {}
};

double heuristic(State* s, State* goal) {
    return abs(s->x - goal->x) + abs(s->y - goal->y);
}

bool isGoalState(State* node, State* goal) {
    return (node->x == goal->x && node->y == goal->y);
}

double alphaBetaSearch(State* node, State* goal, double alpha, double beta, 
                    int depth, int maxDepth, set<pair<int,int>>& visited) {
    
    if (depth >= maxDepth || isGoalState(node, goal)) {
        node->f = node->g + heuristic(node, goal);
        if (isGoalState(node, goal)) {
            node->solved = true;
            node->f = node->g; 
        }
        return node->f;
    }
    
    pair<int,int> pos = {node->x, node->y};
    if (visited.count(pos)) {
        return node->f;
    }
    visited.insert(pos);
    
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    
    for (int k = 0; k < 4; k++) {
        int nx = node->x + dx[k];
        int ny = node->y + dy[k];
        
        if (nx >= 0 && ny >= 0 && nx < 5 && ny < 5) {
            State* child = new State(nx, ny, node->g + 1, !node->isMaxNode);
            node->children.push_back(child);
        }
    }
    
    if (node->children.empty()) {
        node->f = (node->isMaxNode) ? -1e9 : 1e9; 
        visited.erase(pos);
        return node->f;
    }
    
    double bestValue;
    
    if (node->isMaxNode) {
        bestValue = -1e9;
        for (State* child : node->children) {
            double childValue = alphaBetaSearch(child, goal, alpha, beta, depth + 1, maxDepth, visited);
            bestValue = max(bestValue, childValue);
            alpha = max(alpha, bestValue);
            
            if (beta <= alpha) {
                cout << "Pruning at MAX node (" << node->x << "," << node->y << ")" 
                    << " alpha=" << alpha << " beta=" << beta << endl;
                break; 
            }
        }
    } else {
        bestValue = 1e9;
        for (State* child : node->children) {
            double childValue = alphaBetaSearch(child, goal, alpha, beta, depth + 1, maxDepth, visited);
            bestValue = min(bestValue, childValue);
            beta = min(beta, bestValue);
            
            if (beta <= alpha) {
                cout << "Pruning at MIN node (" << node->x << "," << node->y << ")" 
                    << " alpha=" << alpha << " beta=" << beta << endl;
                break; 
            }
        }
    }
    
    node->f = bestValue;
    visited.erase(pos);
    return bestValue;
}

void printPath(State* node, State* goal, int depth = 0) {
    if (!node) return;
    
    cout << string(depth * 2, ' ') << "(" << node->x << "," << node->y << ") "
        << (node->isMaxNode ? "MAX" : "MIN") << " f=" << node->f << endl;
    
    if (isGoalState(node, goal)) {
        cout << string(depth * 2, ' ') << "GOAL REACHED!" << endl;
        return;
    }
    
    State* bestChild = nullptr;
    double bestValue = node->isMaxNode ? -1e9 : 1e9;
    
    for (State* child : node->children) {
        if (node->isMaxNode && child->f > bestValue) {
            bestValue = child->f;
            bestChild = child;
        } else if (!node->isMaxNode && child->f < bestValue) {
            bestValue = child->f;
            bestChild = child;
        }
    }
    
    if (bestChild && depth < 10) { 
        printPath(bestChild, goal, depth + 1);
    }
}

void cleanup(State* node) {
    if (!node) return;
    for (State* child : node->children) {
        cleanup(child);
    }
    delete node;
}

int main() {
    int sx, sy, gx, gy;
    cout << "Enter start coordinates (x y): ";
    cin >> sx >> sy;
    cout << "Enter goal coordinates (x y): ";
    cin >> gx >> gy;
    
    int maxDepth;
    cout << "Enter maximum search depth: ";
    cin >> maxDepth;
    
    State* start = new State(sx, sy, 0, true);
    State* goal = new State(gx, gy, 0, false);
    
    set<pair<int,int>> visited;
    
    double result = alphaBetaSearch(start, goal, -1e9, 1e9, 0, maxDepth, visited);
    
    cout << "\nFinal result: " << result << endl;
    printPath(start, goal);
        
    return 0;
}