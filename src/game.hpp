#define FMT_HEADER_ONLY

#include <iostream>
#include <optional>
#include <string>
#include <cstdio>

#include <locale>
#include <fmt/core.h>

using std::optional;

class TicTacToe {
    std::optional<char> game_table [9];
    private:
        void print() const&;
    public:
        TicTacToe();
        void play();
};

int prompt_digit();
