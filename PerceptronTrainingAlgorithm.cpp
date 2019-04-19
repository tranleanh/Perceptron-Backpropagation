#include <iostream>
#include <math.h>
using namespace std;

int main() {

	double w1, w2, S, bias;
	double updated_w1, updated_w2;
	int x1[] = { 0, 1, 0, 1 };
	int x2[] = { 0, 0, 1, 1 };
	int y[4] = { 0 };

	// Target: AND-Gate
	int t[] = { 0, 0, 0, 1 };

	// Number of epoch
	int epoch = 20;

	// Initialization
	w1 = 0.2;
	w2 = 0.8;
	bias = 0.45;

	for (int j = 0; j < epoch; j++) {
		cout << "epoch " << j + 1 << endl;
		cout << " x1 | x2 |  w1  |  w2  |  S   | y | t\n" << endl;

		// Training for each epoch
		for (int i = 0; i < 4; i++) {
			S = w1 * x1[i] + w2 * x2[i];
			
			// Activation function
			if (S > bias) {
				y[i] = 1;
			}
			else {
				y[i] = 0;
			}

			// Updating weights
			if (y[i] < t[i]) {
				updated_w1 = w1 + x1[i] * 0.5 * w1;
				updated_w2 = w2 + x2[i] * 0.5 * w2;
			}
			else if (y[i] > t[i]) {
				updated_w1 = w1 - x1[i] * 0.5 * w1;
				updated_w2 = w2 - x2[i] * 0.5 * w2;
			}
			else {
				updated_w1 = w1;
				updated_w2 = w2;
			}

			printf(" %d  | %d  | %.2f | %.2f | %.2f | %d | %d\n", x1[i], x2[i], w1, w2, S, y[i], t[i]);

			w1 = updated_w1;
			w2 = updated_w2;
		}

		// Check if output is equal to target, yes: quit training
		if (equal(begin(y), end(y), begin(t))) {
		 	cout << "\nTrained Weights: w1 = " << w1 <<"; w2 = " << w2 << endl;
		 	cout << "\nComplete Training!\n";
		 	break;
		}
	}

	return 0;
}