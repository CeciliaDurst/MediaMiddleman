#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <queue>
#include <algorithm>
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

// default constructor
Content::Content() {
    format = "";
    title = "";
    startYear = 0;
    endYear = 0;
    runTimeMins = 0;
    //genres = {};
}

// constructor that makes Content objects from the stream
Content::Content(string f, string t, int sY, int eY, int rTM) {
    format = f;
    title = t;
    startYear = sY;
    endYear = eY;
    runTimeMins = rTM;
    //genres = {};
}

// sets the genres of the piece of content
// accepts a stream of genres in csv form from the tsv file
// divides them and then adds them to the genre vector
// genres are strings
void Content::setGenres(string genreStream) {
    int index = genreStream.find_first_of(',');

    while (index != -1) {
        genres.push_back(genreStream.substr(0, index));
        genreStream = genreStream.substr(index + 1);
        index = genreStream.find_first_of(',');
    }

    genres.push_back(genreStream);

}
// getter methods
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

// converts the minute runTime of a piece of content to a more conventional
// hour + minute form
// includes edge cases
// returns a string so it can be outpuuted in the Content output function
string Content::RunTimeMins_to_Hours_and_Mins() {
    string result = "";
    if (runTimeMins < 60) {

        result += to_string(runTimeMins) + " minute";
        if (runTimeMins > 1) {
            result += "s";
        }

        return result;
    }

    int mins = runTimeMins % 60;
    int hours = runTimeMins / 60;

    if (mins == 0) {
        result += to_string(hours) + "hour";
        if (hours > 1) {
            result += "s";
        }
        return result;
    }

    result += to_string(hours) + "hour";
    if (hours > 1) {
        result += "s";
    }

    result += " and " + to_string(mins) + "minute";
    if (mins > 1) {
        result += "s";
    }

    return result;

}

// outputs the details of apiece of Content
// will probably be called to output the piece of Content
// that matches the user's qualifications
void Content::outputDetails() {
    cout << "\"" << title << "\" Information:" << endl;
    cout << "Format: " << format << endl;
    cout << "Release Year: " << startYear << endl;
    if (format == "tvSeries" && endYear != 0) {
        cout << "End Year:" << endYear << endl;
    }
    cout << "Run Time: " << RunTimeMins_to_Hours_and_Mins() << endl;
    cout << "Genres: ";
    for (int i = 0; i < genres.size(); i++) {
        cout << genres[i];
        if (i != genres.size() - 1) {
            cout << ",";
        }
    }
}

float Content::getRating() {
    return rating;
}
void Content::setRating(float f) {
    rating = f;
}

// reads in data from a tsv file and constructs/returns a map 
// containing each piece of Content, with a unique identifier as the key
unordered_map<string, Content> ReadTitleBasics(string filename) {
    string line = "";
    unordered_map<string, Content> allContents;
    fstream myfile(filename);

    // open file
    if (myfile.is_open()) {
        getline(myfile, line); // read past first line

        // temporary vector to store each tab separated value as an element
        vector<string> vals;

        // for each line
        while (getline(myfile, line)) {

            // read in each tab-sparated value into vals
            int index = line.find_first_of("\t");
            while (index != -1) {
                // if the value is null, store it as 0
                if (line.substr(0, index) == "\\N") {
                    vals.push_back("0");
                }

                else {
                    vals.push_back(line.substr(0, index));
                }

                line = line.substr(index + 1);
                index = line.find_first_of("\t");
            }
            vals.push_back(line);

            /* Note ! Form of the vector is this:
                vals[0] == unique key
                vals[1] == format
                vals[2] == primaryTitle
                vals[3] ==  originalTitle
                vals[4] == isAdult
                vals[5] == startYear
                vals[6] == endYear
                vals[7] == runtimeMinutes
                vals[8] == csv stream of genres
            */
            // only make Content object if the content is not adult
            if (vals[4] == "0") {


                Content obj = Content(vals[1], vals[2], stoi(vals[5]), stoi(vals[6]), stoi(vals[7]));

                obj.setGenres(vals[8]);
                allContents[vals[0]] = obj;





            }

            vals.clear();

        }

    }

    else {
        cout << "Title Basics File is Not Opening" << endl;
    }

    return allContents;

}

// opens the title_ratings file and assigns the respective ratings to the Content objects in the map
// with the correct identifier
void setRatings(string filename, unordered_map<string, Content>& allContents) {
    string line = "";
    int index = 0;
    string key = "";
    float rating = 0.0f;
    fstream myfile(filename);
    if (myfile.is_open()) {
        getline(myfile, line);
        while (getline(myfile, line)) {
            index = line.find_first_of("\t");
            key = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find_first_of("\t");
            rating = stof(line.substr(0, index));

            if (allContents.count(key) != 0) {
                allContents[key].setRating(rating);
            }

            else {
                cout << "Cannot find " << key << " in the Contents Map" << endl;
            }


        }
    }

    else {
        cout << "Ratings File is not open" << endl;
    }

}


// Filtering

// first input is unordered map containing <key, Content list of information on the movie at this key>
// second input is a Content list of user inputs
// returns a list of keys that match the search requests
vector<pair<string, float> > mapFilter(unordered_map<string, Content> allContent, Content userInputs) {

    int temp = 0;
    Content currList;
    vector<pair<string, float> > correctKeys;
    vector<string> currGenre, currInput = userInputs.getGenres();

    for (auto& i : allContent) { // i loops through every key of allContent

        currList = i.second; // looking at Content at this key
        currGenre = currList.getGenres(); // geting the vector of Genres for this key

        // checking if the movie matches user inputs or is null
        if ((currList.getFormat() == userInputs.getFormat() || userInputs.getFormat() == "None") && (currList.getTitle() == userInputs.getTitle() || userInputs.getTitle() == "None") && (currList.getStartYear() == userInputs.getStartYear() || userInputs.getStartYear() == 0) && (currList.getEndYear() == userInputs.getEndYear() || userInputs.getEndYear() == 0) && (currList.getRunTimeMins() == userInputs.getRunTimeMins() || userInputs.getRunTimeMins() == 0)) {

            if (currInput[0] == "None") { // null

                correctKeys.push_back(make_pair(i.first, i.second.getRating())); // inserting key into the output list

            }
            else {

                for (int j = 0; j < currGenre.size(); j++) {  // looping through genres of this movie

                    temp = 0;

                    for (int k = 0; k < currInput.size(); k++) { // looping through genres of the search request

                        temp = k;

                        if (currGenre[j] == currInput[k]) { // breaking if one matches

                            correctKeys.push_back(make_pair(i.first, i.second.getRating())); // inserting key into the output list
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

// Sorting

// Merge sort
vector<pair<string, float> > mergeSort(unordered_map <string, Content> allContents, vector <pair<string, float> > content, int start, int end) {

    // Make and populate new vector endSort from subsection of given vector
    vector <pair<string, float> > endSort;
    for (int i = start; i < end; i++) {
        endSort.push_back(content[i]);
    }

    // Find current split point of original vector
    int midpoint = (end - start) / 2 + start;

    // If provided list is too small to be halved, return endSort
    if (midpoint == 0 || endSort.size() == 1) {
        return endSort;
    }

    // Recursively halve list
    vector <pair<string, float> > firstHalf = mergeSort(allContents, content, start, midpoint);
    vector <pair<string, float> > secondHalf = mergeSort(allContents, content, midpoint, end);

    //Compare halves' contents and merge
    int index = 0;
    int firstIndex = 0;
    int secondIndex = 0;

    while (firstIndex < (int)firstHalf.size() && secondIndex < (int)secondHalf.size()) {
        if (firstHalf[firstIndex].second > secondHalf[secondIndex].second) {
            endSort[index++] = firstHalf[firstIndex++];
        }
        else {
            endSort[index++] = secondHalf[secondIndex++];
        }
    }

    while (firstIndex < (int)firstHalf.size()) {

        endSort[index++] = firstHalf[firstIndex++];

    }

    while (secondIndex < (int)secondHalf.size()) {

        endSort[index++] = secondHalf[secondIndex++];

    }

    return endSort;
}

// K Largest

// Min Rating sets the logic for a priority queue of content titles and ratings
struct minRating {
    constexpr bool operator()(
        pair<string, float> const& a,
        pair<string, float> const& b)
        const noexcept {
        return a.second > b.second;
    }
};
vector<pair<string, float> > kSort(vector <pair<string, float> > content, int k) {
    // Make a min priority queue to hold all given ints
    priority_queue<pair<string, float>, vector<pair<string, float> >, minRating> sorter;
    vector<pair<string, float> > endSort;

    // Iterate through the given vector, filling the priority queue up to k elements
    for (int i = 0; i < k; i++) {
        sorter.push(make_pair(content[i].first, content[i].second));
    }

    // For the remaining elements, if an int is larger than the top of the queue,
    // pop the smallest element from the priority queue and add that int
    for (int i = k; i < content.size(); i++) {
        if (sorter.top().second < content[i].second) {
            sorter.pop();
            sorter.push(make_pair(content[i].first, content[i].second));
        }
    }

    // Add priority queue elements to a vector and return it
    for (int i = 0; i < k; i++) {
        endSort.push_back(make_pair(sorter.top().first, sorter.top().second));
        sorter.pop();
    }

    reverse(endSort.begin(), endSort.end());

    return endSort;
}


int main() { // user inputs and method calling

    string sortType, format, title, strStartYear, strEndYear, strRuntime, strGenre;
    int startYear = 0, endYear = 0, runtime = 0, isValid = 0;
    vector<string> genres;
    vector<pair<string, float> > correctKeys;


    // opening file
    unordered_map<string, Content> allContent = ReadTitleBasics("/Users/Cecilia1/Documents/GitHub/MediaMiddleman/title_basics2.tsv");
    setRatings("/Users/Cecilia1/Documents/GitHub/MediaMiddleman/title_ratings.tsv", allContent);

    // asking user for inputs
    cout << "The MediaMiddleMan\n--------------------------------------------------------------------\nWould You like to use Merge Sort or K-Largest Sort? (Type as Shown): ";

    getline(cin, sortType);

    if (sortType != "Merge" && sortType != "K-Largest") { // which sort the user will use

        while (true) {

            if (sortType == "Merge" || sortType == "K-Largest") {

                break;

            }

            cout << "Incorrect Sort Please Type as Shown: ";
            getline(cin, sortType);

        }

    }

    cout << "\nSelect your preferences or type None" << endl;

    while (correctKeys.empty()) { // getting search inputs

        cout << "Format: ";
        getline(cin, format);

        cout << "Title: ";
        getline(cin, title);

        cout << "Release Year: ";
        getline(cin, strStartYear);

        while (true) {

            if (strStartYear == "None") { // switching to int

                startYear == 0;
                break;

            }
            else {

                try {

                    startYear = stoi(strStartYear);
                    break;

                }
                catch (invalid_argument& e) { // case not an int

                    cout << "Invalid: Please Input a Number or None\nRelease Year: ";
                    cin >> strStartYear;

                }

            }

        }

        cout << "End Year of Series: ";
        cin >> strEndYear;

        while (true) {

            if (strEndYear == "None") { // switching to int

                endYear == 0;
                break;

            }
            else {

                try {

                    endYear = stoi(strEndYear);
                    break;

                }
                catch (invalid_argument& e) { // case not an int

                    cout << "Invalid: Please Input a Number or None\nEnd Year of Series: ";
                    cin >> strEndYear;

                }

            }

        }

        cout << "Run Time in Minutes or Number of Seasons: ";
        cin >> strRuntime;

        while (true) {

            if (strRuntime == "None") { // switching to int

                runtime == 0;
                break;

            }
            else {

                try {

                    runtime = stoi(strRuntime);
                    break;

                }
                catch (invalid_argument& e) { // case not an int

                    cout << "Invalid: Please Input a Number or None\nRun Time in Minutes or Number of Seasons: ";
                    cin >> strRuntime;

                }

            }

        }

        cout << "Genre(s) with commas in between: ";
        cin >> strGenre;

        // setting user inputs in a Content List
        Content userInputs;
        userInputs = Content(format, title, startYear, endYear, runtime);
        userInputs.setGenres(strGenre);

        // filtering keys based on search inputs
        correctKeys = mapFilter(allContent, userInputs);

    }

    // sorting

    vector<pair<string, float> > sortedKeys;


    if (sortType == "Merge") { // user wants merge sort

        // (Chrono clock objects and manipulation sourced from GeeksforGeeks
        // https://www.geeksforgeeks.org/measure-execution-time-function-cpp/)

        // Get start and end timepoints and then subtract them to find duration of functions
        auto start = std::chrono::high_resolution_clock::now();
        sortedKeys = mergeSort(allContent, correctKeys, 0, (int)correctKeys.size());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "\nDuration of Merge sort algorithm: " << duration.count() << " microseconds" << endl;

    }
    else { // user wants k-largest sort

        auto start = std::chrono::high_resolution_clock::now();
        sortedKeys = kSort(correctKeys, 5);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "\nDuration of K-Largest sort algorithm: " << duration.count() << " microseconds" << endl;

    }

    // Outputing Results

    cout << "\nTop Search Results" << endl;
    string temp = "";

    if (sortedKeys.size() >= 5) { // Top Five Results 

        for (int i = 0; i < 5; i++) {

            temp = allContent[sortedKeys[i].first].getTitle();
            cout << temp << " " << allContent[sortedKeys[i].first].getRating() << endl;

        }

    }
    else { // case we do not have 5 results that match the search

        for (int i = 0; i < sortedKeys.size(); i++) {

            temp = allContent[sortedKeys[i].first].getTitle();
            cout << temp << " " << allContent[sortedKeys[i].first].getRating() << endl;

        }

    }

}
