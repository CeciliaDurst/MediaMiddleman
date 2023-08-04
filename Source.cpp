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
	void setGenres(string genreStream);
	string getFormat();
	string getTitle();
	int getStartYear();
	int getEndYear();
	int getRunTimeMins();
	vector<string> getGenres();

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

void Content::setGenres(string genreStream) {
	int index = genreStream.find_first_of(',');
	//genres.push_back(genreStream);

	while (index != -1) {
		genres.push_back(genreStream.substr(0, index));
		genreStream = genreStream.substr(index + 1);
		index = genreStream.find_first_of(',');
	}

	genres.push_back(genreStream);

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

vector<string> Content::getGenres() {
	return genres;
}

// first input is unordered map containing <key, Content list of information on the movie at this key>
// second input is a Content list of user inputs
// returns a list of keys that match the search requests
vector<string> mapFilter(unordered_map<string, Content> allContent, Content userInputs) {

	int temp = 0;
	Content currList;
	vector<string> correctKeys, currGenre, currInput = userInputs.getGenres();

	for (auto& i : allContent) { // i loops through every key of allContent

		currList = i.second; // looking at Content at this key
		currGenre = currList.getGenres(); // geting the vector of Genres for this key

		// checking if the movie matches user inputs or is null
		if ((currList.getFormat() == userInputs.getFormat() || userInputs.getFormat() == "None") && (currList.getTitle() == userInputs.getTitle() || userInputs.getTitle() == "None") && (currList.getStartYear() == userInputs.getStartYear() || userInputs.getStartYear() == -1) && (currList.getEndYear() == userInputs.getEndYear() || userInputs.getEndYear() == -1) && (currList.getRunTimeMins() == userInputs.getRunTimeMins() || userInputs.getRunTimeMins() == -1)) {

			if (currInput[0] == "None") { // null

				correctKeys.push_back(i.first); // inserting key into the output list

			}			
			else {

				for (int j = 0; j < currGenre.size(); j++) {  // looping through genres of this movie

					temp = 0;

					for (int k = 0; k < currInput.size(); k++) { // looping through genres of the search request

						temp = k;
						
						if (currGenre[j] == currInput[k]) { // breaking if one matches

							correctKeys.push_back(i.first); // inserting key into the output list
							break;

						}				

					}

					if (currGenre[j] == currInput[temp]) { // breaking if one matches

						break;

					}

				}

			}

		}

	}

	if (correctKeys.empty()) { // case no search results found

		cout << "No results found." << endl;

	}

	return correctKeys; // return list of keys that match the search results

}

int main() { // main for testing inputs and outputs

	Content userInputs;
	userInputs = Content("correct", "correct", 0, 0, 0);
	userInputs.setGenres("correct,correct");
	
	Content content;	
	unordered_map<string, Content> allContent;

	content = Content("correct", "correct", 0, 0, 0);
	content.setGenres("correct,correct");
	allContent["abcd"] = content;

	content = Content("wrong", "correct", 0, 0, 0);
	content.setGenres("wrong,correct");
	allContent["efgh"] = content;

	content = Content("correct", "wonrg", 0, 0, 0);
	content.setGenres("wrong,wrong");
	allContent["igjk"] = content;

	content = Content("correct", "correct", 0, 0, 0);
	content.setGenres("wrong,correct");
	allContent["lmno"] = content;

	content = Content("correct", "correct", 0, 0, 0);
	content.setGenres("wrong,wrong");
	allContent["pqrs"] = content;

	vector<string> correctKeys = mapFilter(allContent, userInputs);

	for (auto const& i : correctKeys) {

		cout << i << endl;

	}

	return 0;

}
