#include <gtest/gtest.h>

#include "book.h"


namespace tests {

using namespace birthdays;

class BookTest : public testing::Test {
protected:
    Book e_;  // Empty book.
    Book bb_;

    using Date = std::vector<uint16_t>;

    BookTest() : bb_{
        Person{"michael", "bluth", Date{1967,12,14}},
        Person{"lindsay", "bluth funke", Date{1964,1,31}},
        Person{"gob", "bluth", Date{1965,5,4}},
        Person{"george michael", "bluth", Date{1990,3,3}},
        Person{"maeby", "funke", Date{1990,9,22}},
        Person{"buster", "bluth", Date{1973,9,30}},
        Person{"tobias", "funke", Date{1964,4,4}},
        Person{"george", "bluth sr", Date{1947,8,5}},
        Person{"lucille", "bluth", Date{1948,1,30}}
    } {}
};

// Test constructors.
TEST_F(BookTest, ConstructorTest) {
    EXPECT_EQ(e_.size(), 0);
    EXPECT_EQ(bb_.size(), 9);
    EXPECT_EQ(bb_.ids.size(), 9);
}

// Test appending to book.
TEST_F(BookTest, AppendTest) {
    e_.append(Person{"steve", "holt"});
    EXPECT_EQ(e_.size(), 1);

    // Repeat entry.
    bb_.append(Person{"maeby", "funke", Date{1990,9,22}});
    EXPECT_EQ(bb_.size(), 9);
}

// Test removing from book.
TEST_F(BookTest, RemoveTest) {
    bb_.remove(Person{"buster", "bluth", Date{1973,9,30}});
    EXPECT_EQ(bb_.size(), 8);

    // Entry not in book.
    Person sh{"steve", "holt"};
    e_.remove(sh);
    EXPECT_EQ(e_.size(), 0);
    bb_.remove(sh);
    EXPECT_EQ(bb_.size(), 8);
}

// Test sorting methods.
TEST_F(BookTest, SortTest) {
    bb_.sort(SORT_METHOD::CALENDAR);
    std::vector<size_t> order{8,1,3,6,2,7,4,5,0};
    EXPECT_EQ(bb_.ids, order);

    bb_.sort(SORT_METHOD::LASTNAME);
    order = std::vector<size_t>{5,3,2,8,0,1,7,4,6};
    EXPECT_EQ(bb_.ids, order);

    bb_.update_ages(Date{2024,12,31});
    bb_.sort(SORT_METHOD::AGE);
    order = std::vector<size_t>{3,4,5,0,2,1,6,8,7};
    EXPECT_EQ(bb_.ids, order);

    bb_.sort(SORT_METHOD::AGE, true);
    order = std::vector<size_t>{7,8,6,1,2,0,5,4,3};
    EXPECT_EQ(bb_.ids, order);
}

// Test filtering methods.
TEST_F(BookTest, FilterTest) {
    bb_.filter(FILTER_METHOD::MONTH, 9);
    std::vector<size_t> filtered{4,5};
    EXPECT_EQ(bb_.ids, filtered);

    // Reset to avoid additional filtering.
    bb_.reset_ids();
    bb_.filter(FILTER_METHOD::LASTNAME, 'b');
    filtered = std::vector<size_t>{0,1,2,3,5,7,8};
    EXPECT_EQ(bb_.ids, filtered);

    // Test additional filtering.
    bb_.filter(FILTER_METHOD::FIRSTNAME, 'g');
    filtered = std::vector<size_t>{2,3,7};
    EXPECT_EQ(bb_.ids, filtered);
}

}  // End namespace tests.