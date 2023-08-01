#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
using namespace std;

// first input is unordered map containing <key, list of information on the movie at this key (for testing im using 4 search requests Ex. format, title, release year, runtime
// second input is a list of user inputs
// returns a list of keys that match the search requests
list<string> mapFilter(unordered_map<string, list<string>> allContent, list<string> userInputs) {

	list<string> currList;	
	list<string> correctKeys;
	int count;

	for (auto& i : allContent) { // i loops through every key of allContent

		count = 0;
		currList = i.second;
		for (auto const& j : currList) { // j loops through the list of the current key

			count++;
			for (auto const& n : userInputs) { // n loops through every user search request

				if (j != n) { // incorrect search request

					break;

				}
				else if (count == 4) { // making sure we checked every preference. For testing I used 4 preferences

					correctKeys.push_back(i.first); // adding key to list of correct keys
					break;

				}

			}		

		}

	}

	return correctKeys;

}

int main() {

	list<string> userInputs = {"correct", "correct", "correct", "correct"};
	unordered_map<string, list<string>> allContent;
	list<string> tempList = {"correct", "correct", "correct", "correct"};
	allContent["abcd"] = tempList;
	tempList = {"wrong", "wrong", "wrong", "wrong"};
	allContent["efgh"] = tempList;
	allContent["hijk"] = tempList;	

	list<string> correctKeys = mapFilter(allContent, userInputs);

	for (auto const& i : correctKeys) {

		cout << i << endl;

	}

	return 0;

}