/* 
# May 16, 2019
# Tran Le Anh - MSc Student in Computer Vision
# Dept. of Electronics Engineering, Myongji University, South Korea
# tranleanh.nt@gmail.com
# https://sites.google.com/view/leanhtran
*/

#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

float sigmoid(float x) {
	float output = (1 / (1 + exp(-x)));
	return output;
}

float sigmoid_derivative(float x) {
	float output = x*(1-x);
	return output;
}

int main() {

	// Dataset
	double x1[] = { 0.7, 0.6, 0.7, 0.7, 0.8, 0.9, 0.7, 0.4, 0.6, 0.6, 0.1, 0.4, 0.5, 0.9, 0.2, 0.1, 0.3, 0.4,
				    0.9, 0.2, 0.5, 0.8, 0.5, 0.2, 0.4, 0.3, 0.8, 0.5, 0.2, 0.9, 0.7, 0.3, 0.4, 0.2, 0.3, 0.7,
				    0.1, 0.5, 0.3, 0.3, 0.6, 0.8, 0.2, 0.9, 0.8, 0.6, 0.4, 0.1, 0.6, 0.7, 0.2, 0.1, 0.5, 0.7,
				    0.6, 0.3, 0.9, 0.2, 0.8, 0.8, 0.1, 0.9, 0.4, 0.5, 0.6, 0.1, 0.3, 0.1, 0.9, 0.1, 0.9, 0.7,
				    0.8, 0.6, 0.4, 0.5, 0.5, 0.3, 0.8, 0.2, 0.4 };

	double x2[] = { 0.6, 0.8, 0.1, 0.3, 0.7, 0.4, 0.9, 0.6, 0.9, 0.3, 0.9, 0.2, 0.8, 0.5, 0.4, 0.8, 0.4, 0.4,
				    0.7, 0.8, 0.4, 0.4, 0.9, 0.6, 0.5, 0.3, 0.8, 0.2, 0.7, 0.1, 0.5, 0.2, 0.3, 0.3, 0.8, 0.8,
				    0.7, 0.6, 0.6, 0.1, 0.5, 0.3, 0.2, 0.3, 0.2, 0.7, 0.1, 0.3, 0.6, 0.2, 0.9, 0.5, 0.3, 0.7,
				    0.4, 0.9, 0.6, 0.1, 0.9, 0.5, 0.2, 0.8, 0.9, 0.1, 0.1, 0.4, 0.5, 0.6, 0.9, 0.1, 0.2, 0.4,
				    0.6, 0.2, 0.7, 0.5, 0.7, 0.7, 0.1, 0.5, 0.8 };

	double y[] = { 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
				   0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0,
				   0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
				   0, 0, 0, 0, 0, 0, 1, 0, 0 };

	// Initialize weight and bias of layer 1
	float W1[2][2] = {{1, 1}, 
					 {1, 1}};
	float B1[2][1] = {{ 1 }, 
					 { 1 }};

	// Initialize weight and bias of layer 2
	float W2[] = { 1, 1 };
	float B2 = 1;

	float L = 0;
	float J = 0;
	float learning_rate = 0.01;
	int num_epochs = 50;

	float S1[] = { 0, 0 };
	float A1[] = { 0, 0 };
	float S2 = 0;
	float A2 = 0;
	float y_hat = 0;

	for (int i = 0; i < num_epochs; i++) {
		J = 0;
		for (int xi = 0; xi < 81; xi++) {
			// Feed forward
			S1[0] = B1[1][1] + x1[xi] * W1[1][1] + x2[xi] * W1[2][1];
			S1[1] = B1[2][1] + x1[xi] * W1[1][2] + x2[xi] * W1[2][2];
			A1[0] = sigmoid(S1[0]);
			A1[1] = sigmoid(S1[1]);

			S2 = B2 + A1[0] * W2[0] + A1[1] * W2[1];
			A2 = sigmoid(S2);

			y_hat = A2;

			// Back propagation
			B2 = B2 - learning_rate * (y_hat - y[xi]);
			W2[0] = W2[0] - learning_rate * A1[0] * (y_hat - y[xi]);
			W2[1] = W2[1] - learning_rate * A1[1] * (y_hat - y[xi]);

			B1[1][1] = B1[1][1] - learning_rate * W2[0] * sigmoid_derivative(A1[0]) * (y_hat - y[xi]);
			B1[2][1] = B1[2][1] - learning_rate * W2[1] * sigmoid_derivative(A1[1]) * (y_hat - y[xi]);

			W1[1][1] = W1[1][1] - learning_rate * W2[0] * sigmoid_derivative(A1[0]) * x1[xi] * (y_hat - y[i]);
			W1[1][2] = W1[1][2] - learning_rate * W2[1] * sigmoid_derivative(A1[1]) * x1[xi] * (y_hat - y[i]);
			W1[2][1] = W1[2][1] - learning_rate * W2[0] * sigmoid_derivative(A1[0]) * x2[xi] * (y_hat - y[i]);
			W1[2][2] = W1[2][2] - learning_rate * W2[1] * sigmoid_derivative(A1[1]) * x2[xi] * (y_hat - y[i]);

			// Loss function
			L = -(y[xi] * log10(y_hat) + (1 - y[xi])*log10(1 - y_hat));
			
			J += L;
		}
		
		cout << "epoch " << i + 1 << ": Error = " << J << endl;
	}
	return 0;
}
