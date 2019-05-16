#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int main() {

	double w0, w1, w2, bias, S, y, E;
	double error, learning_rate;
	double updated_w0, updated_w1, updated_w2;

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

	double t[] = { 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
				0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0,
				0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
				0, 0, 0, 0, 0, 0, 1, 0, 0 };

	// Number of epoch
	int epoch = 250;

	// Initialization
	w0 = 0;
	w1 = 0;
	w2 = 0;
	learning_rate = 0.3;

	ofstream myfile("Error_per_epoch.txt");

	for (int j = 0; j < epoch; j++) {
		cout << "epoch " << j + 1 << endl;
		E = 0;

		// Training for each epoch
		for (int i = 0; i < 81; i++) {
			S = w0 + w1 * x1[i] + w2 * x2[i];

			// Activation function: Sigmoid
			y = 1 / (1 + exp(-S));

			error = t[i] - y;

			// Updating weights
			updated_w0 = w0 + learning_rate * error;
			updated_w1 = w1 + x1[i] * learning_rate * error;
			updated_w2 = w2 + x2[i] * learning_rate * error;

			w0 = updated_w0;
			w1 = updated_w1;
			w2 = updated_w2;

			E = E + 0.5 * abs(error);
		}

		printf(" %.5f \n", E);

		if (myfile.is_open()) {
			myfile << E << endl;
		}
	}

	myfile.close();

	return 0;
}
