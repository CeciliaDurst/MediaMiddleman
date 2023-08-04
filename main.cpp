#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <queue>
using namespace std;

// Content class
class Content{
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
        string RunTimeMins_to_Hours_and_Mins();
        void outputDetails();
        
};

Content::Content(){
    format = "";
    title = "";
    startYear = 0;
    endYear = 0;
    runTimeMins = 0;
    genres = {};
}

Content::Content(string f, string t, int sY, int eY, int rTM){
    format = f;
    title = t;
    startYear = sY;
    endYear = eY;
    runTimeMins = rTM;
    genres = {};
}

void Content::setGenres(string genreStream){
    int index = genreStream.find_first_of(',');
    //genres.push_back(genreStream);

    while(index != -1){
        genres.push_back(genreStream.substr(0,index));
        genreStream = genreStream.substr(index+1);
        index = genreStream.find_first_of(',');
    }

    genres.push_back(genreStream);
    
}
string Content::getFormat(){
    return format;
}
string Content::getTitle(){
    return title;
}
int Content::getStartYear(){
    return startYear;
}
int Content::getEndYear(){
    return endYear;

}

int Content::getRunTimeMins(){
    return runTimeMins;
}

vector<string> Content::getGenres(){
    return genres;
}

string Content::RunTimeMins_to_Hours_and_Mins(){
    string result = "";
    if(runTimeMins < 60){
        
        result += to_string(runTimeMins) + " minute";
        if(runTimeMins > 1){
            result += "s";
        }

        return result;
    }

    int mins = runTimeMins % 60;
    int hours = runTimeMins / 60;

    if(mins == 0){
        result += to_string(hours) + "hour";
        if(hours > 1){
            result += "s";
        }
        return result;
    }

    result += to_string(hours) + "hour";
    if(hours > 1){
        result += "s";
    }

    result += " and " + to_string(mins) + "minute";
    if(mins > 1){
        result += "s";
    }

    return result;

}

 void Content::outputDetails(){
    cout << "\""<< title << "\" Information:" << endl;
    cout << "Format: " << format << endl;
    cout << "Release Year: " << startYear << endl;
    if(format == "tvSeries" && endYear != 0){
        cout << "End Year:" << endYear << endl;
    }
    cout << "Run Time: " << RunTimeMins_to_Hours_and_Mins() << endl;
    cout << "Genres: ";
    for(int i = 0; i < genres.size(); i++){
        cout << genres[i];
        if(i !=genres.size()-1){
            cout << ",";
        }
    }
 }

 
unordered_map<string, Content> ReadTitleBasics(string filename){
    string line = "";
    unordered_map<string, Content> allContents;
    fstream myfile(filename);
    
    if(myfile.is_open()){
        getline(myfile,line);
        //getline(myfile,line);
        int index = line.find_first_of("\t");
        vector<string> vals;

        // while(index != -1){
        //     vals.push_back(line.substr(0,index));
        //     line = line.substr(index+1);
        //     index = line.find_first_of("\t");
        // }

        // vals.push_back(line);

        // for(int i = 0; i < vals.size(); i++){
        //     cout << vals[i] << endl;
        // }

        // cout << vals.size() << endl;
        // int test = stoi(vals[8]);
        // cout << test << endl;
        while(getline(myfile,line)){
            
            int index = line.find_first_of("\t");
            while(index != -1){
                if(line.substr(0,index) == "\\N"){
                    vals.push_back("0");
                }

                else{
                    vals.push_back(line.substr(0,index));
                }
                
                line = line.substr(index+1);
                index = line.find_first_of("\t");
            }
            vals.push_back(line);
            
        
            //only make Content object if the content is not adult
            if(vals[4] == "0"){
                Content obj;
                
                obj = Content(vals[1], vals[2], stoi(vals[5]), stoi(vals[6]), stoi(vals[7]));

                obj.setGenres(vals[8]);
                allContents [vals[0]] = obj; 

                

                
                
            }

            vals.clear();
            
        }

        // for(int i = 0; i < 2; i++){
        //     getline(myfile,line);
        //     int index = line.find_first_of("\t");
        //     while(index != -1){
        //         if(line.substr(0,index) == "\\N"){
        //             vals.push_back("0");
        //         }

        //         else{
        //             vals.push_back(line.substr(0,index));
        //         }
                
        //         line = line.substr(index+1);
        //         index = line.find_first_of("\t");
        //     }
        //     vals.push_back(line);
            
        
        //     //only make Content object if the content is not adult
        //     if(vals[4] == "0"){
        //         Content obj;
                
        //         obj = Content(vals[1], vals[2], stoi(vals[5]), stoi(vals[6]), stoi(vals[7]));

        //         obj.setGenres(vals[8]);
        //         allContents [vals[0]] = obj; 

                

                
                
        //     }

        //     vals.clear();
        // }
    }

    else{
        cout << "Title Basics File is Not Opening" << endl;
    }

    return allContents;

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

		cout << "No results found." << endl;

	}

	return correctKeys; // return list of keys that match the search results

}

// Sorting

// Merge sort
vector<int> mergeSort(vector <int> content, int start, int end) {

    // Make and populate new vector endSort from subsection of given vector
    vector <int> endSort;
    for(int i = start; i < end; i++){
        endSort.push_back(content[i]);
    }

    // Find current split point of original vector
    int midpoint = (end - start) / 2 + start;

    // If provided list is too small to be halved, return endSort
    if(midpoint == 0 || endSort.size() == 1){
        return endSort;
    }

    // Recursively halve list
    vector <int> firstHalf = mergeSort(content, start, midpoint);
    vector <int> secondHalf = mergeSort(content, midpoint, end);

    //Compare halves' contents and merge
    int index = 0;
    int firstIndex = 0;
    int secondIndex = 0;

    while(firstIndex < (int)firstHalf.size() || secondIndex < (int)secondHalf.size()){
        if(firstHalf[firstIndex] > secondHalf[secondIndex] || secondIndex >= (int)secondHalf.size()){
            endSort[index ++] = firstHalf[firstIndex ++];
        }
        else{
            endSort[index ++] = secondHalf[secondIndex ++];
        }
    }

    return endSort;
}

// K Largest
vector<int> kSort(vector<int> content, int k){
    // Make a min priority queue to hold all given ints
    priority_queue<int, vector<int>, greater<int> > sorter;
    vector<int> endSort;

    // Iterate through the given vector, filling the priority queue up to k elements
    for(int i = 0; i < k; i++){
        sorter.push(content[i]);
    }

    // For the remaining elements, if an int is larger than the top of the queue,
    // pop the smallest element from the priority queue and add that int
    for(int i = k; i < content.size(); i++){
        if(sorter.top() < content[i]){
            sorter.pop();
            sorter.push(content[i]);
        }
    }

    // Add priority queue elements to a vector and return it
    for(int i = 0; i < k; i++){
        endSort.push_back(sorter.top());
        sorter.pop();
    }

    return endSort;
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




    // Timers and outputs
    
    // (Chrono clock objects and manipulation sourced from GeeksforGeeks 
    // https://www.geeksforgeeks.org/measure-execution-time-function-cpp/)

    // Get start and end timepoints and then subtract them to find duration of functions
    auto start1 = std::chrono::high_resolution_clock::now();
    vector<int> tester = mergeSort(values, 0, values.size());
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = duration_cast<std::chrono::microseconds>(stop1 - start1);


    for(int i = 0; i < 5; i++){
        cout << tester[i] << endl;
    }

    // K Largest Test
    cout << "\nK largest" << endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    vector<int> tester2 = kSort(values, 5);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    for(int i = 4; i > -1; i--){
        cout << tester2[i] << endl;
    }

    cout << "\nTime taken by Merge: " << duration1.count() << " microseconds" << endl;
    cout << "Time taken by K Largest: " << duration2.count() << " microseconds" << endl;





	return 0;

}
