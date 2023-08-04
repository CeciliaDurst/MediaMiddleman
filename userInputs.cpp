#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <queue>
using namespace std;

// Content class
class Content {
private:
    string format;
    string title;
    int startYear;
    int endYear;
    int runTimeMins;
    vector<string> genres;
    float rating;
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
    string RunTimeMins_to_Hours_and_Mins();
    void outputDetails();
    float getRating();
    void setRating(float f);

};

//default constructor
Content::Content() {
    format = "";
    title = "";
    startYear = 0;
    endYear = 0;
    runTimeMins = 0;
    genres = {};
}

//constructor that makes Content objects from the stream
Content::Content(string f, string t, int sY, int eY, int rTM) {
    format = f;
    title = t;
    startYear = sY;
    endYear = eY;
    runTimeMins = rTM;
    genres = {};
}

//sets the genres of the piece of content
//accepts a stream of genres in csv form from the tsv file
//divides them and then adds them to the genre vector
//genres are strings
void Content::setGenres(string genreStream) {
    int index = genreStream.find_first_of(',');

    while (index != -1) {
        genres.push_back(genreStream.substr(0, index));
        genreStream = genreStream.substr(index + 1);
        index = genreStream.find_first_of(',');
    }

    genres.push_back(genreStream);

}
//getter methods
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

// Filtering

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

        cout << "\nNo results found\nSearch Again" << endl;

    }

    return correctKeys; // return list of keys that match the search results

}

int main () {

    string format, title, strStartYear, strEndYear, strRuntime, strGenre;
    int startYear = 0, endYear = 0, runtime = 0;
    vector<string> genres = {};
    vector<string> correctKeys = {};

    // asking user for inputs
	cout << "The MediaMiddleMan\n-------------------------------------\nSelect your preferences or type None" <<endl;

    while (correctKeys.empty()) {

        cout << "\nFormat: ";
        cin >> format;

        cout << "Title: ";
        cin >> title;

        cout << "Release Year: ";
        cin >> strStartYear;

        if (strStartYear == "None") { // switching to int

            startYear == -1;

        }
        else {

            startYear = stoi(strStartYear);

        }

        cout << "End Year of Series: ";
        cin >> strEndYear;

        if (strEndYear == "None") { // switching to int

            endYear == -1;

        }
        else {

            endYear = stoi(strEndYear);

        }

        cout << "Run Time in Minutes: ";
        cin >> strRuntime;

        if (strRuntime == "None") { // switching to int

            runtime == -1;

        }
        else {

            runtime = stoi(strRuntime);

        }

        cout << "Genre(s) with commas in between: ";
        cin >> strGenre;

        // setting user inputs in a Content List
        Content userInputs;
        userInputs = Content(format, title, startYear, endYear, runtime);
        userInputs.setGenres(strGenre);
        unordered_map<string, Content> allContent;
        allContent["abcd"] = Content(format, title, startYear, endYear, runtime);
        correctKeys = mapFilter(allContent, userInputs);

    }

	return 0;

}
