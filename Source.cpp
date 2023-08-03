#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Content {
private:
	string format;
	string title;
	int startYear;
	int endYear;
	int runTimeMins;
	vector<string> genres;
public:
	Content();
	Content(string f, string t, int sY, int eY, int rTM);
	string getFormat();
	string getTitle();
	int getStartYear();
	int getEndYear();
	int getRunTimeMins();

};

Content::Content() {
	format = "";
	title = "";
	startYear = 0;
	endYear = 0;
	runTimeMins = 0;
	genres = {};
}

Content::Content(string f, string t, int sY, int eY, int rTM) {
	format = f;
	title = t;
	startYear = sY;
	endYear = eY;
	runTimeMins = rTM;
	genres = {};
}

string Content::getFormat() {
	return format;
}
string Content::getTitle() {
	return title;
}
int Content::getStartYear() {
	return startYear;
}
int Content::getEndYear() {
	return endYear;

}

int Content::getRunTimeMins() {
	return runTimeMins;
}


// first input is unordered map containing <key, Content list of information on the movie at this key (for testing im using 4 search requests Ex. format, title, release year, runtime
// second input is a Content list of user inputs
// returns a list of keys that match the search requests
vector<string> mapFilter(unordered_map<string, Content> allContent, Content userInputs) {

	Content currList;
	vector<string> correctKeys;

	for (auto& i : allContent) { // i loops through every key of allContent

		currList = i.second;	
		
		// checking if it matches user inputs
		if ((currList.getFormat() == userInputs.getFormat() || userInputs.getFormat() == "None") && (currList.getTitle() == userInputs.getTitle() || userInputs.getTitle() == "None") && (currList.getStartYear() == userInputs.getStartYear() || userInputs.getStartYear() == -1) && (currList.getEndYear() == userInputs.getEndYear() || userInputs.getEndYear() == -1) && (currList.getRunTimeMins() == userInputs.getRunTimeMins() || userInputs.getRunTimeMins() == -1)) {

			correctKeys.push_back(i.first);

		}

	}

	if (correctKeys.empty()) { // case no search results found

		cout << "No results found." << endl;

	}

	return correctKeys;

}

int main() { // main for testing inputs and outputs

	Content userInputs;
	userInputs = Content("correct", "correct", 0, 0, 0);

	Content content;
	content = Content("correct", "correct", 0, 0, 0);
	
	unordered_map<string, Content> allContent;
	allContent["abcd"] = content;

	content = Content("wrong", "correct", 0, 0, 0);
	allContent["efgh"] = content;
	content = Content("correct", "wonrg", 0, 0, 0);
	allContent["igjk"] = content;
	content = Content("correct", "correct", 0, 0, 0);
	allContent["lmno"] = content;	

	vector<string> correctKeys = mapFilter(allContent, userInputs);

	for (auto const& i : correctKeys) {

		cout << i << endl;

	}

	return 0;

}
