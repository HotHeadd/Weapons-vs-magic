/**
 * @file matrix.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "matrix_iterator.hpp"
#include <memory>
#include <optional>
#include <algorithm>
#include <limits>

namespace WVM{

template <typename T>
concept nonconst = std::is_same_v<std::remove_cvref_t<T>, T>;

/// @brief Шаблонный класс для работы с матрицами.
/// @tparam T Тип элементов матрицы.
template <nonconst T>
class Matrix{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;

    using iterator = MatrixIterator<T, false>;
    using const_iterator = MatrixIterator<T, true>;
    template <bool is_const>
    class RowProxy;

    using const_proxy = RowProxy<true>;
    using non_const_proxy = RowProxy<false>;
    
    /// @brief Конструктор по умолчанию. Создает пустую матрицу.
    Matrix() noexcept;

    /// @brief Конструктор с указанием размеров.
    /// @param rows Количество строк.
    /// @param cols Количество столбцов.
    /// @throws std::invalid_argument Если количество строк или столбцов равно нулю.
    Matrix(size_type  x_size, size_type y_size);

    /// @brief Конструктор с указанием размеров и значением для инициализации.
    /// @param x_size Количество строк.
    /// @param y_size Количество столбцов.
    /// @param value Значение, которым будет заполнена матрица.
    /// @requires Тип элементов должен быть копируемым.
    Matrix(size_type  x_size, size_type y_size, const T& value)
     requires (std::copy_constructible<T>);
    
    /// @brief Конструктор с указанием размеров и массивом для инициализации.
    /// @param arr_rows Количество строк в массиве.
    /// @param arr_columns Количество столбцов в массиве.
    /// @param array Указатель на массив значений для инициализации.
    /// @requires Тип элементов должен быть копируемым.
    Matrix(size_type arr_rows, size_type arr_columns, const T* array)
     requires (std::copy_constructible<T>);
    
    /// @brief Конструктор с итераторами и размерами.
    /// @param i_begin Итератор начала.
    /// @param i_end Итератор конца.
    /// @param rows Количество строк.
    /// @param columns Количество столбцов.
    /// @requires Тип элементов должен быть конструируемым из значения итератора.
    template <std::output_iterator<T> Iter>
    Matrix(Iter i_begin, Iter i_end, size_type rows, size_type columns)
     requires (std::constructible_from<T, std::iter_reference_t<Iter>>);

    /// @brief Конструктор из статического массива.
    /// @param array Двумерный статический массив.
    /// @requires Тип элементов должен быть копируемым.
    template <size_type Rows, size_type Columns>
    Matrix(const T(&array)[Rows][Columns])
     requires (std::copy_constructible<T>);
    
    /// @brief Конструктор из std::array.
    /// @param array std::array из std::array.
    /// @requires Тип элементов должен быть копируемым.
    template <size_type Rows, size_type Columns>
    Matrix(const std::array<std::array<T, Columns>, Rows>& array)
     requires (std::copy_constructible<T>);

    /// @brief Конструктор из списка инициализации.
    /// @param list Список инициализации.
    /// @requires Тип элементов должен быть перемещаемым.
    Matrix(std::initializer_list<std::initializer_list<T>> list)
     requires(std::move_constructible<T>);

    /// @brief Оператор присваивания из списка инициализации.
    /// @param list Список инициализации.
    /// @return Ссылка на текущую матрицу.
    /// @requires Тип элементов должен быть перемещаемым.
    Matrix& operator= (std::initializer_list<T> list)
     requires(std::move_constructible<T>);

    /// @brief Конструктор копирования.
    /// @param other Другая матрица для копирования.
    Matrix(const Matrix& rhs)
     requires (std::copy_constructible<T>);
    
    /// @brief Оператор присваивания копированием.
    /// @param other Другая матрица для копирования.
    /// @return Ссылка на текущую матрицу.
    Matrix& operator =(const Matrix& rhs)
     requires (std::copy_constructible<T>);

    /// @brief Конструктор перемещения.
    /// @param other Другая матрица для перемещения.
    Matrix(Matrix&& rhs) noexcept;

    /// @brief Оператор присваивания перемещением.
    /// @param other Другая матрица для перемещения.
    /// @return Ссылка на текущую матрицу.
    Matrix& operator =(Matrix&& rhs) noexcept;

    ~Matrix() = default;

    /// @brief Возвращает количество строк в матрице.
    /// @return Количество строк.
    size_type rows() const noexcept {return rows_;}

    /// @brief Возвращает максимально допустимое количество строк.
    /// @return Максимально возможное количество строк.
    size_type max_rows() const noexcept {return std::numeric_limits<size_type>::max();}

    /// @brief Возвращает количество столбцов в матрице.
    /// @return Количество столбцов.
    size_type columns() const noexcept {return columns_;}

    /// @brief Возвращает максимально допустимое количество столбцов.
    /// @return Максимально возможное количество столбцов.
    size_type max_columns() const noexcept {return std::numeric_limits<size_type>::max();}
    /// @brief Возвращает указатель на данные матрицы.
    /// @return Указатель на первый элемент матрицы.
    pointer data() const noexcept {return data_.get();}

    /// @brief Проверяет, пуста ли матрица.
    /// @return true, если матрица пуста, иначе false.
    bool empty() const noexcept;

    /// @brief Меняет местами содержимое с другой матрицей.
    /// @param other Другая матрица для обмена.
    void swap(Matrix<T>& other) noexcept;

    /// @brief Очищает содержимое матрицы, делая её пустой.
    void clear() noexcept;

    /// @brief Оператор сравнения на равенство.
    /// @param other Другая матрица для сравнения.
    /// @return true, если матрицы равны (имеют одинаковые размеры и элементы), иначе false.
    bool operator== (const Matrix& other) const;

    /// @brief Заполняет матрицу указанным значением.
    /// @param value Значение для заполнения.
    void fill(const_reference value) noexcept {std::fill(begin(), end(), value);}
    
    /// @brief Заполняет строку указанным значением.
    /// @param index Индекс строки.
    /// @param value Значение для заполнения.
    void fill_row(size_type index, const_reference value);

    /// @brief Заполняет столбец указанным значением.
    /// @param index Индекс столбца.
    /// @param value Значение для заполнения.
    void fill_column(size_type index, const_reference value);

    /// @brief Возвращает итератор на начало данных матрицы.
    /// @return Итератор на первый элемент матрицы.
    iterator begin() noexcept {return iterator(data());}

    /// @brief Возвращает итератор на конец данных матрицы.
    /// @return Итератор за последним элементом матрицы.
    iterator end() noexcept {return iterator(data() + rows_*columns_);}

    /// @brief Возвращает константный итератор на начало данных матрицы.
    // @return Константный итератор на первый элемент матрицы.
    const_iterator cbegin() const noexcept {return const_iterator(data());}

    /// @brief Возвращает константный итератор на конец данных матрицы.
    /// @return Константный итератор за последним элементом матрицы.
    const_iterator cend() const noexcept {return const_iterator(data() + rows_*columns_);}

    /// @brief Вспомогательный класс для работы с отдельной строкой матрицы.
    template <bool is_const>
    class RowProxy{
    public:
        using pr_value_type = std::conditional_t<is_const, const T, T>;
        using pr_reference = std::conditional_t<is_const, const T, T>&;
        using pr_pointer = std::conditional_t<is_const, const T, T>*;
        /// @brief Конструктор прокси-строки.
        /// @param row_data Указатель на данные строки.
        /// @param cols Количество столбцов в строке.
        RowProxy(T* row_data, size_type size): row_data_(row_data), row_size_(size) {}

        /// @brief Оператор доступа к элементу строки.
        /// @param col Индекс столбца.
        /// @return Ссылка на элемент строки.
        [[nodiscard]]
        pr_reference operator[] (size_type index) noexcept{
            return row_data_[index];
        }

        /// @brief Оператор доступа к элементу строки (константный).
        /// @param col Индекс столбца.
        /// @return Константная ссылка на элемент строки.
        [[nodiscard]]
        const pr_reference operator[] (size_type index) const noexcept{
            return row_data_[index];
        }
        
        /// @brief Оператор доступа к элементу строки (константный).
        /// @param col Индекс столбца.
        /// @return Константная ссылка на элемент строки.
        /// @throws std::out_of_range Если индекс выходит за пределы строки.
        [[nodiscard]]
        pr_reference  at(size_type index){
            if (index >= row_size_ or index < 0){
                throw std::out_of_range("Column index out of range");
            }
            return row_data_[index];
        }

        /// @brief Оператор доступа к элементу строки.
        /// @param col Индекс столбца.
        /// @return Ссылка на элемент строки.
        /// @throws std::out_of_range Если индекс выходит за пределы строки.
        [[nodiscard]]
        const pr_reference at(size_type index) const{
            if (index >= row_size_ or index < 0){
                throw std::out_of_range("Column index out of range");
            }
            return row_data_[index];
        }

        /// @brief Заполняет строку указанным значением.
        /// @param value Значение для заполнения.
        void fill(const_reference value) noexcept {std::fill(begin(), end(), value);}

        /// @brief Возвращает итератор на начало данных строки.
        /// @return Итератор на первый элемент строки.
        iterator begin() noexcept {return iterator(row_data_);}

        /// @brief Возвращает итератор на конец данных строки.
        // @return Итератор за последним элементом строки.
        iterator end() noexcept {return iterator(row_data_ + row_size_);}

        /// @brief Возвращает константный итератор на начало данных строки.
        // @return Константный итератор на первый элемент строки.
        const_iterator cbegin() const noexcept {return const_iterator(row_data_);}

        /// @brief Возвращает константный итератор на конец данных строки.
        /// @return Константный итератор за последним элементом строки.
        const_iterator cend() const noexcept {return const_iterator(row_data_ + row_size_);}
    private:
        /// @brief Количество столбцов в строке.
        size_type row_size_;

        /// @brief Указатель на данные строки.
        pr_pointer row_data_;
    };
    
    /// @brief Доступ к строке по индексу.
    /// @param row Индекс строки.
    /// @return прокси-класс строки
    [[nodiscard]]
    non_const_proxy operator[] (const size_type index) noexcept;

    /// @brief Доступ к строке по индексу. (константный)
    /// @param row Индекс строки.
    /// @return прокси-класс строки
    [[nodiscard]]
    const_proxy operator[] (const size_type index) const noexcept;
    
    /// @brief Доступ к строке по индексу.
    /// @param row Индекс строки.
    /// @return прокси-класс строки
    /// @throws std::out_of_range Если индекс выходит за границы матрицы.
    [[nodiscard]]
    non_const_proxy at(const size_type index);

    /// @brief Доступ к строке по индексу.
    /// @param row Индекс строки.
    /// @return прокси-класс строки
    /// @throws std::out_of_range Если индекс выходит за границы матрицы.
    [[nodiscard]]
    const_proxy at(const size_type index) const;

    /// @brief Доступ к элементу по индексу.
    /// @param row Индекс строки.
    /// @param col Индекс столбца.
    /// @return Ссылка на элемент матрицы.
    /// @throws std::out_of_range Если индекс выходит за границы матрицы.
    [[nodiscard]]
    reference at(const size_type row, const size_type column);

    /// @brief Доступ к элементу по индексу (константный).
    /// @param row Индекс строки.
    /// @param col Индекс столбца.
    /// @return Константная ссылка на элемент матрицы.
    /// @throws std::out_of_range Если индекс выходит за границы матрицы.
    [[nodiscard]]
    const_reference at(const size_type row, const size_type column) const;

    /// @brief Доступ к элементу по индексу.
    /// @param row Индекс строки.
    /// @param col Индекс столбца.
    /// @return Ссылка на элемент матрицы.
    [[nodiscard]]
    reference operator() (const size_type row, const size_type column) noexcept;

    /// @brief Доступ к элементу по индексу.
    /// @param row Индекс строки.
    /// @param col Индекс столбца.
    /// @return Ссылка на элемент матрицы.
    [[nodiscard]]
    const_reference operator() (const size_type row, const size_type column) const noexcept;

    /// @brief Находит первый элемент, равный указанному значению.
    /// @param to_find Значение для поиска.
    /// @return Итератор на первый найденный элемент или end(), если элемент не найден.
    [[nodiscard]]
    iterator find(const T& to_find) noexcept{
        return std::find(begin(), end(), to_find);
    }

    /// @brief Находит первый элемент, равный указанному значению (константный).
    /// @param to_find Значение для поиска.
    /// @return Константный итератор на первый найденный элемент или cend(), если элемент не найден.
    [[nodiscard]]
    const_iterator find(const T& to_find) const noexcept{
        return std::find(cbegin(), cend(), to_find);
    }

    /// @brief Изменяет размер матрицы.
    /// @param new_rows Новое количество строк.
    /// @param new_columns Новое количество столбцов.
    void resize(const size_type new_rows, const size_type new_columns);

    /// @brief Изменяет размер матрицы и заполняет новым значением.
    /// @param new_rows Новое количество строк.
    /// @param new_columns Новое количество столбцов.
    /// @param value Значение для заполнения новых элементов.
    void resize_and_fill(const size_type new_rows, const size_type new_columns, const_reference value);

    /// @brief Удаляет строку по указанному индексу.
    /// @param index Индекс строки для удаления.
    /// @throws std::out_of_range Если индекс выходит за границы.
    void erase_row(const size_type row_index);
    /// @brief Удаляет столбец по указанному индексу.
    /// @param index Индекс столбца для удаления.
    /// @throws std::out_of_range Если индекс выходит за границы.
    void erase_column(const size_type column_index);

    /// @brief Вставляет строку в указанную позицию.
    /// @param row_index Индекс строки для вставки.
    /// @param it_b Итератор начала вставляемых элементов.
    /// @param it_e Итератор конца вставляемых элементов.
    /// @requires Тип элементов должен быть конструируемым из значения итератора.
    template <std::output_iterator<T> Iter>
    void insert_row(size_type row_index, Iter it_b, Iter it_e)
     requires std::constructible_from<T, std::iter_reference_t<Iter>>;

    /// @brief Вставляет столбец в указанную позицию.
    /// @param col_index Индекс столбца для вставки.
    /// @param it_b Итератор начала вставляемых элементов.
    /// @param it_e Итератор конца вставляемых элементов.
    /// @requires Тип элементов должен быть конструируемым из значения итератора.
    template <std::output_iterator<T> Iter>
    void insert_column(size_type col_index, Iter it_b, Iter it_e)
     requires std::constructible_from<T, std::iter_reference_t<Iter>>;
    
    /// @brief Вставляет столбец в указанную позицию.
    /// @param index Индекс столбца для вставки.
    /// @param value Значение для заполнения нового столбца.
    /// @throws std::out_of_range Если индекс выходит за границы.

    void insert_row(size_type row_index, const T& value);
    /// @brief Вставляет строку в указанную позицию.
    /// @param index Индекс строки для вставки.
    /// @param value Значение для заполнения новой строки.
    /// @throws std::out_of_range Если индекс выходит за границы.
    void insert_column(size_type col_index, const T& value);

protected:
    /// @brief Количество строк в матрице.
    size_type rows_;

    /// @brief Количество столбцов в матрице.
    size_type columns_;

    /// @brief Указатель на данные матрицы в виде массива.
    std::unique_ptr<T[]> data_;
};

static_assert(std::contiguous_iterator<MatrixIterator<int, true>>);
static_assert(std::contiguous_iterator<MatrixIterator<int, false>>);

template <nonconst T>
Matrix<T>::Matrix() noexcept: rows_(0), columns_(0){
    data_ = nullptr;
}

template <nonconst T>
Matrix<T>::Matrix(size_type  x_size, size_type y_size)
                : rows_(x_size), columns_(y_size) {
    data_ = std::make_unique_for_overwrite<T[]>(rows_*columns_);
}

template <nonconst T>
Matrix<T>::Matrix(size_type  x_size, size_type y_size, const T& value)
            requires (std::copy_constructible<T>): Matrix(x_size, y_size) {
    fill(value);
}

template <nonconst T>
Matrix<T>::Matrix(size_type arr_rows, size_type arr_columns, const T* array)
            requires (std::copy_constructible<T>) : Matrix(arr_rows, arr_columns) {
    for (int i=0; i<rows_; i++){
        for (int j=0; j<columns_; j++){
            data_[i*columns_+j] = array[i*columns_+j];
        }
    }
}


template <nonconst T>
template <size_t Rows, size_t Columns>
Matrix<T>::Matrix(const T(&array)[Rows][Columns])
            requires (std::copy_constructible<T>) : Matrix(Rows, Columns) {
    for (int i=0; i<rows_; i++){
        for (int j=0; j<columns_; j++){
            data_[i*columns_+j] = array[i][j];
        }
    }
}

template <nonconst T>
template <std::output_iterator<T> Iter>
Matrix<T>::Matrix(Iter i_begin, Iter i_end, size_type rows, size_type columns)
     requires (std::constructible_from<T, std::iter_reference_t<Iter>>) : Matrix(rows, columns){
    auto m_iter = begin();
    for (; i_begin < i_end; i_begin++){
        if (m_iter >= end()){
            break;
        }
        *m_iter = *i_begin;
        ++m_iter;
    }
}
template <nonconst T>
template <size_t Rows, size_t Columns>
Matrix<T>::Matrix(const std::array<std::array<T, Columns>, Rows>& array)
            requires (std::copy_constructible<T>) : Matrix(Rows, Columns) {
    size_type i=0;
    for (const auto& row : array){
        for(const auto& elem : row){
            data_[i++] = elem;
        }
    }
}

template <nonconst T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
            requires(std::move_constructible<T>) : Matrix(list.size(), list.begin()->size()) {
    size_type i=0;
    for (const auto& row : list){
        for(const auto& elem : row){
            data_[i++] = std::move(elem);
        }
    }
}
template <nonconst T>
Matrix<T>& Matrix<T>::operator= (std::initializer_list<T> list)
            requires(std::move_constructible<T>){
    data_ = std::make_unique_for_overwrite<T[]>(list.size()*list.begin()->size());    
    rows_ = list.size();
    columns_ = list.begin()->size();
    size_type i=0;
    for (const auto& row : list){
        for(const auto& elem : row){
            data_[i++] = std::move(elem);
        }
    }
}

template <nonconst T>
Matrix<T>::Matrix(const Matrix& rhs) 
            requires (std::copy_constructible<T>) : Matrix(rhs.rows_, rhs.columns_){
    std::copy(rhs.cbegin(), rhs.cend(), begin());
}

template <nonconst T>
Matrix<T>& Matrix<T>::operator =(const Matrix& rhs)
            requires (std::copy_constructible<T>){
    data_ = std::make_unique_for_overwrite<T[]>(rhs.rows_*rhs.columns_);
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    std::copy(rhs.cbegin(), rhs.cend(), begin());
    return *this;
}

template <nonconst T>
Matrix<T>::Matrix(Matrix&& rhs) noexcept {
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    data_ = std::move(rhs.data_);
    rhs.rows_ = 0;
    rhs.columns_ = 0;
}

template <nonconst T>
Matrix<T>& Matrix<T>::operator =(Matrix&& rhs) noexcept{
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    data_ = std::move(rhs.data_);
    rhs.rows_ = 0;
    rhs.columns_ = 0;
    return *this;
}

template <nonconst T>
bool Matrix<T>::operator== (const Matrix& other) const{
    if (rows_ != other.rows_ or columns_ != other.columns_){
        return false;
    }
    return std::equal(cbegin(), cend(), other.cbegin(), other.cend());
}

template <nonconst T>
void Matrix<T>::fill_row(size_type index, const_reference value) {
    if (index >= rows_ or index < 0){
        throw std::out_of_range("Row index out of range");
    }
    (*this)[index].fill(value);
}

template <nonconst T>
void Matrix<T>::fill_column(size_type index, const_reference value) {
    if (index >= columns_ or index < 0){
        throw std::out_of_range("Column index out of range");
    }
    for (int i=0; i<rows_; i++){
        (*this)(i, index) = value;
    }
}

template <nonconst T>
Matrix<T>::non_const_proxy Matrix<T>::operator[](const size_t index) noexcept{
    return non_const_proxy(data()+index*columns_, columns_);
}

template <nonconst T>
Matrix<T>::const_proxy Matrix<T>::operator[](const size_t index) const noexcept{
    return const_proxy(data()+index*columns_, columns_);
}

template <nonconst T>
Matrix<T>::non_const_proxy Matrix<T>::at(const size_t index){
    if (index >= rows_ or index < 0){
        throw std::out_of_range("Row index out of range");
    }
    return non_const_proxy(data()+index*columns_, columns_);
}

template <nonconst T>
Matrix<T>::const_proxy Matrix<T>::at(const size_t index) const{
    if (index >= rows_ or index < 0){
        throw std::out_of_range("Row index out of range");
    }
    return const_proxy(data()+index*columns_, columns_);
}

template <nonconst T>
T& Matrix<T>::at(const size_t row, const size_t column){
    if (row >= rows_ or row < 0){
        throw std::out_of_range("Row index out of range");
    }
    if (column >= columns_ or column < 0){
            throw std::out_of_range("Column index out of range");
    }
    return data_[row*columns_ + column];
}

template <nonconst T>
const T& Matrix<T>::at(const size_t row, const size_t column) const{
    if (row >= rows_ or row < 0){
        throw std::out_of_range("Row index out of range");
    }
    if (column >= columns_ or column < 0){
            throw std::out_of_range("Column index out of range");
    }
    return data_[row*columns_ + column];
}

template <nonconst T>
T& Matrix<T>::operator() (const size_t row, const size_t column) noexcept{
    return data_[row*columns_ + column];
}

template <nonconst T>
const T& Matrix<T>::operator() (const size_t row, const size_t column) const noexcept{
    return data_[row*columns_ + column];
}

template <nonconst T>
void Matrix<T>::resize(const size_type new_rows, const size_type new_columns){
    std::unique_ptr<T[]> new_data = std::make_unique_for_overwrite<T[]>(new_rows*new_columns);
    size_type copy_rows = std::min(rows_, new_rows), copy_columns = std::min(columns_, new_columns);
    for (int i=0; i<copy_rows; i++){
        for (int j=0; j<copy_columns; j++){
            new_data[i*new_columns + j] = data_[i*columns_ + j];
        }
    }
    rows_ = new_rows;
    columns_ = new_columns;
    data_ = std::move(new_data);
}

template <nonconst T>
void Matrix<T>::resize_and_fill(const size_type new_rows, const size_type new_columns, const_reference value){
    if (new_rows <= rows_ and new_columns <= columns_){
        resize(new_rows, new_columns);
        return;
    }
    std::unique_ptr<T[]> new_data = std::make_unique_for_overwrite<T[]>(new_rows*new_columns);
    for (int i=0; i<new_rows; i++){
        for (int j=0; j<new_columns; j++){
            if (j < columns_ and i < rows_){
                new_data[i*new_columns + j] = data_[i*columns_ + j];
            }
            else{
                new_data[i*new_columns + j] = value;
            }
        }
    }
    rows_ = new_rows;
    columns_ = new_columns;
    data_ = std::move(new_data);
}

template <nonconst T>
bool Matrix<T>::empty() const noexcept{
    return (rows_ == 0 and columns_ == 0);
}

template <nonconst T>
void Matrix<T>::swap(Matrix<T>& other) noexcept{
    std::swap(data_, other.data_);
    std::swap(rows_, other.rows_);
    std::swap(columns_, other.columns_);
}

template <nonconst T>
void Matrix<T>::clear() noexcept{
    data_ = nullptr;
    rows_ = 0;
    columns_ = 0;
}

template <nonconst T>
void Matrix<T>::erase_row(const size_type row_index){
    if (row_index >= rows_ or row_index < 0){
        throw std::out_of_range("Row index out of range");
    }
    if (rows_ != 0){
        std::unique_ptr<T[]> buffer = std::make_unique_for_overwrite<T[]>((rows_-1)*columns_);
        for (size_t cur_row=0; cur_row < rows_-1; cur_row++){\
            size_t row_ind = cur_row < row_ind ? cur_row : cur_row+1;
            std::copy((*this)[row_ind].begin(), (*this)[row_ind].end(), buffer.get()+cur_row*(columns_));
        }
        --rows_;
        data_ = std::move(buffer);
    }
}

template <nonconst T>
void Matrix<T>::erase_column(const size_type column_index){
    if (column_index >= columns_ or column_index < 0){
        throw std::out_of_range("Column index out of range");
    }
    if (columns_ != 0){
        std::unique_ptr<T[]> buffer = std::make_unique_for_overwrite<T[]>(rows_*(columns_-1));
        for (size_t cur_row=0; cur_row < rows_; cur_row++){\
            for (size_t cur_col=0; cur_col<columns_-1; cur_col++){
                size_t ind = cur_col < column_index ? cur_col : cur_col+1;
                buffer[cur_row*(columns_-1)+cur_col] = (*this)(cur_row, ind);
            }
        }
        --columns_;
        data_ = std::move(buffer);
    }
}

template <nonconst T>
template <std::output_iterator<T> Iter>
void Matrix<T>::insert_row(size_type row_index, Iter it_b, Iter it_e)
            requires std::constructible_from<T, std::iter_reference_t<Iter>>{
    if (row_index > rows_ or row_index < 0){
        throw std::out_of_range("Row index out of range");
    }
    if (rows_ != max_rows()){
        resize(rows_+1, columns_);
    }
    for (size_t c_row=rows_-1; c_row>row_index; c_row--){
        std::copy((*this)[c_row-1].begin(), (*this)[c_row-1].end(), (*this)[c_row].begin());
    }
    std::copy(it_b, it_e, (*this)[row_index].begin());
}

template <nonconst T>
void Matrix<T>::insert_row(size_type row_index, const T& value){
    if (row_index > rows_ or row_index < 0){
        throw std::out_of_range("Row index out of range");
    }
    if (rows_ != max_rows()){
        resize(rows_+1, columns_);
    }
    for (size_t c_row=rows_-1; c_row>row_index; c_row--){
        std::copy((*this)[c_row-1].begin(), (*this)[c_row-1].end(), (*this)[c_row].begin());
    }
    std::fill((*this)[row_index].begin(), (*this)[row_index].end(), value);
}

template <nonconst T>
template <std::output_iterator<T> Iter>
void Matrix<T>::insert_column(size_type col_index, Iter it_b, Iter it_e)
            requires std::constructible_from<T, std::iter_reference_t<Iter>>{
    if (col_index > columns_ or col_index < 0){
        throw std::out_of_range("Column index out of range");
    }
    if (columns_ != max_rows()){
        resize(rows_, columns_+1);
    }
    for (size_t c_row=0; c_row<rows_; c_row++){
        for (size_t c_col=columns_-1; c_col>col_index; c_col--){
            (*this)(c_row, c_col) = (*this)(c_row, c_col-1);
        }
    }
    for (size_t c_row=0; c_row<rows_; c_row++){
        if (it_b >= it_e){
            break;
        }
        (*this)(c_row, col_index) = *it_b;
        ++it_b;
    }
}

template <nonconst T>
void Matrix<T>::insert_column(size_type col_index, const T& value){
    if (col_index > columns_ or col_index < 0){
        throw std::out_of_range("Column index out of range");
    }
    if (columns_ != max_rows()){
        resize(rows_, columns_+1);
    }
    for (size_t c_row=0; c_row<rows_; c_row++){
        for (size_t c_col=columns_-1; c_col>col_index; c_col--){
            (*this)(c_row, c_col) = (*this)(c_row, c_col-1);
        }
    }
    for (size_t c_row=0; c_row<rows_; c_row++){
        (*this)(c_row, col_index) = value;
    }
}

}
