#include "sea.h"

//-------------POSITION-------------

const int Position::_max_row(10);
const int Position::_max_col(10);

Position::Position() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
    _row = std::rand() % _max_row + 1;
    _col = std::rand() % _max_col + 1;
}

Position::Position(int row, int col) {
    if (is_collision(row) || is_collision(static_cast<char>('A' + col - 1))) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = col;
}

Position::Position(int row, char col) {
    if (is_collision(row) || is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = std::toupper(col) - 'A' + 1;
}

Position::Position(const Position& other) {
    _row = other._row;
    _col = other._col;
}

Position::Position(const std::string& str) {
    parse(str, (*this));
}

void parse(const std::string& str, Position& pos) {
    int row = 0;
    char col = 0;
    size_t i = 0;
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    while (i < str.size() && std::isdigit(str[i])) {
        row = row * 10 + (str[i] - '0');
        i++;
    }
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    if (i < str.size() && std::isalpha(str[i])) {
        col = std::toupper(str[i]);
    }
    pos = Position(row, col);
}

std::string to_string(const Position& p) {
    std::string result;
    result.append("(");
    result.append(std::to_string(p._row));
    result.append(", ");
    result.append(std::to_string(p._col));
    result.append(")");
    return result;
}

bool is_collision(int row) {
    return (row < 1 || row > Position::_max_row);
}

bool is_collision(char col) {
    char upper_col = std::toupper(static_cast<unsigned char>(col));
    int col_num = upper_col - 'A' + 1;
    return (col_num < 1 || col_num > Position::_max_col);
}

//---------SHIP---------------

Ship::Ship(int size, Position position, Direction direction) : _size(size), _position(position), _direction(direction) {
    if (is_collision(size, position, direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

Ship::Ship(int size, char direction, int row, char col) {
    try {
        _position = Position(row, col);
    }
    catch (std::exception&) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    Direction dir;
    char d = std::toupper(static_cast<unsigned char>(direction));
    if (d == 'H') dir = Direction::Horizontal;
    else if (d == 'V') dir = Direction::Vertical;
    else throw std::logic_error("Invalid input: incorrect ship");

    if (is_collision(size, _position, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
    _direction = dir;
}

Ship::Ship(const std::string& str) {
    parse(str, *this);
}

void Ship::row(int row) {
    try {
        Position new_pos(row, _position.col());
        if (is_collision(_size, new_pos, _direction)) {
            throw std::logic_error("Invalid input: incorrect ship");
        }
        _position = new_pos;
    }
    catch (std::exception&) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

void Ship::col(int col) {
    if (col >= 'A' && col <= 'Z') {
        col = col - 'A' + 1;
    }
    else if (col >= 'a' && col <= 'z') {
        col = col - 'a' + 1;
    }
    try {
        Position new_pos(_position.row(), col);
        if (is_collision(_size, new_pos, _direction)) {
            throw std::logic_error("Invalid input: incorrect ship");
        }
        _position = new_pos;
    }
    catch (std::exception&) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

void Ship::col(char col) {
    try {
        Position new_pos(_position.row(), col);
        if (is_collision(_size, new_pos, _direction)) {
            throw std::logic_error("Invalid input: incorrect ship");
        }
        _position = new_pos;
    }
    catch (std::exception&) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}


void Ship::direction(char direction) {
    Direction dir;
    char d = std::toupper(static_cast<unsigned char>(direction));
    if (d == 'H') dir = Direction::Horizontal;
    else if (d == 'V') dir = Direction::Vertical;
    else throw std::logic_error("Invalid input: incorrect ship");

    if (is_collision(_size, _position, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = dir;
}

Ship& Ship::operator=(const Ship& ship) {
    _size = ship._size;
    _position = ship._position;
    _direction = ship._direction;
    return *this;
}

void parse(const std::string& str, Ship& ship) {
    int row = 0;
    char col = 0;
    char dir = 0;
    Direction direction;
    size_t i = 0;
    int size = 0;
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    while (i < str.size() && std::isdigit(str[i])) {
        size = size * 10 + (str[i] - '0');
        i++;
    }
    if (size == 0) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    if (i < str.size() && std::isalpha(str[i])) {
        dir = str[i];
        if (dir == 'V' || dir == 'v') {
            direction = Direction::Vertical;
        }
        else if (dir == 'H' || dir == 'h') {
            direction = Direction::Horizontal;
        }
        else {
            throw std::logic_error("Invalid input: incorrect ship");
        }
        i++;
        if (str[i] != ' ') {
            throw std::logic_error("Invalid input: incorrect ship");
        }
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    while (i < str.size() && std::isdigit(str[i])) {
        row = row * 10 + (str[i] - '0');
        i++;
    }
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    if (i < str.size() && std::isalpha(str[i])) {
        col = std::toupper(str[i]);
        i++;
    }
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    if (i != str.size()) {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    try {
        ship = Ship(size, Position(row, col), Direction(direction));
    }
    catch (std::exception&) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

bool is_collision(int size, Position position, Direction direction) {
    if (size < 1 || size > 4) {
        return true;
    }

    int start_row = position.row();
    int start_col = position.col();

    try {
        Position start_pos(start_row, start_col);
        if (direction == Direction::Horizontal) {
            Position pos(start_row, start_col + size - 1);
        }
        else if (direction == Direction::Vertical) {
            Position pos(start_row + size - 1, start_col);
        }
    }
    catch (std::exception&) {
        return true;
    }

    return false;
}
