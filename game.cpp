#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include<random>
#include "game.h"

static std::random_device rd;
static std::mt19937 gen(rd());
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

std::vector<std::string> pool = {
    "quill", "lamar", "queen", "brick", "storm",
    "apple", "brave", "crane", "dance", "eagle",
    "flame", "grape", "house", "ivory", "joker",
    "knife", "lemon", "mango", "noble", "ocean",
    "piano", "queen", "river", "stone", "tiger",
    "ultra", "vivid", "water", "xenon", "youth",
    "zebra", "angel", "bread", "cloud", "dream",
    "earth", "frost", "ghost", "heart", "image",
    "juice", "light", "magic", "night", "orbit",
    "peace", "quick", "radio", "smile", "train",
    "unity", "voice", "world", "yield", "zones",
    "beach", "chair", "drive", "enjoy", "field",
    "giant", "happy", "index", "judge", "known",
    "laugh", "money", "never", "order", "plant",
    "quiet", "round", "sweet", "table", "under",
    "visit", "whole", "young", "adore", "block",
    "charm", "count", "enter", "faith", "guide",
    "honor", "input", "learn", "model", "power",
    "reset", "serve", "trust", "value", "write",
    "adapt", "blaze", "candy", "clear", "delay",
    "event", "fresh", "globe", "ideal", "limit"
};

void printbg()
{
    for (std::string s : bg)
    {
        std::cout << s << std::endl;
    }
}

size_t randomgen(int min, int max){
    std::uniform_int_distribution<size_t> dist(min, max);

    return static_cast<size_t>(dist(gen));
}

bool findinstring(char c, std::string str){
    for(char &s : str){
        if(c==s){
            return true;
        }
    }
    return false;
}

#ifdef __linux__
static termios g_orig;
static bool g_raw = false;
static std::string g_buf;

void terminal_raw()
{
    std::cout << std::flush;
    if(!g_raw) {
        tcgetattr(STDIN_FILENO, &g_orig);
        termios raw = g_orig;
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_iflag &= ~IXON;
        raw.c_cc[VMIN] = 0;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        g_raw = true;
    }
}

void terminal_cooked()
{
    if(g_raw) {
        g_buf.clear();
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig);
        g_raw = false;
    }
}

void restoreterminal()
{
    terminal_cooked();
    std::cout << "\033[0m\033[?25h" << std::flush;
}
#endif

bool keypressed(int key)
{
#ifdef _WIN32
    return GetAsyncKeyState(key) & 0x8000;
#else
    char c;
    while(read(STDIN_FILENO, &c, 1) == 1)
        g_buf += c;
    if(g_buf.size() > 64)
        g_buf.erase(0, g_buf.size() - 64);

    const char* seq;
    size_t len;
    if(key == VK_UP) {
        seq = "\x1b[A";
        len = 3;
    }
    else if(key == VK_DOWN) {
        seq = "\x1b[B";
        len = 3;
    }
    else if(key == VK_TAB) {
        seq = "\t";
        len = 1;
    }
    else {
        return false;
    }

    size_t pos = g_buf.find(seq, 0, len);
    if(pos != std::string::npos) {
        g_buf.erase(pos, len);
        return true;
    }
    return false;
#endif
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