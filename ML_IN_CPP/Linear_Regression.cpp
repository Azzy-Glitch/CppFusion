#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to calculate the mean of a vector
double mean(const vector<double> &values)
{
    double sum = 0.0;
    for (double val : values)
    {
        sum += val;
    }
    return sum / values.size();
}

// Function to calculate the slope (m) and intercept (b) for Linear Regression
void linear_regression(const vector<double> &X, const vector<double> &y, double &m, double &b)
{
    double mean_X = mean(X);
    double mean_y = mean(y);

    double numerator = 0.0;
    double denominator = 0.0;

    for (size_t i = 0; i < X.size(); ++i)
    {
        numerator += (X[i] - mean_X) * (y[i] - mean_y);
        denominator += pow(X[i] - mean_X, 2);
    }

    m = numerator / denominator; // Slope
    b = mean_y - m * mean_X;     // Intercept
}

// Function to predict the value based on the learned parameters
double predict(double x, double m, double b)
{
    return m * x + b;
}

int main()
{
    // Step 1: Prepare the data (hours studied and exam scores)
    vector<double> hours_studied = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};        // Feature (X)
    vector<double> exam_scores = {50, 55, 60, 65, 70, 75, 80, 85, 90, 95}; // Label (y)

    // Step 2: Train the Linear Regression model
    double slope = 0.0, intercept = 0.0;
    linear_regression(hours_studied, exam_scores, slope, intercept);

    // Output the learned slope and intercept
    cout << "Learned Slope (m): " << slope << endl;
    cout << "Learned Intercept (b): " << intercept << endl;

    // Step 3: Make a prediction for 7.5 hours of study
    double hours_to_predict = 7.5;
    double predicted_score = predict(hours_to_predict, slope, intercept);

    cout << "Predicted score for " << hours_to_predict << " hours of study: " << predicted_score << endl;

    return 0;
}
