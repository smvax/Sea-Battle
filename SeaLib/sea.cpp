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

//---------GAMEFIELD

GameField::GameField() : _n(10), _m(10) {
    _field = new char* [_n];
    for (int i = 0; i < _n; i++) {
        _field[i] = new char[_m];
        for (int j = 0; j < _m; j++) {
            _field[i][j] = ' ';
        }
    }
}

GameField::~GameField() {
    for (int i = 0; i < _n; i++) {
        delete[] _field[i];
    }
    delete[] _field;
}

void GameField::set(const Ship& ship) {
    if (is_collision(*this, ship)) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    int row = ship.row() - 1;
    int col = ship.col() - 1;
    int size = ship.size();
    Direction dir = ship.direction();

    for (int i = 0; i < size; i++) {
        if (dir == Direction::Horizontal) {
            _field[row][col + i] = '*';
        }
        else {
            _field[row + i][col] = '*';
        }
    }
}

State GameField::set(int row, char col) {
    if (row < 1 || row > _n) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    int colIdx = std::toupper(col) - 'A' + 1;
    if (colIdx < 1 || colIdx > _m) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    int r = row - 1;
    int c = colIdx - 1;

    if (_field[r][c] == '.' || _field[r][c] == 'X') {
        throw std::logic_error("Invalid input: incorrect move");
    }

    if (_field[r][c] == ' ') {
        _field[r][c] = '.';
        return State::Missed;
    }

    if (_field[r][c] == '*') {
        _field[r][c] = 'X';

        int shipSize = check_destroy(r, c);

        switch (shipSize) {
        case 1:  return State::BoatDestroyed;
        case 2:  return State::DestroyersDestroyed;
        case 3:  return State::CruisersDestroyed;
        case 4:  return State::BattleshipDestroyed;
        default: return State::Hit;
        }
    }

    return State::Missed;
}

int GameField::check_destroy(int row, int col) {
    int start_c = col, end_c = col;
    while (start_c > 0 && (_field[row][start_c - 1] == 'X' || _field[row][start_c - 1] == '*')) start_c--;
    while (end_c < _m - 1 && (_field[row][end_c + 1] == 'X' || _field[row][end_c + 1] == '*')) end_c++;

    int start_r = row, end_r = row;
    while (start_r > 0 && (_field[start_r - 1][col] == 'X' || _field[start_r - 1][col] == '*')) start_r--;
    while (end_r < _n - 1 && (_field[end_r + 1][col] == 'X' || _field[end_r + 1][col] == '*')) end_r++;

    int size = 1;
    bool allDestroyed = true;

    if (end_c > start_c) {
        size = end_c - start_c + 1;
        for (int c = start_c; c <= end_c; c++) {
            if (_field[row][c] == '*') {
                allDestroyed = false;
            }
        }
    }
    else if (end_r > start_r) {
        size = end_r - start_r + 1;
        for (int r = start_r; r <= end_r; r++) {
            if (_field[r][col] == '*') {
                allDestroyed = false;
            }
        }
    }
    else {
        size = 1;
        if (_field[row][col] == '*') {
            allDestroyed = false;
        }
    }

    return allDestroyed ? size : 0;
}

std::string to_string(const GameField& field, bool show) {
    std::string result = "  |";

    for (int j = 0; j < field._m; j++) {
        result += (char)('A' + j);
        if (j < field._m - 1) result += ' ';
    }
    result += "|\n";

    result += "  +";
    for (int j = 0; j < field._m * 2 - 1; j++) {
        result += '-';
    }
    result += "+\n";

    for (int i = 0; i < field._n; i++) {
        result += std::to_string(i + 1);
        if (i + 1 < 10) {
            result += ' ';
        }
        result += '|';

        for (int j = 0; j < field._m; j++) {
            char cell = field._field[i][j];
            if (cell == '*' && !show) {
                result += ' ';
            }
            else {
                result += cell;
            }
            if (j < field._m - 1) result += '|';
        }
        result += "|\n";
    }

    result += "  +";
    for (int j = 0; j < field._m * 2 - 1; j++) {
        result += '-';
    }
    result += "+\n";

    return result;
}

bool is_collision(const GameField& field, const Ship& ship) {
    int row = ship.row() - 1;
    int col = ship.col() - 1;
    int size = ship.size();
    Direction dir = ship.direction();

    if (row < 0 || row >= field._n || col < 0 || col >= field._m || size < 1) {
        return true;
    }

    if (dir == Direction::Horizontal) {
        if (col + size > field._m) return true;
    }
    else {
        if (row + size > field._n) return true;
    }

    int min_r = row - 1;
    int max_r = (dir == Direction::Vertical) ? (row + size) : (row + 1);
    int min_c = col - 1;
    int max_c = (dir == Direction::Horizontal) ? (col + size) : (col + 1);

    for (int r = min_r; r <= max_r; r++) {
        for (int c = min_c; c <= max_c; c++) {
            if (r >= 0 && r < field._n && c >= 0 && c < field._m) {
                if (field._field[r][c] == '*' || field._field[r][c] == 'X') {
                    return true;
                }
            }
        }
    }

    return false;
}
