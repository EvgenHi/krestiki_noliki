#include "game.hpp"

TicTacToe::TicTacToe() {}

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

Winner TicTacToe::get_winner() const& {
    // Check lines
    for (int i = 0; i < 3; i++) {
        int sp(i * 3); // start point 
        optional<char> char_at_sp(game_table[sp]); // char at start point
        if ( char_at_sp.has_value() && game_table[sp + 1] == char_at_sp && game_table[sp + 2] == char_at_sp) {
            return to_winner(char_at_sp.value());
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        int sp(i);
        optional<char> char_at_sp(game_table[sp]);
        if ( char_at_sp.has_value() && game_table[sp + 3] == char_at_sp && game_table[sp + 6] == char_at_sp) {
            return to_winner(char_at_sp.value());
        }
    }
    // Check diagonales
    if (game_table[0].has_value()) {
        optional<char> char_at_sp(game_table[0]);
        if (game_table[4] == char_at_sp && game_table[8] == char_at_sp) {
            return to_winner(char_at_sp.value());
        }
    }
    if (game_table[2].has_value()) {
        optional<char> char_at_sp(game_table[2]);
        if (game_table[4] == char_at_sp && game_table[6] == char_at_sp) {
            return to_winner(char_at_sp.value());
        }
    }
    // If any of cell contains 'None' at this point, that means that Winner wasn't dound
    for (int i = 0; i < 9;i++) {
        if (!game_table[i].has_value()) {
            throw WinnerNotFound;   
        }
    }
    // If none of the checks above returned 
    return Winner::Draw;
}

void TicTacToe::play() {
    fmt::print("\x1B[H");
    fmt::print("\x1B[2J");
    int current_move = 0;
    while (true) {
        current_move += 1;
        this->print();
        int user_choice = prompt_digit();
        if (game_table[user_choice- 1].has_value()) {
            continue;
        } else {
            game_table[user_choice- 1] = current_move % 2 ? 'X' : 'O';
        }
        try {
            Winner winner(this->get_winner());
            fmt::print("\x1B[2J");
            this->print();
            switch (winner) {
                case X:
                    fmt::print("X won");
                    break;
                case O:
                    fmt::print("O won");
                    break;
                case Draw:
                    fmt::print("Draw");
                    break;
            }
            break;
        } catch (class WinnerNotFound) {
            fmt::print("\x1B[2J");
            fmt::print("\x1B[H");
        }

    }
}

std::string paint_cell_or_num(optional<char> ch, char num) {
    std::string start_o("\x1B[38;5;46m");
    std::string start_x("\x1B[38;5;160m");
    std::string start_num("\x1B[38;5;243m");  
    std::string end_color("\x1B[38;5;15m");
    char ch_cell = ch.value_or(num);
    return fmt::format("{}{}{}", ch_cell == 'X' ? start_x : ch_cell == 'O' ? start_o : start_num, ch_cell, end_color);
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
paint_cell_or_num(game_table[0], '1'),
paint_cell_or_num(game_table[1], '2'),
paint_cell_or_num(game_table[2], '3'),
paint_cell_or_num(game_table[3], '4'),
paint_cell_or_num(game_table[4], '5'),
paint_cell_or_num(game_table[5], '6'),
paint_cell_or_num(game_table[6], '7'),
paint_cell_or_num(game_table[7], '8'),
paint_cell_or_num(game_table[8], '9')
    );
}

int main() {
    TicTacToe game;
    game.play();
}
