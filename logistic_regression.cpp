#include <iostream>
#include <cmath>
#include <vector>

// Logistic function (sigmoid)
double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

// Hypothesis function
double hypothesis(const std::vector<double>& theta, const std::vector<double>& features) {
    if (theta.size() != features.size()) {
        std::cerr << "Error: Size mismatch in hypothesis function" << std::endl;
        return 0.0;
    }

    double result = 0.0;
    for (size_t i = 0; i < theta.size(); ++i) {
        result += theta[i] * features[i];
    }

    return sigmoid(result);
}

// Cost function
double costFunction(const std::vector<std::vector<double>>& X,
                    const std::vector<int>& y,
                    const std::vector<double>& theta) {
    size_t m = X.size();
    double J = 0.0;

    for (size_t i = 0; i < m; ++i) {
        double h = hypothesis(theta, X[i]);
        J += -y[i] * log(h) - (1 - y[i]) * log(1 - h);
    }

    return J / m;
}

// Gradient descent
void gradientDescent(std::vector<std::vector<double>>& X,
                     std::vector<int>& y,
                     std::vector<double>& theta,
                     double alpha,
                     int numIterations) {
    size_t m = X.size();
    size_t n = X[0].size();

    for (int iteration = 0; iteration < numIterations; ++iteration) {
        std::vector<double> grad(n, 0.0);

        for (size_t i = 0; i < m; ++i) {
            double h = hypothesis(theta, X[i]);
            double error = h - y[i];

            for (size_t j = 0; j < n; ++j) {
                grad[j] += error * X[i][j];
            }
        }

        for (size_t j = 0; j < n; ++j) {
            theta[j] -= alpha * grad[j] / m;
        }

        // Display cost every 100 iterations
        if (iteration % 100 == 0) {
            std::cout << "Iteration " << iteration << ", Cost: " << costFunction(X, y, theta) << std::endl;
        }
    }
}

int main() {
    // Example data
    std::vector<std::vector<double>> X = {{1, 2}, {1, 3}, {1, 4}, {1, 5}}; // Features
    std::vector<int> y = {0, 0, 1, 1}; // Labels

    // Initial parameters
    std::vector<double> theta = {0, 0};

    // Hyperparameters
    double alpha = 0.01; // Learning rate
    int numIterations = 1000;

    // Train the logistic regression model
    gradientDescent(X, y, theta, alpha, numIterations);

    // Display the trained parameters
    std::cout << "Trained Parameters: ";
    for (size_t i = 0; i < theta.size(); ++i) {
        std::cout << theta[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
