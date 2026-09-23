#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>

enum Direction { Horizontal, Vertical };

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

class Ship {
    int _size;
    Position _coord;
    Direction _direction;

    bool is_collision(int, Position, Direction) const noexcept;

public:
    inline int size() const noexcept {
        return _size;
    }
    inline Direction direction() const noexcept {
        return _direction;
    }
    inline int row() const noexcept {
        return _coord.row();
    }
    inline int col() const noexcept {
        return _coord.col();
    }

    Ship() = delete;
    Ship(const Ship&) = delete;
    Ship(int, Position, Direction);
    Ship(int, Position);
    Ship(int, char, int, char);

    void rotate();
};

class GameField {
    char** _field;
    const int _n;   //height (rows count)
    const int _m;   //width (columns count)

    void create();

public:
    GameField();
    GameField(char**, int, int);
    GameField(int, int);
    GameField(const GameField&);

    ~GameField();

    void set(int, char);
    char get(int, char) const;

    friend std::string to_string(const GameField&);
};
