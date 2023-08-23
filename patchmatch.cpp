#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>

int main() {
    // Load left and right images
    cv::Mat leftImage = cv::imread("left_image.png", cv::IMREAD_GRAYSCALE);
    cv::Mat rightImage = cv::imread("right_image.png", cv::IMREAD_GRAYSCALE);
    
    // Initialize the disparity map
    cv::Mat disparityMap = cv::Mat::zeros(leftImage.size(), CV_16S);
    
    // Number of iterations
    int numIterations = 5;
    
    // Patch size for propagation
    int patchSize = 7;
    
    // Random search range
    int searchRange = 20;
    
    // Initialize random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Iterate through iterations
    for (int iteration = 0; iteration < numIterations; ++iteration) {
        for (int y = 0; y < leftImage.rows; ++y) {
            for (int x = 0; x < leftImage.cols; ++x) {
                // Get the reference pixel in the left image
                int refIntensity = leftImage.at<uchar>(y, x);
                
                // Propagation step: Update disparity using neighboring pixels
                // Propagate from top, left, right, and bottom neighbors
                // Update disparity based on the best-matching pixel's disparity
                
                // Random search step: Explore search space and update disparity
                int bestDisparity = disparityMap.at<short>(y, x);
                int bestCost = INT_MAX;
                for (int dx = -searchRange; dx <= searchRange; ++dx) {
                    for (int dy = -searchRange; dy <= searchRange; ++dy) {
                        int newX = x + dx;
                        int newY = y + dy;
                        
                        // Check boundary conditions
                        if (newX >= 0 && newX < leftImage.cols && newY >= 0 && newY < leftImage.rows) {
                            int cost = 0;
                            
                            // Calculate matching cost for the patch
                            // Update bestDisparity and bestCost if a better match is found
                        }
                    }
                }
                
                // Aggregation step: Update disparity based on best match
                disparityMap.at<short>(y, x) = static_cast<short>(bestDisparity);
            }
        }
    }
    
    // Normalize and visualize the disparity map
    cv::normalize(disparityMap, disparityMap, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::imshow("Disparity Map", disparityMap);
    cv::waitKey(0);
    
    return 0;
}
