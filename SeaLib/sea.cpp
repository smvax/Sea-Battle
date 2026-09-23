#include "sea.h"

const int Position::_max_row(10);
const int Position::_max_col(10);

std::string to_string(const Position& p) {
    std::string result;
    result.append("(");
    result.append(std::to_string(p._row));
    result.append(", ");
    result.append(std::to_string(p._col));
    result.append(")");
    return result;
}

Position parse(const std::string& str) {
    int row, col;
    size_t sep = str.find(", ");
    row = std::stoi(str.substr(1, sep - 1));
    col = std::stoi(str.substr(sep + 2, str.size() - sep - 3));
    return Position(row, col);
}

Position::Position() {
    _row = 1;
    _col = 1;
}
Position::Position(int row, int col) {
    this->row(row);
    this->col(col);
}
Position::Position(const Position& other) {
    _row = other._row;
    _col = other._col;
}
Position::Position(const std::string& str) {
    (*this) = parse(str);
}
