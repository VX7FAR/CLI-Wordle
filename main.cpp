#include <iostream>
#include <string>
#include <windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include "game.h"
#include "animation.h"
using namespace std;

quickascii colour;
string guess;
string random = "asdfg";

// Take 5 digit input in terminal
string answer_input()
{
    while (true)
    {
        string input = "";
        cout<< "\033[14;1H" << colour.yellow << "Enter word: " << colour.cyan;
        cout<<"\033[14;13H"<<"\033[K"<<"\033[14;13H";
        cin>>input;
        if(input.size() != 5){
            cout<< colour.red << "\033[15;1H" << "Word must be 5 characters only!";
        }
        else{
            cout<<"\033[15;1H"<<"\033[K";
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
    int nav = 0;
    int oldnav = -1;
    int attempts = 1;
    bool won = false;

    while (true)
    {   
        cout<<"\033[H";         //Removes flickering
        cout<<"\033[?25l";      //Hides cursor
        for(string s:LOGO){
            cout<<s<<endl;
        }
        cout << "Use UP/DOWN ARROW for moving and ENTER for selecting"<<endl;
        if(keypressed(VK_UP)){
            nav = 0;
        }
        else if(keypressed(VK_DOWN)){
            nav = 1;
        }
        else if(keypressed(VK_RETURN)){
            if (nav == 0){
                answer = "";
                attempts = 1;
                won = false;
                system("cls");
                cout << "\033[H"; // Move cursor to top left
                cout<<colour.reset;
                printbg();
                while (!won && attempts < 7)
                {
                    movecursor({1, 14});
                    cout << "                                                                                                         ";
                    movecursor({1, 14});
                    answer = answer_input();
                    if (writeintable(answer, "quill", attempts))
                    {
                        movecursor({1, 14});
                        std::cout << "                                                       ";
                        playanimation(you_won_anim, 1000, {1, 14});
                        break;
                    }
                    attempts++;
                }
                system("cls");
            }
        }

        if(oldnav != nav){
            cout<<"\033[J";
            toggle("PLAY", nav, 0);
            toggle("QUIT", nav, 1);
            oldnav = nav;
        }

        this_thread::sleep_for(chrono::milliseconds(80));
    }
}