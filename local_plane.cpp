#include <opencv2/opencv.hpp>

int main() {
    // Load left and right images
    cv::Mat leftImage = cv::imread("left_image.png", cv::IMREAD_GRAYSCALE);
    cv::Mat rightImage = cv::imread("right_image.png", cv::IMREAD_GRAYSCALE);
    
    // Initialize the disparity map
    cv::Mat disparityMap = cv::Mat::zeros(leftImage.size(), CV_16S);
    
    // Number of depth hypotheses
    int numDepthHypotheses = 16;  // You can adjust this
    
    // Depth range
    int minDepth = 1;  // Minimum depth value
    int maxDepth = 255;  // Maximum depth value
    
    // Iterate through image pixels
    for (int y = 0; y < leftImage.rows; ++y) {
        for (int x = 0; x < leftImage.cols; ++x) {
            // Generate depth hypotheses
            for (int h = 0; h < numDepthHypotheses; ++h) {
                double depth = minDepth + (maxDepth - minDepth) * (h / static_cast<double>(numDepthHypotheses));
                
                // Calculate matching cost for the current depth hypothesis
                double cost = 0.0;
                for (int wx = -1; wx <= 1; ++wx) {
                    for (int wy = -1; wy <= 1; ++wy) {
                        int refX = x + wx;
                        int refY = y + wy;
                        int refIntensity = leftImage.at<uchar>(refY, refX);
                        
                        // Calculate corresponding position in the right image based on depth
                        int rightX = refX - static_cast<int>(depth);
                        
                        if (rightX >= 0 && rightX < rightImage.cols) {
                            int rightIntensity = rightImage.at<uchar>(refY, rightX);
                            cost += std::abs(refIntensity - rightIntensity);
                        }
                    }
                }
                
                // Update disparity map if this depth hypothesis has lower cost
                if (cost < disparityMap.at<short>(y, x) || h == 0) {
                    disparityMap.at<short>(y, x) = static_cast<short>(cost);
                }
            }
        }
    }
    
    // Normalize and visualize the disparity map
    cv::normalize(disparityMap, disparityMap, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::imshow("Disparity Map", disparityMap);
    cv::waitKey(0);
    
    return 0;
}
