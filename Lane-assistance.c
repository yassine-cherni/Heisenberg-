#include <opencv2/opencv.hpp>

int main() {
    // Open a video stream or read frames from a camera
    cv::VideoCapture cap("your_video_file.mp4");

    if (!cap.isOpened()) {
        std::cerr << "Error opening video file." << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "End of video stream." << std::endl;
            break;
        }

        // Convert the frame to grayscale
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Apply GaussianBlur to reduce noise
        cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);

        // Use Canny edge detector to find edges
        cv::Mat edges;
        cv::Canny(gray, edges, 50, 150);

        // Define region of interest (ROI) for lane detection
        cv::Mat mask = cv::Mat::zeros(edges.size(), edges.type());
        cv::Point pts[4] = {cv::Point(0, frame.rows), cv::Point(frame.cols / 2, frame.rows / 2),
                            cv::Point(frame.cols, frame.rows)};
        cv::fillConvexPoly(mask, pts, 3, cv::Scalar(255, 255, 255));

        // Apply mask to focus on the region of interest
        cv::bitwise_and(edges, mask, edges);

        // Use HoughLines to detect lines in the image
        std::vector<cv::Vec2f> lines;
        cv::HoughLines(edges, lines, 1, CV_PI / 180, 100);

        // Draw lines on the original frame
        for (size_t i = 0; i < lines.size(); i++) {
            float rho = lines[i][0], theta = lines[i][1];
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            cv::Point pt1(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
            cv::Point pt2(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
            cv::line(frame, pt1, pt2, cv::Scalar(0, 0, 255), 2);
        }

        // Display the result
        cv::imshow("Lane Assist", frame);

        if (cv::waitKey(30) == 27) {
            // Press 'Esc' to exit the program
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
