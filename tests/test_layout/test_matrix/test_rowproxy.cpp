#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "matrix.hpp"
#include "matrix_fixtures.hpp"

TEST_F(MatrixTest, proxy_class){
    int second_row[3] = {4, 5, 6};
    auto row = matrix[1];
    auto elem = row[1];

    ASSERT_TRUE(std::equal(row.begin(), row.end(), second_row));
    ASSERT_THROW(auto a = row.at(3), std::out_of_range);
    ASSERT_EQ(elem, second_row[1]);
    row[1] = 2;
    elem = row[1];
    ASSERT_EQ(elem, 2);
}


TEST_F(MatrixTest, const_proxy_class){
    int second_row[3] = {4, 5, 6};
    const Matrix<int> c_matrix = matrix;
    auto row = c_matrix[1];
    auto elem = row[1];

    ASSERT_TRUE(std::equal(row.cbegin(), row.cend(), second_row));
    ASSERT_THROW(auto a = row.at(3), std::out_of_range);
    ASSERT_EQ(elem, second_row[1]);
    // row[1] = 2; // не компилируется
}