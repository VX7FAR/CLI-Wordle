<h1>CLIWordle</h1>

Yknow the wordle game in discord where we are supposed to guess a random word by giving small hints?
Thats what I made but it works in terminal and was made purely from C++ without any additional libraries.

## How to play?
Playing this is very simple each round the computer will generate a random 5 character word and you are supposed to guess what that word is in 6 attempts or less.
You start by taking a random or a calculated guess if your guess is correct then you win, if its wrong then there are 3 possibilities:

- In the word you guessed none of the characters exist in the guessed word. For example `opera` and `quill` are two different words with no similarity.
- In the word you guessed, it has some or all characters as of the other word then the similar characters but in different position then it will be highlighted as cyan/blue colour. For example in `quill` and `lamar` both have the same character `l` and hence it will be highlighted
- In the word you guessed, some of the characters have the same character at same position then it will be highlighted green. For example in word `queen` and `quill` both have `q` at the same place so it will be highlighted green.

Thats all there is for you to be able to play this game.

## How to run?
Runinng this is very simple, you simply download the release version and run the `.exe` file.
Or if you have C++20 then you can simply download the source code and compile it yourself. No libraries needed!