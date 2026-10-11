#pragma once
#include<iostream>
#include<string>

extern std::string bg[];

extern std::vector<std::string> pool;

enum result{
    incorrect, correct, wrongposition
};

struct vector2{
    int x;
    int y;
};

struct quickascii{
    std::string red = "\033[31m";
    std::string green = "\033[32m";
    std::string yellow = "\033[33m";
    std::string blue = "\033[34m";
    std::string magenta = "\033[35m";
    std::string cyan = "\033[36m";
    std::string reset = "\033[0m";
};

size_t randomgen(int min, int max);

void printbg();

bool findinstring(char c, std::string str);

void movecursor(vector2 to);

bool keypressed(int key);

bool booleaninput(std::string in);

void toggle(std::string sentence, int reference, int at);

bool writeintable(std::string input, std::string word, int attempt);