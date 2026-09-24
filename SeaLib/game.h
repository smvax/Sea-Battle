#pragma once
#include "sea.h"
#define CELL_COUNT 4

//--------PLAYER

class Player {
    GameField _gamefield;                   //player's fiels with setted ships
    int _ships_counts[4];

    static const int _max_ships_counts[4];  // count of ships with 1-4 cells

public:
    Player();

    void set_ship(const Ship&);
    State set_action(int row, char col);
    void show_field(bool hide_ships = false) const;
    inline bool check_lose() const noexcept;
    bool check_ready() const noexcept;
};

//--------GAME

class Game {
protected: //for GTests
    Player _user;        //user field
    Player _computer;    //computer field

    int _comp_row = 0;
    int _comp_col = 0;
    int _comp_diag = 0;

    void user_init(std::string);
    void computer_init(std::string);
    inline bool is_end() noexcept;
    void show_game_window() noexcept;
    State user_move(std::string);
    State computer_move();

public:
    Game();
    void start();
};

inline bool Game::is_end() noexcept {
    return (_user.check_lose() || _computer.check_lose());
}


