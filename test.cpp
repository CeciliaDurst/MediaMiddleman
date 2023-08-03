#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
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

int main (){
    unordered_map<string, Content> test = ReadTitleBasics("title_basics2.tsv");
    cout << test["tt0000002"].getTitle() << endl;
    cout << test.size() << endl;
    for(auto i : test){
        cout << i.first << endl;
    }
    return -1;
}




