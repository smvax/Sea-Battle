#include "pch.h"
#include "sea.h"

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
