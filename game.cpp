#include <iostream>
#include <string>
#include <windows.h>
#include "game.h"

std::string bg[] = {
    "+---+---+---+---+---+",
    "|   |   |   |   |   |",
    "+---+---+---+---+---+",
    "|   |   |   |   |   |",
    "+---+---+---+---+---+",
    "|   |   |   |   |   |",
    "+---+---+---+---+---+",
    "|   |   |   |   |   |",
    "+---+---+---+---+---+",
    "|   |   |   |   |   |",
    "+---+---+---+---+---+",
    "|   |   |   |   |   |",
    "+---+---+---+---+---+"};

void printbg()
{
    for (std::string s : bg)
    {
        std::cout << s << std::endl;
    }
}

bool findinstring(char c, std::string str){
    for(char &s : str){
        if(c==s){
            return true;
        }
        else {return false;}
    }
}

bool keypressed(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}

void movecursor(vector2 to){
    std::cout<<"\033[" << to.y <<";"<<to.x<<"H";
}

bool booleaninput(std::string in)
{
    if (in == "Y")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void toggle(std::string sentence, int reference, int at){
    if(reference == at){
        std::cout << "\033[36m> "<<sentence<<" <"<<std::endl;
    }
    else{
        std::cout << "\033[0m"<<sentence<<""<<std::endl;
    }
}

bool writeintable(std::string input,std::string word, int attempt){
    int increment = 4;
    vector2 position = {3 - increment, 2*attempt};

    if(input == word){
        for(char &c : word){
            position.x += increment;
            movecursor(position);
            std::cout << "\033[32m" << c;
        }
        return true;
    }

    for(int i=0;i<5;i++){
        char c = input[i];
        position.x += increment;
        movecursor(position);
        
        if(c==word[i]){
            std::cout << "\033[32m"<<c<<"\033[37m";
        }
        else{
            if(findinstring(c, word)){
                std::cout << "\033[36m" << c<<"\033[37m";
            }
            else{
                std::cout << "\033[31m" << c<<"\033[37m";
            }
        }
    }
    return false;
}