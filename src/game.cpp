#include "game.hpp"

TicTacToe::TicTacToe() {

}

// Prompts integer in 1..=9
int prompt_digit() {
    bool valid_input = false;
    std::string raw_input;
    int user_choose;
    while (!valid_input) {
        fmt::print("Put char in: ");
        std::cin >> raw_input;
        try {
            user_choose = std::stoi(raw_input);
        } catch (std::invalid_argument) {
            continue;
        } catch (std::out_of_range) {
            continue;
        }
        if (user_choose >= 0 && user_choose <= 9) {
            return user_choose;
        }
        
    }
    throw "unreachable";
}

void TicTacToe::play() {
    bool game_end = false;
    int current_move = 0;
    while (!game_end) {
        current_move += 1;
        this->print();
        game_table[prompt_digit() - 1] = current_move % 2 ? 'X' : 'O';
    }
}
void TicTacToe::print() const& {
    fmt::print("\
+---+---+---+\n\
| {} | {} | {} |\n\
+---+---+---+\n\
| {} | {} | {} |\n\
+---+---+---+\n\
| {} | {} | {} |\n\
+---+---+---+\n",
game_table[0].value_or('1'),
game_table[1].value_or('2'),
game_table[2].value_or('3'),
game_table[3].value_or('4'),
game_table[4].value_or('5'),
game_table[5].value_or('6'),
game_table[6].value_or('7'),
game_table[7].value_or('8'),
game_table[8].value_or('9')
    );
}

int main() {
    TicTacToe game;
    game.play();

}
