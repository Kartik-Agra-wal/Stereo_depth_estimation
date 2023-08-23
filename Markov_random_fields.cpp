#include <iostream>
#include <vector>
#include <maxflow-v3.03/graph.h>

int main() {
    int numPixels = 100;  // Number of pixels
    int numDisparities = 16;  // Number of possible disparity values
    
    // Simulated data costs (negative log-likelihoods)
    std::vector<std::vector<int>> dataCosts(numPixels, std::vector<int>(numDisparities, 0));
    
    // Simulated smoothness costs (pairwise potentials)
    std::vector<std::vector<int>> smoothnessCosts(numDisparities, std::vector<int>(numDisparities, 0));
    
    // Create a graph
    Graph<int, int, int> g(numPixels, numDisparities * numPixels);
    
    // Add nodes with data costs
    for (int pixel = 0; pixel < numPixels; ++pixel) {
        for (int disparity = 0; disparity < numDisparities; ++disparity) {
            g.add_node();
            g.add_tweights(pixel * numDisparities + disparity, dataCosts[pixel][disparity], 0);
        }
    }
    
    // Add edges with smoothness costs (pairwise potentials)
    for (int pixel = 0; pixel < numPixels - 1; ++pixel) {
        for (int disparityA = 0; disparityA < numDisparities; ++disparityA) {
            for (int disparityB = 0; disparityB < numDisparities; ++disparityB) {
                g.add_edge(pixel * numDisparities + disparityA,
                           (pixel + 1) * numDisparities + disparityB,
                           smoothnessCosts[disparityA][disparityB],
                           smoothnessCosts[disparityA][disparityB]);
            }
        }
    }
    
    // Run the graph cut algorithm
    int flow = g.maxflow();
    
    // Obtain the optimal disparity values
    std::vector<int> optimalDisparities(numPixels);
    for (int pixel = 0; pixel < numPixels; ++pixel) {
        for (int disparity = 0; disparity < numDisparities; ++disparity) {
            if (g.what_segment(pixel * numDisparities + disparity) == Graph<int, int, int>::SOURCE)
                optimalDisparities[pixel] = disparity;
        }
    }
    
    // Print the optimal disparity values
    for (int pixel = 0; pixel < numPixels; ++pixel) {
        std::cout << "Pixel " << pixel << ": Disparity " << optimalDisparities[pixel] << std::endl;
    }
    
    return 0;
}
