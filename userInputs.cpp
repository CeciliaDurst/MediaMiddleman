#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main () {

	string title, runtime, releaseYear, genre;

	cout << "The MediaMiddleMan\n-------------------------------------\nSelect your preferences or type None" <<endl;
	cout << "Title: ";
	cin >> title;

	cout << "Run Time: ";
	cin >> runtime;

	cout << "Release Year: ";
	cin >> releaseYear;
	
	cout << "Genre: ";
	cin >> genre;

	vector<string> userInputs = {title, runtime, releaseYear, genre};

	return 0;

}
