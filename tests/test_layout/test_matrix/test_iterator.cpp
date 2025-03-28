#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "matrix.hpp"
#include "matrix_fixtures.hpp"

TEST_F(MatrixTest, iterator_asterisk_increment){
    auto iter = matrix.begin();
    int elem = *iter;
    ASSERT_EQ(elem, 1);
    elem = *(iter++);
    ASSERT_EQ(elem, 1);
    elem = *iter;
    ASSERT_EQ(elem, 2);
    elem = *(++iter);
    ASSERT_EQ(elem, 3);
    *iter = 1234;
    ASSERT_EQ(*iter, 1234);
    auto new_iter = matrix.begin();
    ASSERT_EQ(*new_iter, 1);
    elem = *(new_iter++);
    ASSERT_EQ(elem, 1);
    elem = *new_iter;
    ASSERT_EQ(elem, 2);
    elem = *(++new_iter);
    ASSERT_EQ(elem, 1234);
    new_iter--;
    ASSERT_EQ(*new_iter, 2);
}

TEST_F(MatrixTest, iterator_addition){
    auto iter = matrix.begin();
    iter += 2;
    ASSERT_EQ(*iter, 3);
    auto new_iter = iter + 3;
    ASSERT_EQ(*new_iter, 6);
    new_iter -= 2;
    ASSERT_EQ(*new_iter, 4);
    ASSERT_TRUE(new_iter > iter);
    new_iter -= 1;
    ASSERT_TRUE(iter == new_iter);

    auto iter2 = iter - 2;

    ASSERT_EQ(*iter2, 1);
    ASSERT_EQ(iter - iter2, 2);
    ASSERT_EQ(iter[3], 6);
}

TEST(matrix, iterator_sort){
    Matrix<int> matrix = {{3, 2, 4}, {5, 1, 9}, {8, 6, 7}};
    std::sort(matrix.begin(), matrix.end());
    int i = 1;
    for (auto elem : matrix){
        ASSERT_EQ(elem, i++);
    }
}

TEST_F(MatrixTest, const_iterator){
    auto iter = matrix.begin();
    auto iter2 = matrix.end();
    iter2 = iter;
    auto iter3 = iter;
    auto iter4 = std::move(iter3);
    ASSERT_EQ(iter2, iter);
    ASSERT_EQ(iter4, iter);
    
    auto c_iter = matrix.cbegin();

    auto c_iter_from_c_iter = c_iter;
    ASSERT_EQ(c_iter, c_iter_from_c_iter);

    c_iter_from_c_iter = c_iter;
    ASSERT_EQ(c_iter, c_iter_from_c_iter);

    MatrixIterator<int, true> c_iter_from_nonc_iter = iter;
    ASSERT_EQ(c_iter_from_nonc_iter, iter);

    c_iter_from_nonc_iter = iter;
    ASSERT_EQ(c_iter_from_nonc_iter, iter);

    // MatrixIterator<int, false> nonc_iter_from_c = c_iter;
    //не компилируется, так как нельзя создать из константного неконстантный (не удовлетворяет requires)

}

TEST(matrix, high_load_sort){
    MyRNG rng;
    uint32_t seed;
    rng.seed(seed);
    std::uniform_int_distribution<uint32_t> dist(1, 1000);
    size_t rows=1000, columns=1000;
    Matrix<int> matrix(rows, columns);
    for (auto& elem : matrix){
        elem = dist(rng);
    }
    std::sort(matrix.begin(), matrix.end());
    ASSERT_TRUE(std::is_sorted(matrix.begin(), matrix.end()));
}