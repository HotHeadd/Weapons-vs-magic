#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "matrix.hpp"
#include "matrix_fixtures.hpp"

using namespace WVM;

TEST(matrix_constructor, empty_constructor){
    Matrix<int> m;
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.columns(), 0);
    ASSERT_EQ(m.data(), nullptr);
    ASSERT_TRUE(m.empty());
}

TEST(matrix_constructor, non_initialized_and_general){
    size_t rows=3, columns=3;
    int value = 12;
    Matrix<int> matrix(rows, columns);
    ASSERT_EQ(matrix.rows(), rows);
    ASSERT_EQ(matrix.columns(), columns);

    matrix[2][2] = value;
    auto elem = matrix[2][2];
    ASSERT_EQ(elem, value);  
    
    matrix[2][2] = 123;
    elem = matrix[2][2];
    EXPECT_EQ(elem, 123);
    EXPECT_EQ(matrix(2, 2), 123);

    EXPECT_EQ(matrix.max_rows(), std::numeric_limits<size_t>::max());
    EXPECT_EQ(matrix.max_columns(), std::numeric_limits<size_t>::max());
}

TEST(matrix, out_of_memo){
    size_t rows=3, columns=3;
    Matrix<int> matrix(rows, columns, 2);

    EXPECT_THROW(auto a = matrix.at(2).at(3), std::logic_error);
    EXPECT_THROW(auto a = matrix.at(3), std::logic_error);
    EXPECT_THROW(auto a = matrix.at(3, 2), std::logic_error);
    EXPECT_THROW(auto a = matrix.at(2, 3), std::logic_error);
}

TEST(matrix, constructor_def_value){
    size_t rows=3, columns=3;
    int def_val = 12;
    Matrix<int> matrix(rows, columns, def_val);
    ASSERT_EQ(matrix.rows(), rows);
    ASSERT_EQ(matrix.columns(), columns);
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            EXPECT_EQ(matrix[i][j], def_val);
        }
    }
}

TEST(matrix, iter_constructor){
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    Matrix<int> m(v.begin(), v.end(), 3, 2);

    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.columns(), 2);
    ASSERT_TRUE(std::equal(v.begin(), v.end(), m.begin()));
}

TEST(matrix, constructor_1dArray){
    size_t rows=3, columns=3;
    int array[rows*columns] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<int> matrix(rows, columns, array);
    ASSERT_EQ(matrix.rows(), rows);
    ASSERT_EQ(matrix.columns(), columns);
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            EXPECT_EQ(matrix[i][j], i*columns+j+1);
        }
    }
}

TEST(matrix, constructor_2d_std_arr){
    const size_t rows=3, columns=3;
    std::array<std::array<int, columns>, rows> array = {{{{1, 2, 3}}, {{4, 5, 6}}, {{7, 8, 9}}}};
    Matrix<int> matrix(array);
    ASSERT_EQ(matrix.rows(), rows);
    ASSERT_EQ(matrix.columns(), columns);
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            EXPECT_EQ(matrix[i][j], i*columns+j+1);
        }
    }
}

TEST(matrix, constructor_2d_arr){
    const size_t rows=3, columns=3;
    int array[rows][columns] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> matrix(array);
    ASSERT_EQ(matrix.rows(), rows);
    ASSERT_EQ(matrix.columns(), columns);
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            EXPECT_EQ(matrix[i][j], i*columns+j+1);
        }
    }
}

TEST(matrix, move_constructor_operator){
    const size_t rows=3, columns=3;
    int array[rows][columns] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> matrix1(array);
    Matrix<int> matrix2(array);

    Matrix<int> matrix_c1(std::move(matrix1));
    Matrix<int> matrix_c2(2, 2);
    matrix_c2 = std::move(matrix2);

    ASSERT_EQ(matrix_c1.rows(), rows);
    ASSERT_EQ(matrix_c2.rows(), rows);
    ASSERT_EQ(matrix_c1.columns(), columns);
    ASSERT_EQ(matrix_c2.columns(), columns);

    ASSERT_EQ(matrix1.rows(), 0);
    ASSERT_EQ(matrix2.rows(), 0);
    ASSERT_EQ(matrix1.columns(), 0);
    ASSERT_EQ(matrix2.columns(), 0);

    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            ASSERT_EQ(matrix_c1[i][j], i*columns+j+1);
        }
    }
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            ASSERT_EQ(matrix_c2[i][j], i*columns+j+1);
        }
    }

    ASSERT_EQ(matrix1.data(), nullptr);
    ASSERT_EQ(matrix2.data(), nullptr);
}

TEST(matrix, init_list_constructor){
    const size_t rows=3, columns=3;
    int array[rows][columns] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            ASSERT_EQ(matrix[i][j], array[i][j]);
            ASSERT_EQ(matrix.at(i, j), array[i][j]);
        }
    }
}

TEST(matrix, init_list_assignment){
    Matrix<int> m(2, 2);
    m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const size_t rows=3, columns=3;
    int array[rows][columns] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            ASSERT_EQ(m(i, j), array[i][j]);
            ASSERT_EQ(m(i, j), array[i][j]);
        }
    }
}

TEST(matrix, copy_constructor_assignment){
    Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> matrix_c1(matrix);
    Matrix<int> matrix_c2;
    matrix_c2 = matrix;
    ASSERT_TRUE(std::equal(matrix_c1.begin(), matrix_c1.end(), matrix.begin()));
    ASSERT_TRUE(std::equal(matrix_c2.begin(), matrix_c2.end(), matrix.begin()));
}

TEST_F(MatrixTest, swap){
    Matrix<int> new_m = {{3, 4, 5}};
    matrix.swap(new_m);

    ASSERT_EQ(matrix.rows(), 1);
    ASSERT_EQ(matrix.columns(), 3);
    ASSERT_ANY_THROW(auto a = matrix.at(1, 0));
    ASSERT_EQ(matrix(0, 1), 4);

    ASSERT_EQ(new_m.rows(), 3);
    ASSERT_EQ(new_m.columns(), 3);
}

TEST_F(MatrixTest, clear){
    matrix.clear();
    ASSERT_EQ(matrix.rows(), 0);
    ASSERT_EQ(matrix.columns(), 0);
    ASSERT_EQ(matrix.data(), nullptr);
    ASSERT_TRUE(matrix.empty());
}

TEST_F(MatrixTest, comparing){
    Matrix<int> m_copy = matrix;

    ASSERT_TRUE(m_copy == matrix);
}

TEST_F(MatrixTest, fill){
    matrix.fill(10);
    for (auto& elem : matrix){
        EXPECT_EQ(elem, 10);
    }
}

TEST_F(MatrixTest, fill_row_test){
    matrix.fill_row(1, 10);
    for (auto& elem : matrix[1]){
        EXPECT_EQ(elem, 10);
    }
}

TEST_F(MatrixTest, fill_column_test){
    matrix.fill_column(1, 10);
    for (size_t i=0; i<matrix.rows(); i++){
        for (size_t j=0; j<matrix.columns(); j++){
            if (j==1){
                EXPECT_EQ(matrix(i, j), 10);
            }
            else{
                EXPECT_EQ(matrix(i, j), i*matrix.rows()+j+1);
            }
        }
    }
}

TEST_F(MatrixTest, find_elem){
    auto iter = matrix.find(9);
    auto iter2 = matrix.find(111);
    ASSERT_EQ(*iter, 9);
    *iter = 11;
    ASSERT_EQ(*iter, 11);
    ASSERT_EQ(iter2, matrix.end());
    std::vector<int> v;
    std::array<int, 4> a;
}

TEST_F(MatrixTest, insert_rows){
    std::array<int, 3> new_row = {-4, -5, -6};
    matrix.insert_row(1, new_row.begin(), new_row.end());
    ASSERT_EQ(matrix.rows(), 4);
    ASSERT_EQ(matrix.columns(), 3);
    int ind=0;
    int val=1;
    for (auto& elem : matrix){
        if (ind == 6){
            val -= 3;
        }
        if (ind > 2 and ind < 6){
            ASSERT_EQ(elem, -val);
        }
        else{
            ASSERT_EQ(elem, val);
        }
        ++val;
        ++ind;
    }
}

TEST_F(MatrixTest, insert_row_filled){
    matrix.insert_row(1, -1);
    ASSERT_EQ(matrix.rows(), 4);
    ASSERT_EQ(matrix.columns(), 3);
    int ind=0;
    int val=1;
    for (auto& elem : matrix){
        if (ind > 2 and ind < 6){
            ASSERT_EQ(elem, -1);
        }
        else{
            ASSERT_EQ(elem, val);
            ++val;
        }
        ++ind;
    }
}

TEST_F(MatrixTest, insert_columns) {
    std::array<int, 3> new_col = {-1, -1, -1};
    matrix.insert_column(1, new_col.begin(), new_col.end());
    ASSERT_EQ(matrix.rows(), 3);
    ASSERT_EQ(matrix.columns(), 4);
    for (size_t i=0; i<matrix.rows(); i++){
        for (size_t j=0; j<matrix.columns(); j++){
            if (j==1){
                ASSERT_EQ(matrix(i,j), -1);
            }
            else{
                ASSERT_EQ(matrix(i, j), i*3+j+(j<1));
            }
        }
    }
}

TEST_F(MatrixTest, insert_col_filled){
    matrix.insert_column(1, -1);
    ASSERT_EQ(matrix.rows(), 3);
    ASSERT_EQ(matrix.columns(), 4);
    for (size_t i=0; i<matrix.rows(); i++){
        for (size_t j=0; j<matrix.columns(); j++){
            if (j==1){
                ASSERT_EQ(matrix(i,j), -1);
            }
            else{
                ASSERT_EQ(matrix(i, j), i*3+j+(j<1));
            }
        }
    }
}

TEST_F(MatrixTest, erase_rows){
    matrix.erase_row(1);
    ASSERT_EQ(matrix.rows(), 2);
    ASSERT_EQ(matrix.columns(), 3);
    for (int i=0; i<matrix.rows();i++){
        for (int j=0; j<matrix.columns();j++){
        }
    }

    ASSERT_EQ(matrix(0, 0), 1);
    ASSERT_EQ(matrix(0, 1), 2);
    ASSERT_EQ(matrix(0, 2), 3);
    ASSERT_EQ(matrix(1, 0), 7);
    ASSERT_EQ(matrix(1, 1), 8);
    ASSERT_EQ(matrix(1, 2), 9);
}

TEST_F(MatrixTest, erase_columns) {
    matrix.erase_column(1);
    ASSERT_EQ(matrix.rows(), 3);
    ASSERT_EQ(matrix.columns(), 2);
    ASSERT_EQ(matrix(0, 0), 1);
    ASSERT_EQ(matrix(0, 1), 3);
    ASSERT_EQ(matrix(1, 0), 4);
    ASSERT_EQ(matrix(1, 1), 6);
    ASSERT_EQ(matrix(2, 0), 7);
    ASSERT_EQ(matrix(2, 1), 9);
}

TEST_F(MatrixTest, resize_fill){
    matrix.resize_and_fill(5, 6, 777);
    ASSERT_EQ(matrix.rows(), 5);
    ASSERT_EQ(matrix.columns(), 6);
    int val = 1;
    for (auto i=0; i<matrix.rows(); i++){
        for (auto j=0; j<matrix.columns(); j++){
            if (i<3 and j<3){
                ASSERT_EQ(matrix(i, j), val);
                val++;
            }
            else{
                ASSERT_EQ(matrix[i][j], 777);
            }
        }
    }
}

TEST_F(MatrixTest, throws){
    std::array<int, 3> new_x = {-1, -1, -1};
    EXPECT_THROW(matrix.insert_row(10, new_x.begin(), new_x.end()), std::out_of_range);
    EXPECT_THROW(matrix.insert_column(10, new_x.begin(), new_x.end()), std::out_of_range);
    EXPECT_THROW(matrix.insert_column(10, -1), std::out_of_range);
    EXPECT_THROW(matrix.insert_row(10, -1), std::out_of_range);
    EXPECT_THROW(matrix.erase_column(10), std::out_of_range);
    EXPECT_THROW(matrix.erase_row(10), std::out_of_range);
    EXPECT_THROW(matrix.fill_row(10, -1), std::out_of_range);
    EXPECT_THROW(matrix.fill_column(10, -1), std::out_of_range);
}

TEST_F(MatrixTest, fast_returns){
    matrix.resize_and_fill(2, 2, 2);
    ASSERT_EQ(matrix.rows(), 2);
    ASSERT_EQ(matrix.rows(), 2);

    Matrix<int> new_matrix = {{2, 2}, {2, 3, 3}};
    ASSERT_EQ(matrix.rows(), 2);
    ASSERT_EQ(matrix.rows(), 2);

    std::array<int, 4> new_col = {-1, -1, -1, -1};
    EXPECT_NO_THROW(matrix.insert_column(1, new_col.begin(), new_col.end()));
}