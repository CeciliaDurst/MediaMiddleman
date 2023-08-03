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

int main () {

    string format, title, strStartYear, strEndYear, strRuntime;
    int startYear = 0, endYear = 0, runtime = 0;

	cout << "The MediaMiddleMan\n-------------------------------------\nSelect your preferences or type None" <<endl;

    cout << "Format: ";
    cin >> format;

	cout << "Title: ";
	cin >> title;

    cout << "Release Year: ";
    cin >> strStartYear;

    if (strStartYear == "None") {

        startYear == -1;

    }
    else {

        startYear = stoi(strStartYear);

    }

    cout << "End Year of Series: ";
    cin >> strEndYear;

    if (strEndYear == "None") {

        endYear == -1;

    }
    else {

        endYear = stoi(strEndYear);

    }

    cout << "Run Time in Minutes: ";
    cin >> strRuntime;

    if (strRuntime == "None") {

        runtime == -1;

    }
    else {

        runtime = stoi(strRuntime);

    }

    Content userInputs;
	userInputs = Content(format, title, startYear, endYear, runtime);

	return 0;

}
