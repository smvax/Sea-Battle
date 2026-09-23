#include "game.h"

//-----PLAYER

Player::Player() {
    for (size_t i = 0; i < CELL_COUNT; i++) {
        _ships_counts[i] = 0;
    }
}

void Player::set_ship(const Ship& ship) {
    int size = ship.size();
    if (size < 1 || size > CELL_COUNT) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    int index = size - 1;
    if (_ships_counts[index] < _max_ships_counts[index] && !is_collision(_gamefield, ship)) {
        _gamefield.set(ship);
        _ships_counts[index]++;
        return;
    }
    throw std::logic_error("Invalid input: incorrect field");
}

State Player::set_action(int row, char col) {
    if (row < 1 || col < 'A') {
        throw std::logic_error("Invalid input: incorrect move");
    }
    State result = _gamefield.set(row, col);

    if (result == BoatDestroyed) {
        _ships_counts[0]--;
    }
    else if (result == DestroyersDestroyed) {
        _ships_counts[1]--;
    }
    else if (result == CruisersDestroyed) {
        _ships_counts[2]--;
    }
    else if (result == BattleshipDestroyed) {
        _ships_counts[3]--;
    }
    return result;
}

void Player::show_field(bool hide_ships) const {
    std::cout << to_string(_gamefield, hide_ships) << std::endl;
    std::cout << "Ships Left:" << std::endl;
    std::cout << "* - " << _ships_counts[0] << " "
        << "** - " << _ships_counts[1] << " "
        << "*** - " << _ships_counts[2] << " "
        << "**** - " << _ships_counts[3] << std::endl;
}

inline bool Player::check_lose() const noexcept {
    for (size_t i = 0; i < CELL_COUNT; i++) {
        if (_ships_counts[i] > 0) {
            return false;
        }
    }
    return true;
}

bool Player::check_ready() const noexcept {
    for (size_t i = 0; i < CELL_COUNT; i++) {
        if (_ships_counts[i] != _max_ships_counts[i]) {
            return false;
        }
    }
    return true;
}

const int Player::_max_ships_counts[CELL_COUNT] = { 4, 3, 2, 1 };

//----------GAME

Game::Game() : _user(), _computer(), _comp_row(0), _comp_col(0), _comp_diag(0) {}

void Game::user_init(std::string ship_input) {
    try {
        _user.set_ship(Ship(ship_input));
    }
    catch (...) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

void Game::computer_init(std::string ship_input) {
    try {
        _computer.set_ship(Ship(ship_input));
    }
    catch (...) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

State Game::user_move(std::string input) {
    State result;
    try {
        Position pos(input);
        result = _computer.set_action(pos.row(), static_cast<char>(pos.col() + 'A' - 1));
    }
    catch (...) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    return result;
}

State Game::computer_move() {
    State result;
    while (true) {
        if (_comp_diag == 0) {
            _comp_row++;
            _comp_col++;
            if (_comp_row >= 11) {
                _comp_diag = 1;
                _comp_row = 1;
                _comp_col = 10;
            }
            try {
                result = _user.set_action(_comp_row, static_cast<char>(_comp_col + 'A' - 1));
                return result;
            }
            catch (...) {
                throw std::logic_error("Invalid input: incorrect field");
            }
        }

        if (_comp_diag == 1) {
            _comp_row++;
            _comp_col--;
            if (_comp_row >= 11) {
                _comp_diag = 2;
                _comp_row = 1;
                _comp_col = 2;
            }
            try {
                result = _user.set_action(_comp_row, static_cast<char>(_comp_col + 'A' - 1));
                return result;
            }
            catch (...) {
                throw std::logic_error("Invalid input: incorrect field");
            }
        }

        if (_comp_diag == 2) {
            if (_comp_row >= 11) {
                break;
            }

            _comp_col++;
            if (_comp_row == _comp_col || 11 - _comp_col == _comp_row) {
                _comp_col++;
            }
            if (_comp_col >= 11) {
                _comp_col = 1;
                _comp_row++;
            }
            if (_comp_row == _comp_col || 11 - _comp_col == _comp_row) {
                _comp_col++;
            }
            if (_comp_row >= 10 && _comp_col >= 11) {
                break;
            }
            try {
                result = _user.set_action(_comp_row, static_cast<char>(_comp_col + 'A' - 1));
                return result;
            }
            catch (...) {
                throw std::logic_error("Invalid input: incorrect field");
            }
        }
    }
    return State::Missed;
}

void Game::show_game_window() noexcept {
    std::cout << "= COMPUTER GAME FIELD =\n\n";
    _user.show_field(false);
    std::cout << "\n=== YOUR PLAY FIELD ===\n\n";
    _computer.show_field(true);
}

void Game::start() {
    std::string user_field_input;
    std::string comp_field_input;
    std::string empty_line;

    for (size_t i = 0; i < 10; i++) {
        std::getline(std::cin, user_field_input);
        try {
            user_init(user_field_input);
        }
        catch (...) {
            throw std::logic_error("Invalid input: incorrect field");
        }
    }
    std::getline(std::cin, empty_line);

    for (size_t i = 0; i < 10; i++) {
        std::getline(std::cin, comp_field_input);
        try {
            computer_init(comp_field_input);
        }
        catch (...) {
            throw std::logic_error("Invalid input: incorrect field");
        }
    }
    std::getline(std::cin, empty_line);
    show_game_window();
    std::cout << std::endl;

    bool user_turn = true;
    std::string turn_input;

    while (!is_end()) {
        if (user_turn) {
            std::getline(std::cin, turn_input);
            if (turn_input.empty()) {
                continue;
            }
            State res = user_move(turn_input);
            if (res == State::Missed) {
                user_turn = false;
            }
            else {
                user_turn = true;
            }
        }
        else {
            State res = computer_move();
            if (res == State::Missed) {
                user_turn = true;
            }
            else {
                user_turn = false;
            }
        }
    }

    show_game_window();

    if (_computer.check_lose()) {
        std::cout << std::endl << "USER WIN!\n";
    }
    else {
        std::cout << std::endl << "COMPUTER WIN!\n";
    }
}

