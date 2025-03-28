#pragma once

#include <gtest/gtest.h>
#include "matrix.hpp"
#include <random>

using namespace WVM;
using MyRNG = std::mt19937;

class MatrixTest : public testing::Test {
public:
    Matrix<int> matrix;
    void SetUp() override{
        const size_t rows=3, columns=3;
        matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    }
};