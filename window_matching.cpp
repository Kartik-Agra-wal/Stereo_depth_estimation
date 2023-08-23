#include <opencv2/opencv.hpp>

int main() {
    // Load the left and right stereo images (grayscale)
    cv::Mat leftImage = cv::imread("left_image.png", cv::IMREAD_GRAYSCALE);
    cv::Mat rightImage = cv::imread("right_image.png", cv::IMREAD_GRAYSCALE);
    
    // Define the window size for matching
    int windowSize = 5;  // You can adjust this based on your requirements
    
    // Create a disparity map to store the calculated disparities
    cv::Mat disparityMap(leftImage.rows, leftImage.cols, CV_16S);
    
    // Loop through each pixel in the left image
    for (int y = 0; y < leftImage.rows; ++y) {
        for (int x = 0; x < leftImage.cols; ++x) {
            // Define the search window in the right image
            int min_x = std::max(x - windowSize, 0);
            int max_x = std::min(x + windowSize, rightImage.cols - 1);
            
            int bestDisparity = 0;
            int minSSD = INT_MAX;
            
            // Search for the best disparity in the search window
            for (int d = 0; d < max_x - min_x - windowSize; ++d) {
                int ssd = 0;
                
                // Calculate the sum of squared differences (SSD)
                for (int wy = -windowSize; wy <= windowSize; ++wy) {
                    for (int wx = -windowSize; wx <= windowSize; ++wx) {
                        int leftPixel = leftImage.at<uchar>(y + wy, x + wx);
                        int rightPixel = rightImage.at<uchar>(y + wy, min_x + d + wx);
                        ssd += (leftPixel - rightPixel) * (leftPixel - rightPixel);
                    }
                }
                
                // Update the best disparity if SSD is smaller
                if (ssd < minSSD) {
                    minSSD = ssd;
                    bestDisparity = d;
                }
            }
            
            // Store the best disparity in the disparity map
            disparityMap.at<short>(y, x) = static_cast<short>(bestDisparity);
        }
    }
    
    // Normalize the disparity map for visualization
    cv::normalize(disparityMap, disparityMap, 0, 255, cv::NORM_MINMAX, CV_8U);
    
    // Display the disparity map
    cv::imshow("Disparity Map", disparityMap);
    cv::waitKey(0);
    
    return 0;
}
