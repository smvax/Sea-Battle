#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>

enum Direction { Horizontal, Vertical };

//---------POSITION

class Position;

std::string to_string(const Position&);
void parse(const std::string&, Position&);
bool is_collision(int);
bool is_collision(char);

class Position {
    int _row;
    int _col;

    static const int _max_row;
    static const int _max_col;

public:
    inline int row() const noexcept {
        return _row;
    }
    inline int col() const noexcept {
        return _col;
    }
    inline int max_row() const noexcept { //for GTests
        return _max_row;
    }
    inline int max_col() const noexcept { //for GTests
        return _max_col;
    }
    inline char char_col() const noexcept {
        return static_cast<char>('A' + _col - 1);
    }
    inline void row(int row) {
        if (is_collision(row)) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _row = row;
    }
    inline void col(int col) {
        if (is_collision(static_cast<char>('A' + col - 1))) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _col = col;
    }
    inline void col(char col) {
        if (is_collision(col)) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _col = std::toupper(col) - 'A' + 1;
    }

    Position();
    Position(int, int);
    Position(int, char);
    Position(const Position&);
    Position(const std::string&);

    friend std::string to_string(const Position&);
    friend void parse(const std::string&, Position&);
    friend bool is_collision(int);
    friend bool is_collision(char);
};

//-----------SHIP

class Ship;

void parse(const std::string&, Ship&);
bool is_collision(int, Position, Direction);

class Ship {
    int _size;
    Position _position;
    Direction _direction;

public:
    Ship() = delete;
    Ship(const Ship&) = delete;
    Ship(int, Position, Direction);
    Ship(int, char, int, char);
    Ship(const std::string&);

    inline int size() const noexcept {
        return _size;
    }
    inline int row() const noexcept {
        return _position.row();
    }
    inline int col() const noexcept {
        return _position.col();
    }
    inline Position position() const noexcept {
        return _position;
    }
    inline Direction direction() const noexcept {
        return _direction;
    }

    inline void size(int size) {
        if (is_collision(size, _position, _direction)) {
            throw std::logic_error("Invalid input: incorrect ship");
        }
        _size = size;
    }

    inline void direction(Direction direction) {
        if (is_collision(_size, _position, direction)) {
            throw std::logic_error("Invalid input: incorrect ship");
        }
        _direction = direction;
    }

    inline void position(Position position) {
        if (is_collision(_size, position, _direction)) {
            throw std::logic_error("Invalid input: incorrect ship");
        }
        _position = position;
    }

    void row(int);
    void col(int);
    void col(char);
    void direction(char);

    friend void parse(const std::string&, Ship&);
    friend bool is_collision(int, Position, Direction);

    Ship& operator=(const Ship&);
};

//-------------------

enum State { Missed, BoatDestroyed, DestroyersDestroyed, CruisersDestroyed, BattleshipDestroyed, Hit };

//---------GAMEFIELD

class GameField {
    char** _field;
    const int _n;   //height (rows count)
    const int _m;   //width (columns count)

public:
    GameField();
    ~GameField();

    void set(const Ship&);
    State set(int, char);
    int check_destroy(int, int);

    friend std::string to_string(const GameField& field, bool show = false);
    friend bool is_collision(const GameField&, const Ship&);
};
