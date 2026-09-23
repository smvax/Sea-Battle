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
