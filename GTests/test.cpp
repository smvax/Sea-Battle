#include "pch.h"
#include "sea.h"

TEST(PositionTest, TestDefaultConstructorAndGetters) {
    Position p;
    EXPECT_EQ(p.row(), 1);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTest, TestInitConstructor) {
    Position p(5, 7);
    EXPECT_EQ(p.row(), 5);
    EXPECT_EQ(p.col(), 7);
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

TEST(PositionTest, TestStringConstructor) {
    Position p("(2, 8)");
    EXPECT_EQ(p.row(), 2);
    EXPECT_EQ(p.col(), 8);
}

TEST(PositionTest, TestDefaultSettersValid) {
    Position p;
    p.row(5);
    p.col(9);
    EXPECT_EQ(p.row(), 5);
    EXPECT_EQ(p.col(), 9);
}
TEST(PositionTest, TestEdgeSettersValid) {
    Position p;
    p.row(0);
    p.col(0);
    EXPECT_EQ(p.row(), 0);
    EXPECT_EQ(p.col(), 0);
    p.row(10);
    p.col(10);
    EXPECT_EQ(p.row(), 10);
    EXPECT_EQ(p.col(), 10);
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
}

TEST(PositionTest, TestInitConstructorInvalid) {
    EXPECT_THROW(Position(-1, 5), std::logic_error);
    EXPECT_THROW(Position(5, -1), std::logic_error);
    EXPECT_THROW(Position(-1, -1), std::logic_error);
    EXPECT_THROW(Position(11, 5), std::logic_error);
    EXPECT_THROW(Position(5, 11), std::logic_error);
    EXPECT_THROW(Position(11, 11), std::logic_error);
}

TEST(PositionTest, TestToStringMethod) {
    Position p(5, 5);
    EXPECT_EQ(to_string(p), "(5, 5)");
}

TEST(PositionTest, TestParseMethod) {
    Position p = parse("(0, 10)");
    EXPECT_EQ(p.row(), 0);
    EXPECT_EQ(p.col(), 10);
}
