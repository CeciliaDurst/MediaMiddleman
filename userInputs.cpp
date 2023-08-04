#include <iostream>
#include <string>
#include <vector>
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

int main () {

    string format, title, strStartYear, strEndYear, strRuntime, strGenre;
    int startYear = 0, endYear = 0, runtime = 0;
    vector<string> genres = {};

    // asking user for inputs
	cout << "The MediaMiddleMan\n-------------------------------------\nSelect your preferences or type None" <<endl;

    cout << "Format: ";
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

	return 0;

}
