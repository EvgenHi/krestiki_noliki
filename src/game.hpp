#define FMT_HEADER_ONLY

#include <iostream>
#include <string>

#include <fmt/core.h>

enum Winner {
    X,
    O,
    Draw,
    NotFound
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
        throw "meh";
        break;
    case Winner::NotFound:
        throw "meh";
        break;
    }
}


#include <optional>
#include <array>
using std::optional;
class TicTacToe {
    std::array<std::optional<char>,9> game_table{};
    Winner winner{NotFound};
    char last_move{};
    private:
        void print() const&;
        void find_winner() &;
        int prompt_digit() &;
        std::string paint_cell(optional<char> ch, char num) const&;
    public:
        TicTacToe();
        void play();
};

int prompt_digit();