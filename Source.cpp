#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// first input is unordered map containing <key, vector of information on the movie at this key (for testing im using 4 search requests Ex. format, title, release year, runtime
// second input is a vector of user inputs
// returns a list of keys that match the search requests
vector<string> mapFilter(unordered_map<string, vector<string>> allContent, vector<string> userInputs) {

	vector<string> currList;
	vector<string> correctKeys;
	int count;

	for (auto& i : allContent) { // i loops through every key of allContent

		count = 0;
		currList = i.second;
		for (auto const& j : currList) { // j loops through the vector of the current key

			for (auto const& n : userInputs) { // n loops through every user search request

				if (j != n || n == "None") { // incorrect search request

					break;

				}
				else if (count == 3) { // making sure we checked every preference. For testing I used 4 preferences

					correctKeys.push_back(i.first); // adding key to vector of correct keys
					break;

				}

			}

			count++;

		}

	}

	return correctKeys;

}

int main() { // main for testing inputs and outputs

	vector<string> userInputs = {"correct", "correct", "correct", "correct"};
	unordered_map<string, vector<string>> allContent;
	vector<string> tempList = {"correct", "correct", "correct", "correct"};
	allContent["abcd"] = tempList;
	tempList = {"wrong", "wrong", "wrong", "wrong"};
	allContent["efgh"] = tempList;
	allContent["hijk"] = tempList;
	tempList = { "correct", "correct", "correct", "correct" };
	allContent["lmno"] = tempList;

	vector<string> correctKeys = mapFilter(allContent, userInputs);

	for (auto const& i : correctKeys) {

		cout << i << endl;

	}

	return 0;

}
