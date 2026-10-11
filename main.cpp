#include <iostream>
#include <string>
#include <windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include "game.h"
#include "animation.h"
#include <stdlib.h>
using namespace std;

quickascii colour;

// Take 5 digit input in terminal
string answer_input()
{
    while (true)
    {
        string input = "";
        std::cout<< "\033[14;1H" << colour.yellow << "Enter word: " << colour.cyan;
        std::cout<<"\033[14;13H"<<"\033[K"<<"\033[14;13H";
        cin>>input;
        std::cout<<"\033[J"<<endl;
        if(input.size() != 5){
            std::cout<< colour.red << "\033[15;1H" << "Word must be 5 characters only!";
        }
        else{
            std::cout<<"\033[15;1H"<<"\033[K";
            return input;
        }
    }
    
}

// input at 12,15
// error at 1,16

int main()
{
    system("cls");
    string user_input;
    string answer;
    string random;
    int nav = 0;
    int oldnav = -1;
    int attempts = 1;
    bool won = false;

    while (true)
    {   
        std::cout<<"\033[H";         //Removes flickering
        std::cout<<"\033[?25l";      //Hides cursor
        for(string s:LOGO){
            std::cout<<s<<endl;
        }
        std::cout << "Use UP/DOWN ARROW for moving and TAB for selecting"<<endl;
        if(nav > 1 || nav < 0){
            if(keypressed(VK_DOWN) || keypressed(VK_UP)){
                nav = 0;
            }
        }
        if(keypressed(VK_DOWN) && nav < 1){
            nav++;
        }
        else if(keypressed(VK_UP) && nav > 0){
            nav--;
        }
        else if(keypressed(VK_TAB)){
            if (nav == 0){
                answer = "";
                attempts = 1;
                won = false;
                system("cls");
                random = pool[randomgen(0, pool.size() - 1)];
                std::cout << "\033[H"; // Move cursor to top left
                std::cout<<colour.reset;
                printbg();
                while (!won && attempts < 7)
                {
                    movecursor({1, 14});
                    std::cout << "                                                                                                         ";
                    movecursor({1, 14});
                    answer = "";
                    answer = answer_input();
                    if (writeintable(answer, random, attempts))
                    {
                        movecursor({1, 14});
                        std::cout << "                                                       ";
                        playanimation(you_won_anim, 1000, {1, 14});
                        break;
                    }
                    attempts++;
                }
                system("cls");
                nav = 100;
            }
            if (nav == 1){
                system("cls");
                std::cout<<colour.reset;
                exit(0);
            }
        }

        if(oldnav != nav){
            std::cout<<"\033[J";
            toggle("PLAY", nav, 0);
            toggle("QUIT", nav, 1);
            oldnav = nav;
        }

        std::cout<<colour.cyan;
        movecursor({1,16});
        std::cout << "GUIDE: ";
        std::cout << "Playing this is very simple each round the computer will generate a random 5 character word and you are supposed to guess what that word is in 6 attempts or less."<<endl;
        std::cout << "You start by taking a random or a calculated guess if your guess is correct then you win, if its wrong then there are 3 possibilities:\n"<<endl;
        std::cout << "- In the word you guessed none of the characters exist in the guessed word. For example `opera` and `quill` are two different words with no similarity." <<endl;
        std::cout << "- In the word you guessed, it has some or all characters as of the other word then the similar characters but in different position then it will be highlighted as cyan/blue colour. For example in `quill` and `lamar` both have the same character `l` and hence it will be highlighted." <<endl;
        std::cout << "- In the word you guessed, some of the characters have the same character at same position then it will be highlighted green. For example in word `queen` and `quill` both have `q` at the same place so it will be highlighted green."<<endl;
        std::cout << "\nThats all there is for you to be able to play this game."<<endl;
        std::cout << colour.reset;

        this_thread::sleep_for(chrono::milliseconds(80));
    }
}