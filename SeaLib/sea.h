#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

enum Direction { Horizontal, Vertical };

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
    inline void row(int row) {
        if (row > _max_row || row < 0) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _row = row;
    }
    inline void col(int col) {
        if (col > _max_col || col < 0) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _col = col;
    }

    Position();
    Position(int, int);
    Position(const Position&);
    Position(const std::string&);

    friend std::string to_string(const Position&);
    friend Position parse(const std::string&);
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
