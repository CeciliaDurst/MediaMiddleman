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
    int index = 0;
    while(genreStream.size() != 0){
        index = genreStream.find_first_of(',');

    }
}





int main (){
    string test = "Horror, Adventure, Comedy";
    int index = test.find_first_not_of(',');
    cout << test.substr(0,index) << endl;    
    return 0;
}

//HEY