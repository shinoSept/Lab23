#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string textline;
    while(getline(source,textline)) {
        const char * text = textline.c_str();
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int a,b,c;
        sscanf(text,format,name,&a,&b,&c);
        int score = a + b + c;
        names.push_back(name);
        scores.push_back(score);
        grades.push_back(score2grade(score));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string input;
    getline(cin, input);
    int spaceIndex = input.find_first_of(" ");
    command = input.substr(0, spaceIndex);
    key = input.substr(spaceIndex+1, sizeof(input));
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < names.size(); i++) {
        if(key == toUpperStr(names[i])) {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){\
    bool isfound = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < grades.size(); i++) {
        if(key[0] == grades[i]) {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            isfound = true;
        }
    }
    if(!isfound) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
