#include <iostream>
#include <vector>
#include <maxflow-v3.03/graph.h>

int main() {
    int numPixelsX = 10;  // Number of pixels along X-axis
    int numPixelsY = 10;  // Number of pixels along Y-axis
    int numDisparities = 16;  // Number of possible disparity values
    
    // Simulated data costs (negative log-likelihoods)
    std::vector<std::vector<std::vector<int>>> dataCosts(numPixelsY,
        std::vector<std::vector<int>>(numPixelsX, std::vector<int>(numDisparities, 0)));
    
    // Create a graph
    Graph<int, int, int> g(numPixelsX * numPixelsY, numDisparities * numPixelsX * numPixelsY);
    
    // Add nodes with data costs
    for (int y = 0; y < numPixelsY; ++y) {
        for (int x = 0; x < numPixelsX; ++x) {
            for (int disparity = 0; disparity < numDisparities; ++disparity) {
                g.add_node();
                g.add_tweights(y * numPixelsX + x + disparity * numPixelsX * numPixelsY,
                               dataCosts[y][x][disparity], 0);
            }
        }
    }
    
    // Add horizontal edges with smoothness costs
    for (int y = 0; y < numPixelsY; ++y) {
        for (int x = 0; x < numPixelsX - 1; ++x) {
           
