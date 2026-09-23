#include "pch.h"
#include "sea.h"

//-----------POSITION

TEST(PositionTest, TestDefaultConstructorAndGetters) {
    Position p;
    EXPECT_TRUE(p.row() <= p.max_row());
    EXPECT_TRUE(p.row() >= 1);
    EXPECT_TRUE(p.col() <= p.max_col());
    EXPECT_TRUE(p.col() >= 1);
}

TEST(PositionTest, TestGoodInitConstructor) {
    Position p(5, 7);
    EXPECT_EQ(p.row(), 5);
    EXPECT_EQ(p.col(), 7);
}

TEST(PositionTest, TestGoodInitConstructorWithChar) {
    Position p(5, 'A');
    EXPECT_EQ(p.row(), 5);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTest, TestCopyConstructor) {
    Position original(3, 4);
    Position copy(original);
    EXPECT_EQ(copy.row(), 3);
    EXPECT_EQ(copy.col(), 4);
    EXPECT_EQ(original.row(), 3);
    EXPECT_EQ(original.col(), 4);
    EXPECT_NE(&copy, &original);
}

TEST(PositionTest, TestGoodStringConstructor) {
    Position p1("8A");
    EXPECT_EQ(p1.row(), 8);
    EXPECT_EQ(p1.col(), 1);
    Position p2("8 A");
    EXPECT_EQ(p2.row(), 8);
    EXPECT_EQ(p2.col(), 1);
    Position p3("8a");
    EXPECT_EQ(p3.row(), 8);
    EXPECT_EQ(p3.col(), 1);
}

TEST(PositionTest, TestStringConstructorEdges) {
    Position p1("10J");
    EXPECT_EQ(p1.row(), 10);
    EXPECT_EQ(p1.col(), 10);
    Position p2("1 A");
    EXPECT_EQ(p2.row(), 1);
    EXPECT_EQ(p2.col(), 1);
}

TEST(PositionTest, TestDefaultSettersValid) {
    Position p;
    p.row(5);
    p.col(9);
    EXPECT_EQ(p.row(), 5);
    EXPECT_EQ(p.col(), 9);
    p.col('A');
    EXPECT_EQ(p.col(), 1);
    p.col('b');
    EXPECT_EQ(p.col(), 2);
}

TEST(PositionTest, TestEdgeSettersValid) {
    Position p;
    p.row(1);
    p.col(1);
    EXPECT_EQ(p.row(), 1);
    EXPECT_EQ(p.col(), 1);
    p.row(10);
    p.col(10);
    EXPECT_EQ(p.row(), 10);
    EXPECT_EQ(p.col(), 10);
    p.col('J');
    EXPECT_EQ(p.col(), 10);
}


TEST(PositionTest, TestIsCollisionInt) {
    EXPECT_FALSE(is_collision(1));
    EXPECT_FALSE(is_collision(5));
    EXPECT_FALSE(is_collision(10));

    EXPECT_TRUE(is_collision(0));
    EXPECT_TRUE(is_collision(-5));

    EXPECT_TRUE(is_collision(11));
    EXPECT_TRUE(is_collision(100));
}

TEST(PositionTest, TestIsCollisionChar) {
    EXPECT_FALSE(is_collision('A'));
    EXPECT_FALSE(is_collision('E'));
    EXPECT_FALSE(is_collision('J'));

    EXPECT_FALSE(is_collision('a'));
    EXPECT_FALSE(is_collision('j'));

    EXPECT_TRUE(is_collision('K'));
    EXPECT_TRUE(is_collision('Z'));
    EXPECT_TRUE(is_collision('k'));

    EXPECT_TRUE(is_collision('1'));
    EXPECT_TRUE(is_collision('?'));
}


TEST(PositionTest, TestRowSetterInvalid) {
    Position p;
    EXPECT_THROW(p.row(-1), std::logic_error);
    EXPECT_THROW(p.row(11), std::logic_error);
}

TEST(PositionTest, TestColSetterInvalid) {
    Position p;
    EXPECT_THROW(p.col(-1), std::logic_error);
    EXPECT_THROW(p.col(11), std::logic_error);
    EXPECT_THROW(p.col('L'), std::logic_error);
}

TEST(PositionTest, TestInitConstructorInvalid) {
    EXPECT_THROW(Position(-1, 5), std::logic_error);
    EXPECT_THROW(Position(5, -1), std::logic_error);
    EXPECT_THROW(Position(-1, -1), std::logic_error);
    EXPECT_THROW(Position(11, 5), std::logic_error);
    EXPECT_THROW(Position(5, 11), std::logic_error);
    EXPECT_THROW(Position(11, 11), std::logic_error);
}

TEST(PositionTest, TestInitConstructorWithCharInvalid) {
    EXPECT_THROW(Position(-1, 'A'), std::logic_error);
    EXPECT_NO_THROW(Position(5, 'A'));
    EXPECT_THROW(Position(11, 'A'), std::logic_error);
    EXPECT_THROW(Position(5, 'u'), std::logic_error);
    EXPECT_THROW(Position(11, 't'), std::logic_error);
}

TEST(PositionTest, TestToStringMethod) {
    Position p(5, 5);
    EXPECT_EQ(to_string(p), "(5, 5)");
}

TEST(PositionTest, TestGoodParseMethod) {
    Position p;
    parse("8 A", p);
    EXPECT_EQ(p.row(), 8);
    EXPECT_EQ(p.col(), 1);
    parse("8A", p);
    EXPECT_EQ(p.row(), 8);
    EXPECT_EQ(p.col(), 1);
    parse("8a", p);
    EXPECT_EQ(p.row(), 8);
    EXPECT_EQ(p.col(), 1);
    parse("8 a", p);
    EXPECT_EQ(p.row(), 8);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTest, TestParseMethodEdges) {
    Position p;
    parse("10J", p);
    EXPECT_EQ(p.row(), 10);
    EXPECT_EQ(p.col(), 10);
}

//---------------SHIP

TEST(ShipTest, TestGetters) {
    Position pos(4, 5);
    Ship ship(2, pos, Direction::Vertical);

    EXPECT_EQ(ship.size(), 2);
    EXPECT_EQ(ship.row(), 4);
    EXPECT_EQ(ship.col(), 5);
    EXPECT_EQ(ship.position().row(), 4);
    EXPECT_EQ(ship.position().col(), 5);
    EXPECT_EQ(ship.direction(), Direction::Vertical);
}

TEST(ShipTest, TestGoodInitConstructor) {
    Position pos(1, 1);
    Ship ship(3, pos, Direction::Horizontal);

    EXPECT_EQ(ship.size(), 3);
    EXPECT_EQ(ship.position().row(), 1);
    EXPECT_EQ(ship.position().col(), 1);
    EXPECT_EQ(ship.direction(), Direction::Horizontal);
}

TEST(ShipTest, TestGoodInitWithCharConstructor) {
    Ship ship(3, 'H', 1, 'A');

    EXPECT_EQ(ship.size(), 3);
    EXPECT_EQ(ship.row(), 1);
    EXPECT_EQ(ship.col(), 1);
    EXPECT_EQ(ship.direction(), Direction::Horizontal);
}

TEST(ShipTest, TestGoodStringConstructor) {
    Ship ship("3 H 1 A");

    EXPECT_EQ(ship.size(), 3);
    EXPECT_EQ(ship.row(), 1);
    EXPECT_EQ(ship.col(), 1);
    EXPECT_EQ(ship.direction(), Direction::Horizontal);
}

TEST(ShipTest, TestInlineSettersValid) {
    Position pos1(1, 1);
    Position pos2(2, 2);
    Ship ship(1, pos1, Direction::Horizontal);

    ship.size(2);
    EXPECT_EQ(ship.size(), 2);

    ship.direction(Direction::Vertical);
    EXPECT_EQ(ship.direction(), Direction::Vertical);

    ship.position(pos2);
    EXPECT_EQ(ship.row(), 2);
    EXPECT_EQ(ship.col(), 2);
}

TEST(ShipTest, TestDefaultSettersValid) {
    Position pos(1, 1);
    Ship ship(2, pos, Direction::Horizontal);

    ship.row(3);
    EXPECT_EQ(ship.row(), 3);

    ship.col(4);
    EXPECT_EQ(ship.col(), 4);

    ship.col('C');
    EXPECT_EQ(ship.col(), 3);

    ship.direction('V');
    EXPECT_EQ(ship.direction(), Direction::Vertical);
}

TEST(ShipTest, TestAssignmentOperator) {
    Position pos1(1, 1);
    Position pos2(5, 5);
    Ship ship1(3, pos1, Direction::Horizontal);
    Ship ship2(2, pos2, Direction::Vertical);

    ship1 = ship2;

    EXPECT_EQ(ship1.size(), 2);
    EXPECT_EQ(ship1.row(), 5);
    EXPECT_EQ(ship1.col(), 5);
    EXPECT_EQ(ship1.direction(), Direction::Vertical);
}

TEST(ShipTest, TestGoodParseMethod) {
    Position pos(1, 1);
    Ship ship(1, pos, Direction::Horizontal);

    parse("4 V 2 B", ship);

    EXPECT_EQ(ship.size(), 4);
    EXPECT_EQ(ship.row(), 2);
    EXPECT_EQ(ship.col(), 2);
    EXPECT_EQ(ship.direction(), Direction::Vertical);
}

TEST(ShipTest, TestSpecificParseMethod) {
    Position pos(1, 1);
    Ship ship(1, pos, Direction::Horizontal);

    parse("4 v 2 b", ship);
    EXPECT_EQ(ship.size(), 4);
    EXPECT_EQ(ship.row(), 2);
    EXPECT_EQ(ship.col(), 2);
    EXPECT_EQ(ship.direction(), Direction::Vertical);

    parse("4 V 2B", ship);
    EXPECT_EQ(ship.size(), 4);
    EXPECT_EQ(ship.row(), 2);
    EXPECT_EQ(ship.col(), 2);
    EXPECT_EQ(ship.direction(), Direction::Vertical);
}

TEST(ShipTest, TestSettersInvalid) {
    Position pos(9, 9);
    Ship ship(2, pos, Direction::Horizontal);

    Position edge_pos(10, 10);
    EXPECT_THROW(Ship edge_ship(2, edge_pos, Direction::Horizontal), std::logic_error);
    EXPECT_THROW(ship.position(Position(10, 10)), std::logic_error);
}

TEST(ShipTest, TestIsCollision) {
    EXPECT_FALSE(is_collision(1, Position(10, 10), Direction::Horizontal));
    EXPECT_TRUE(is_collision(2, Position(10, 10), Direction::Horizontal));
    EXPECT_TRUE(is_collision(2, Position(10, 10), Direction::Vertical));
    EXPECT_TRUE(is_collision(0, Position(5, 5), Direction::Horizontal));
    EXPECT_TRUE(is_collision(-1, Position(5, 5), Direction::Vertical));
}

TEST(ShipTest, TestConstructorWithCharInvalid) {
    EXPECT_THROW(Ship(3, 'G', 1, 'A'), std::logic_error);
    EXPECT_THROW(Ship(3, 'H', 11, 'A'), std::logic_error);
    EXPECT_THROW(Ship(3, 'H', 1, 'K'), std::logic_error);
    EXPECT_THROW(Ship(5, 'H', 1, 'A'), std::logic_error);
}

TEST(ShipTest, TestStringConstructorInvalid) {
    EXPECT_THROW(Ship("1 G 4 B"), std::logic_error);
    EXPECT_THROW(Ship("1 H 11 B"), std::logic_error);
    EXPECT_THROW(Ship("1 H 4 K"), std::logic_error);
    EXPECT_THROW(Ship("5 H 4 B"), std::logic_error);
}

TEST(ShipTest, TestParseMethodInvalid) {
    Position pos(1, 1);
    Ship ship(1, pos, Direction::Horizontal);

    EXPECT_THROW(parse("1 G 4 B", ship), std::logic_error);
    EXPECT_THROW(parse("1 H 11 B", ship), std::logic_error);
    EXPECT_THROW(parse("1 H 4 K", ship), std::logic_error);
    EXPECT_THROW(parse("5 H 4 B", ship), std::logic_error);
}

TEST(ShipTest, TestParameterizedConstructorInvalid) {
    EXPECT_THROW(Ship(5, Position(1, 1), Direction::Horizontal), std::logic_error);
    EXPECT_THROW(Ship(2, Position(10, 10), Direction::Horizontal), std::logic_error);
}
