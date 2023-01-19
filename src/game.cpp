#include "game.hpp"

TicTacToe::TicTacToe(){}

// Prompts integer in 1..=9
int TicTacToe::prompt_digit() & {
    std::string raw_input;
    int user_choice;
    while (true) {
        fmt::print("Put char in: ");
        std::cin >> raw_input;
        try {
            user_choice = std::stoi(raw_input);
        } catch (...) {
            continue;
        }
        if (user_choice >= 0 && user_choice <= 9 && !game_table[user_choice -1].has_value()) {
            last_move = std::to_string(user_choice).c_str()[0];
            return user_choice;
        }
    }
}

void TicTacToe::find_winner() & {
    // Check lines
    for (int i = 0; i < 3; i++) {
        int sp(i * 3); // start point 
        optional<char> char_at_sp(game_table[sp]); // char at start point
        if ( char_at_sp.has_value() && game_table[sp + 1] == char_at_sp && game_table[sp + 2] == char_at_sp) {
            this->winner=to_winner(char_at_sp.value());
            return;
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        int sp(i);
        optional<char> char_at_sp(game_table[sp]);
        if ( char_at_sp.has_value() && game_table[sp + 3] == char_at_sp && game_table[sp + 6] == char_at_sp) {
            this->winner = to_winner(char_at_sp.value()); 
            return; 
        }
    }
    // Check diagonales
    if (game_table[0].has_value()) {
        optional<char> char_at_sp(game_table[0]);
        if (game_table[4] == char_at_sp && game_table[8] == char_at_sp) {
            this->winner = to_winner(char_at_sp.value());
            return;
        }
    }
    if (game_table[2].has_value()) {
        optional<char> char_at_sp(game_table[2]);
        if (game_table[4] == char_at_sp && game_table[6] == char_at_sp) {
            this->winner = to_winner(char_at_sp.value());
            return;
        }
    }
    // If any of cell contains 'None' at this point, that means that Winner wasn't dound
    for (int i = 0; i < 9;i++) {
        if (!game_table[i].has_value()) {
            this->winner = Winner::NotFound;
            return; 
        }
    }
    // If none of the checks above returned 
    this->winner=Winner::Draw;
}

void TicTacToe::play() {
    fmt::print("\x1B[H");
    fmt::print("\x1B[2J");
    int current_move = 0;
    while (this->winner == NotFound) {
        this->print();

        current_move += 1;
        int user_choice = prompt_digit();
        game_table[user_choice- 1] = current_move % 2 ? 'X' : 'O';    
        
        this->find_winner();
        fmt::print("\x1B[H");
        fmt::print("\x1B[2J");            
        switch (winner) {
            case X:
                this->print();
                fmt::print("X won\n");
                break;
            case O:
                this->print();
                fmt::print("O won\n");
                break;
            case Draw:
                this->print();
                fmt::print("Draw\n");
                break;
            case NotFound:
                break;
        };
    }
}

std::string TicTacToe::paint_cell(optional<char> ch, char num) const& {
    std::string start_o("\x1B[38;5;46m");
    std::string start_x("\x1B[38;5;160m");
    std::string start_last("\x1B[38;5;220m");
    std::string start_num("\x1B[38;5;243m");  
    std::string end_color("\x1B[38;5;15m");
    char ch_cell = ch.value_or(num);
    return fmt::format("{}{}{}", num == last_move ? start_last : ch_cell == 'O' ? start_o : ch_cell == 'X' ? start_x : start_num, ch_cell, end_color);
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
this->paint_cell(game_table[0], '1'),
this->paint_cell(game_table[1], '2'),
this->paint_cell(game_table[2], '3'),
this->paint_cell(game_table[3], '4'),
this->paint_cell(game_table[4], '5'),
this->paint_cell(game_table[5], '6'),
this->paint_cell(game_table[6], '7'),
this->paint_cell(game_table[7], '8'),
this->paint_cell(game_table[8], '9')
    );
}

int main() {
    TicTacToe game;
    game.play();
}
