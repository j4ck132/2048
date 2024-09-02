//
//  main.cpp
//  2048
//
//  Created by Jack Yin on 12/3/20.
//

#include <iostream>
#include <string>
#include <sstream>
#include<unistd.h>

using namespace std;

char moves;
int highscore = 102924;
int score = 0;

string s[17];
string use[17];

string add(string a, string b){
    if (a == "    ") return "    ";
    stringstream twea(a);
    stringstream tweb(b);
    int x = 0;
    int y = 0;
    twea >> x;
    tweb >> y;
    if (x+y < 10) return (to_string(x+y)+"   ");
    else if (x+y < 100) return (to_string(x+y)+"  ");
    else if (x+y < 1000) return (to_string(x+y)+" ");
    else return to_string(x+y);
}

int multiply(int x){
    if (x == 0) return 0;
    int times = 0;
    while (x != 1){
        x = x/2;
        times++;
    }
    return times;
}

bool alive(){
    for (int i = 1; i < 17; i++){
        if (s[i] == "    ") return true;
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            if(s[4*i+j+1] == s[4*i+j+2]) return true;
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            if(s[4*i+j+1] == s[4*i+j+5]) return true;
        }
    }
    
    return false;
}

void display(){
    cout << endl;
    cout <<"┌───────┐ ┌───────┐ ┌───────┐ ┌───────┐" << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    for (int i = 0; i < 4; i++) cout <<"│ " << s[1+i] << "  │ ";
    cout << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    cout <<"└───────┘ └───────┘ └───────┘ └───────┘" << endl;
    cout <<"┌───────┐ ┌───────┐ ┌───────┐ ┌───────┐" << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    for (int i = 0; i < 4; i++) cout <<"│ " << s[5+i] << "  │ ";
    cout << "high score: " << highscore << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    cout <<"└───────┘ └───────┘ └───────┘ └───────┘" << endl;
    cout <<"┌───────┐ ┌───────┐ ┌───────┐ ┌───────┐" << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    for (int i = 0; i < 4; i++) cout <<"│ " << s[9+i] << "  │ ";
    cout << "score: " << score << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    cout <<"└───────┘ └───────┘ └───────┘ └───────┘" << endl;
    cout <<"┌───────┐ ┌───────┐ ┌───────┐ ┌───────┐" << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    for (int i = 0; i < 4; i++) cout <<"│ " << s[13+i] << "  │ ";
    cout << endl;
    cout <<"│       │ │       │ │       │ │       │" << endl;
    cout <<"└───────┘ └───────┘ └───────┘ └───────┘" << endl;
}

void up(){
    for (int i = 0; i < 4; i++){
        if (s[i+1] == s[i+5] && s[i+9] == s[i+13] && s[i+5] != "    " && s[i+9] != "    "){
            s[i+1] = add(s[i+1],s[i+5]);
            s[i+5] = add(s[i+9],s[i+13]);
            s[i+9] = "    ";
            s[i+13] = "    ";
        }
        else if (s[i+1] != s[i+5] && s[i+5] == s[i+9] && s[i+5] != "    "){
            if (s[i+1] == "    "){
                s[i+1] = add(s[i+5],s[i+9]);
                s[i+5] = s[i+13];
                s[i+9] = "    ";
                s[i+13] = "    ";
            }
            else {
                s[i+5] = add(s[i+5],s[i+9]);
                s[i+9] = s[i+13];
                s[i+13] = "    ";
            }
        }
        else if (s[i+1] == s[i+5] && s[i+1] != "    "){
            s[i+1] = add(s[i+1],s[i+5]);
            if (s[i+9] == "    "){
                s[i+5] = s[i+13];
                s[i+13] = "    ";
            }
            else {
                s[i+5] = s[i+9];
                s[i+9] = s[i+13];
                s[i+13] = "    ";
            }
        }
        else if (s[i+1] == s[i+9] && s[i+1] != "    " && s[i+5] == "    "){
            s[i+1] = add(s[i+1],s[i+9]);
            s[i+5] = s[i+13];
            s[i+9] = "    ";
            s[i+13] = "    ";
        }
        else if (s[i+9] == s[i+13] && s[i+9] != "    "){
            if (s[i+1] == "    " && s[i+5] == "    "){
                s[i+1] = add(s[i+9],s[i+13]);
                s[i+9] = "    ";
                s[i+13] = "    ";
            }
            else if (s[i+1] == "    "){
                s[i+1] = s[i+5];
                s[i+5] = add(s[i+9],s[i+13]);
                s[i+9] = "    ";
                s[i+13] = "    ";
            }
            else if (s[i+5] == "    "){
                s[i+5] = add(s[i+9],s[i+13]);
                s[i+9] = "    ";
                s[i+13] = "    ";
            }
            else {
                s[i+9] = add(s[i+9],s[i+13]);
                s[i+13] = "    ";
            }
        }
        else if (s[i+5] == s[i+13] && s[i+5] != "    " && s[i+9] == "    "){
            if (s[i+1] == "    "){
                s[i+1] = add(s[i+5],s[i+13]);
                s[i+5] = "    ";
                s[i+13] = "    ";
            }
            else {
                s[i+5] = add(s[i+5],s[i+13]);
                s[i+13] = "    ";
            }
        }
        else if (s[i+1] == s[i+13] && s[i+5] == "    " && s[i+9] == "    "){
            s[i+1] = add(s[i+1],s[i+13]);
            s[i+13] = "    ";
        }
        else if (s[i+1] == "    "){
            if (s[i+5] == "    " && s[i+9] == "    "){
                s[i+1] = s[i+13];
                s[i+13] = "    ";
            }
            else if (s[i+5] == "    "){
                s[i+1] = s[i+9];
                s[i+5] = s[i+13];
                s[i+9] = "    ";
                s[i+13] = "    ";
            }
            else if (s[i+9] == "    "){
                s[i+1] = s[i+5];
                s[i+5] = s[i+13];
                s[i+13] = "    ";
            }
            else {
                s[i+1] = s[i+5];
                s[i+5] = s[i+9];
                s[i+9] = s[i+13];
                s[i+13] = "    ";
            }
        }
        else if (s[i+5] == "    "){
            if (s[i+9] == "    "){
                s[i+5] = s[i+13];
                s[i+13] = "    ";
            }
            else {
                s[i+5] = s[i+9];
                s[i+9] = s[i+13];
                s[i+13] = "    ";
            }
        }
        else if (s[i+9] == "    "){
            s[i+9] = s[i+13];
            s[i+13] = "    ";
        }
    }
}

void left(){
    for (int i = 0; i < 4; i++){
        if (s[4*i+1] == s[4*i+2] && s[4*i+3] == s[4*i+4] && s[4*i+2] != "    " && s[4*i+3] != "    "){
            s[4*i+1] = add(s[4*i+1],s[4*i+2]);
            s[4*i+2] = add(s[4*i+3],s[4*i+4]);
            s[4*i+3] = "    ";
            s[4*i+4] = "    ";
        }
        else if (s[4*i+1] != s[4*i+2] && s[4*i+2] == s[4*i+3] && s[4*i+2] != "    "){
            if (s[4*i+1] == "    "){
                s[4*i+1] = add(s[4*i+2],s[4*i+3]);
                s[4*i+2] = s[4*i+4];
                s[4*i+3] = "    ";
                s[4*i+4] = "    ";
            }
            else {
                s[4*i+2] = add(s[4*i+2],s[4*i+3]);
                s[4*i+3] = s[4*i+4];
                s[4*i+4] = "    ";
            }
        }
        else if (s[4*i+1] == s[4*i+2] && s[4*i+1] != "    "){
            s[4*i+1] = add(s[4*i+1],s[4*i+2]);
            if (s[4*i+3] == "    "){
                s[4*i+2] = s[4*i+4];
                s[4*i+4] = "    ";
            }
            else {
                s[4*i+2] = s[4*i+3];
                s[4*i+3] = s[4*i+4];
                s[4*i+4] = "    ";
            }
        }
        else if (s[4*i+1] == s[4*i+3] && s[4*i+1] != "    " && s[4*i+2] == "    "){
            s[4*i+1] = add(s[4*i+1],s[4*i+3]);
            s[4*i+2] = s[4*i+4];
            s[4*i+3] = "    ";
            s[4*i+4] = "    ";
        }
        else if (s[4*i+3] == s[4*i+4] && s[4*i+3] != "    "){
            if (s[4*i+1] == "    " && s[4*i+2] == "    "){
                s[4*i+1] = add(s[4*i+3],s[4*i+4]);
                s[4*i+3] = "    ";
                s[4*i+4] = "    ";
            }
            else if (s[4*i+1] == "    "){
                s[4*i+1] = s[4*i+2];
                s[4*i+2] = add(s[4*i+3],s[4*i+4]);
                s[4*i+3] = "    ";
                s[4*i+4] = "    ";
            }
            else if (s[4*i+2] == "    "){
                s[4*i+2] = add(s[4*i+3],s[4*i+4]);
                s[4*i+3] = "    ";
                s[4*i+4] = "    ";
            }
            else {
                s[4*i+3] = add(s[4*i+3],s[4*i+4]);
                s[4*i+4] = "    ";
            }
        }
        else if (s[4*i+2] == s[4*i+4] && s[4*i+2] != "    " && s[4*i+3] == "    "){
            if (s[4*i+1] == "    "){
                s[4*i+1] = add(s[4*i+2],s[4*i+4]);
                s[4*i+2] = "    ";
                s[4*i+4] = "    ";
            }
            else {
                s[4*i+2] = add(s[4*i+2],s[4*i+4]);
                s[4*i+4] = "    ";
            }
        }
        else if (s[4*i+1] == s[4*i+4] && s[4*i+2] == "    " && s[4*i+3] == "    "){
            s[4*i+1] = add(s[4*i+1],s[4*i+4]);
            s[4*i+4] = "    ";
        }
        else if (s[4*i+1] == "    "){
            if (s[4*i+2] == "    " && s[4*i+3] == "    "){
                s[4*i+1] = s[4*i+4];
                s[4*i+4] = "    ";
            }
            else if (s[4*i+2] == "    "){
                s[4*i+1] = s[4*i+3];
                s[4*i+2] = s[4*i+4];
                s[4*i+3] = "    ";
                s[4*i+4] = "    ";
            }
            else if (s[4*i+3] == "    "){
                s[4*i+1] = s[4*i+2];
                s[4*i+2] = s[4*i+4];
                s[4*i+4] = "    ";
            }
            else {
                s[4*i+1] = s[4*i+2];
                s[4*i+2] = s[4*i+3];
                s[4*i+3] = s[4*i+4];
                s[4*i+4] = "    ";
            }
        }
        else if (s[4*i+2] == "    "){
            if (s[4*i+3] == "    "){
                s[4*i+2] = s[4*i+4];
                s[4*i+4] = "    ";
            }
            else {
                s[4*i+2] = s[4*i+3];
                s[4*i+3] = s[4*i+4];
                s[4*i+4] = "    ";
            }
        }
        else if (s[4*i+3] == "    "){
            s[4*i+3] = s[4*i+4];
            s[4*i+4] = "    ";
        }
    }
}

void down(){
    for (int i = 0; i < 4; i++){
        if (s[i+13] == s[i+9] && s[i+5] == s[i+1] && s[i+9] != "    " && s[i+5] != "    "){
            s[i+13] = add(s[i+13],s[i+9]);
            s[i+9] = add(s[i+5],s[i+1]);
            s[i+5] = "    ";
            s[i+1] = "    ";
        }
        else if (s[i+13] != s[i+9] && s[i+9] == s[i+5] && s[i+9] != "    "){
            if (s[i+13] == "    "){
                s[i+13] = add(s[i+9],s[i+5]);
                s[i+9] = s[i+1];
                s[i+5] = "    ";
                s[i+1] = "    ";
            }
            else {
                s[i+9] = add(s[i+9],s[i+5]);
                s[i+5] = s[i+1];
                s[i+1] = "    ";
            }
        }
        else if (s[i+13] == s[i+9] && s[i+13] != "    "){
            s[i+13] = add(s[i+13],s[i+9]);
            if (s[i+5] == "    "){
                s[i+9] = s[i+1];
                s[i+1] = "    ";
            }
            else {
                s[i+9] = s[i+5];
                s[i+5] = s[i+1];
                s[i+1] = "    ";
            }
        }
        else if (s[i+13] == s[i+5] && s[i+13] != "    " && s[i+9] == "    "){
            s[i+13] = add(s[i+13],s[i+5]);
            s[i+9] = s[i+1];
            s[i+5] = "    ";
            s[i+1] = "    ";
        }
        else if (s[i+5] == s[i+1] && s[i+5] != "    "){
            if (s[i+13] == "    " && s[i+9] == "    "){
                s[i+13] = add(s[i+5],s[i+1]);
                s[i+5] = "    ";
                s[i+1] = "    ";
            }
            else if (s[i+13] == "    "){
                s[i+13] = s[i+9];
                s[i+9] = add(s[i+5],s[i+1]);
                s[i+5] = "    ";
                s[i+1] = "    ";
            }
            else if (s[i+9] == "    "){
                s[i+9] = add(s[i+5],s[i+1]);
                s[i+5] = "    ";
                s[i+1] = "    ";
            }
            else {
                s[i+5] = add(s[i+5],s[i+1]);
                s[i+1] = "    ";
            }
        }
        else if (s[i+9] == s[i+1] && s[i+9] != "    " && s[i+5] == "    "){
            if (s[i+13] == "    "){
                s[i+13] = add(s[i+9],s[i+1]);
                s[i+9] = "    ";
                s[i+1] = "    ";
            }
            else {
                s[i+9] = add(s[i+9],s[i+1]);
                s[i+1] = "    ";
            }
        }
        else if (s[i+13] == s[i+1] && s[i+9] == "    " && s[i+5] == "    "){
            s[i+13] = add(s[i+13],s[i+1]);
            s[i+1] = "    ";
        }
        else if (s[i+13] == "    "){
            if (s[i+9] == "    " && s[i+5] == "    "){
                s[i+13] = s[i+1];
                s[i+1] = "    ";
            }
            else if (s[i+9] == "    "){
                s[i+13] = s[i+5];
                s[i+9] = s[i+1];
                s[i+5] = "    ";
                s[i+1] = "    ";
            }
            else if (s[i+5] == "    "){
                s[i+13] = s[i+9];
                s[i+9] = s[i+1];
                s[i+1] = "    ";
            }
            else {
                s[i+13] = s[i+9];
                s[i+9] = s[i+5];
                s[i+5] = s[i+1];
                s[i+1] = "    ";
            }
        }
        else if (s[i+9] == "    "){
            if (s[i+5] == "    "){
                s[i+9] = s[i+1];
                s[i+1] = "    ";
            }
            else {
                s[i+9] = s[i+5];
                s[i+5] = s[i+1];
                s[i+1] = "    ";
            }
        }
        else if (s[i+5] == "    "){
            s[i+5] = s[i+1];
            s[i+1] = "    ";
        }
    }
}

void right(){
    for (int i = 0; i < 4; i++){
        if (s[4*i+4] == s[4*i+3] && s[4*i+2] == s[4*i+1] && s[4*i+3] != "    " && s[4*i+2] != "    "){
            s[4*i+4] = add(s[4*i+4],s[4*i+3]);
            s[4*i+3] = add(s[4*i+2],s[4*i+1]);
            s[4*i+2] = "    ";
            s[4*i+1] = "    ";
        }
        else if (s[4*i+4] != s[4*i+3] && s[4*i+3] == s[4*i+2] && s[4*i+3] != "    "){
            if (s[4*i+4] == "    "){
                s[4*i+4] = add(s[4*i+3],s[4*i+2]);
                s[4*i+3] = s[4*i+1];
                s[4*i+2] = "    ";
                s[4*i+1] = "    ";
            }
            else {
                s[4*i+3] = add(s[4*i+3],s[4*i+2]);
                s[4*i+2] = s[4*i+1];
                s[4*i+1] = "    ";
            }
        }
        else if (s[4*i+4] == s[4*i+3] && s[4*i+4] != "    "){
            s[4*i+4] = add(s[4*i+4],s[4*i+3]);
            if (s[4*i+2] == "    "){
                s[4*i+3] = s[4*i+1];
                s[4*i+1] = "    ";
            }
            else {
                s[4*i+3] = s[4*i+2];
                s[4*i+2] = s[4*i+1];
                s[4*i+1] = "    ";
            }
        }
        else if (s[4*i+4] == s[4*i+2] && s[4*i+4] != "    " && s[4*i+3] == "    "){
            s[4*i+4] = add(s[4*i+4],s[4*i+2]);
            s[4*i+3] = s[4*i+1];
            s[4*i+2] = "    ";
            s[4*i+1] = "    ";
        }
        else if (s[4*i+2] == s[4*i+1] && s[4*i+2] != "    "){
            if (s[4*i+4] == "    " && s[4*i+3] == "    "){
                s[4*i+4] = add(s[4*i+2],s[4*i+1]);
                s[4*i+2] = "    ";
                s[4*i+1] = "    ";
            }
            else if (s[4*i+4] == "    "){
                s[4*i+4] = s[4*i+3];
                s[4*i+3] = add(s[4*i+2],s[4*i+1]);
                s[4*i+2] = "    ";
                s[4*i+1] = "    ";
            }
            else if (s[4*i+3] == "    "){
                s[4*i+3] = add(s[4*i+2],s[4*i+1]);
                s[4*i+2] = "    ";
                s[4*i+1] = "    ";
            }
            else {
                s[4*i+2] = add(s[4*i+2],s[4*i+1]);
                s[4*i+1] = "    ";
            }
        }
        else if (s[4*i+3] == s[4*i+1] && s[4*i+3] != "    " && s[4*i+2] == "    "){
            if (s[4*i+4] == "    "){
                s[4*i+4] = add(s[4*i+3],s[4*i+1]);
                s[4*i+3] = "    ";
                s[4*i+1] = "    ";
            }
            else {
                s[4*i+3] = add(s[4*i+3],s[4*i+1]);
                s[4*i+1] = "    ";
            }
        }
        else if (s[4*i+4] == s[4*i+1] && s[4*i+3] == "    " && s[4*i+2] == "    "){
            s[4*i+4] = add(s[4*i+4],s[4*i+1]);
            s[4*i+1] = "    ";
        }
        else if (s[4*i+4] == "    "){
            if (s[4*i+3] == "    " && s[4*i+2] == "    "){
                s[4*i+4] = s[4*i+1];
                s[4*i+1] = "    ";
            }
            else if (s[4*i+3] == "    "){
                s[4*i+4] = s[4*i+2];
                s[4*i+3] = s[4*i+1];
                s[4*i+2] = "    ";
                s[4*i+1] = "    ";
            }
            else if (s[4*i+2] == "    "){
                s[4*i+4] = s[4*i+3];
                s[4*i+3] = s[4*i+1];
                s[4*i+1] = "    ";
            }
            else {
                s[4*i+4] = s[4*i+3];
                s[4*i+3] = s[4*i+2];
                s[4*i+2] = s[4*i+1];
                s[4*i+1] = "    ";
            }
        }
        else if (s[4*i+3] == "    "){
            if (s[4*i+2] == "    "){
                s[4*i+3] = s[4*i+1];
                s[4*i+1] = "    ";
            }
            else {
                s[4*i+3] = s[4*i+2];
                s[4*i+2] = s[4*i+1];
                s[4*i+1] = "    ";
            }
        }
        else if (s[4*i+2] == "    "){
            s[4*i+2] = s[4*i+1];
            s[4*i+1] = "    ";
        }
    }
}

int main() {
    
    for (int i = 1; i < 17; i++){
        s[i] = "    ";
    }
    s[0] = "2    ";
    
    srand(time(0));
    if (rand() % 6 == 0) s[rand() % 16 + 1] = "4   ";
    else s[rand() % 16 + 1] = "2   ";
    s[rand() % 16 + 1] = "2   ";
    
    display();
    system("stty raw");
    
    while(alive()){
        for (int i = 1; i < 17; i++){
            use[i] = s[i];
        }
        moves = getchar();
        if (moves == 'w') up();
        if (moves == 'a') left();
        if (moves == 's') down();
        if (moves == 'd') right();

        for (int i = 1; i < 17; i++){
            stringstream twec(s[i]);
            stringstream twed(use[i]);
            int m = 0;
            int n = 0;
            twec >> m;
            twed >> n;
            score += m * multiply(m);
            score -= n * multiply(n);
        }
        
        bool test = false;
        for (int i = 1; i < 17; i++){
            if (use[i] != s[i]) test = true;
        }
        
        display();
        usleep(15000);
        
        if (test){
            int x = 0;
            while (s[x] != "    "){
                x = rand() % 16 + 1;
            }
            if (rand() % 6 == 0) s[x] = "4   ";
            else s[x] = "2   ";
        }
        
        display();
    }
    cout << "Game Over" << endl;
    
    return 0;
}
