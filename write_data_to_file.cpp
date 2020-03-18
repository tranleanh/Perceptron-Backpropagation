// writing on a text file
#include <iostream>
#include <fstream>
using namespace std;

// create an empty file: example.txt

int main () {
  ofstream myfile ("example.txt");
  if (myfile.is_open())
  {
	myfile << "This is a line.\n";
	myfile << "This is another line.\n";
	myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}