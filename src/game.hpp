#define FMT_HEADER_ONLY

#include <iostream>
#include <string>

#include <fmt/core.h>

enum Winner {
    X,
    O,
    Draw
};

Winner to_winner(char s) {
    if (s == 'X') {
        return Winner::X;
    } else {
        return Winner::O;
    }
}

char from_winner(Winner w) {
    switch (w)
    {
    case Winner::X:
        return 'X';
        break;
    case Winner::O:
        return 'O';
        break;
    case Winner::Draw:
        return 'D';
        break;
    }
}
class WinnerNotFound {} WinnerNotFound;

#include <optional>
using std::optional;
class TicTacToe {
    std::optional<char> game_table [9];
    private:
        void print() const&;
        Winner get_winner() const&;
    public:
        TicTacToe();
        void play();
};

int prompt_digit();