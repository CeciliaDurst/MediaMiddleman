#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
        Content(string f, string t, int sY, int eY, int rTM, vector<string> genres);
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

Content::Content(string f, string t, int sY, int eY, int rTM, vector<string> genres){
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

vector<string> Content::getGenres(){
    return genres;
}



int main (){
    string streamTest = "Horror,Adventure,Comedy";
    Content testContent;
    testContent.setGenres(streamTest);
    for(int i = 0; i < testContent.getGenres().size(); i++){
        cout << testContent.getGenres()[i] << endl;
    }

    vector<string> equalTest = {"Horror", "Adventure", "Comedy"};
    bool guh;
    for(int i = 0; i < testContent.getGenres().size(); i++){
        guh = testContent.getGenres()[i] == equalTest[i];
        cout << guh << endl;
    }
    
}

//HEY