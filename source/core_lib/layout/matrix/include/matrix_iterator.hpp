#pragma once

#include <iterator>

namespace WVM
{

/// @brief Итератор для доступа к элементам матрицы.
/// @tparam T Тип элементов матрицы.
/// @tparam is_const Указывает, является ли итератор константным.
template <typename T, bool is_const>
class MatrixIterator{
public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::conditional_t<is_const, const T, T>;
    using reference = std::conditional_t<is_const, const T, T>&;
    using pointer = std::conditional_t<is_const, const T, T>*;
    using iterator_category = std::contiguous_iterator_tag;
    
    /// @brief Конструктор по умолчанию.
    /// @param ptr Указатель на начало данных (по умолчанию nullptr).
    MatrixIterator(pointer ptr=nullptr) noexcept : ptr_(ptr) {}

    /// @brief Конструктор копирования из итератора с другим признаком константности.
    /// @tparam other_const Константность другого итератора.
    /// @param other Другой итератор для копирования.
    template <bool other_const>
    MatrixIterator(const MatrixIterator<T, other_const>& other) noexcept 
    requires(is_const >= other_const) : ptr_(other.ptr_) {}
    
    /// @brief Оператор присваивания из итератора с другим признаком константности.
    /// @tparam other_const Константность другого итератора.
    /// @param other Другой итератор для присваивания.
    /// @return Ссылка на текущий итератор.
    template <bool other_const>
    MatrixIterator& operator= (const MatrixIterator<T, other_const>& other) noexcept
    requires(is_const >= other_const){
        ptr_ = other.ptr_;
        return *this;
    }

    /// @brief Доступ к значению, на которое указывает итератор.
    /// @return Ссылка на элемент.
    reference operator* () const {return *ptr_;}

    /// @brief Доступ к указателю на значение, на которое указывает итератор.
    /// @return Указатель на элемент.
    pointer operator-> () const {return ptr_;}

    /// @brief Доступ к элементу по смещению относительно итератора.
    /// @param n Смещение.
    /// @return Ссылка на элемент.
    reference operator [](difference_type n) const noexcept{
        return ptr_[n];
    }

    /// @brief Префиксный оператор инкремента.
    /// @return Ссылка на текущий итератор.
    MatrixIterator& operator++ () noexcept{
        ptr_++;
        return *this;
    }

    /// @brief Постфиксный оператор инкремента.
    /// @return Копия итератора до инкремента.
    MatrixIterator operator++ (int) noexcept{
        auto old = *this;
        ptr_++;
        return old;
    }

    /// @brief Префиксный оператор декремента.
    /// @return Ссылка на текущий итератор.
    MatrixIterator& operator-- () noexcept{
        ptr_--;
        return *this;
    }

    /// @brief Постфиксный оператор декремента.
    /// @return Копия итератора до декремента.
    MatrixIterator operator-- (int) noexcept{
        auto old = *this;
        ptr_--;
        return old;
    }

    /// @brief Оператор сложения со смещением.
    /// @param n Смещение.
    /// @return Ссылка на текущий итератор.
    MatrixIterator& operator+= (difference_type n) noexcept{
        ptr_ += n;
        return *this;
    }

    /// @brief Оператор вычитания смещения.
    /// @param n Смещение.
    /// @return Ссылка на текущий итератор.
    MatrixIterator& operator-= (difference_type n) noexcept{
        ptr_ -= n;
        return *this;
    }

    /// @brief Трехсторонний оператор сравнения.
    /// @param lhs Левый операнд.
    /// @param rhs Правый операнд.
    /// @return Результат сравнения.
    friend std::strong_ordering operator<=> (const MatrixIterator& lhs, const MatrixIterator& rhs) 
    noexcept {return lhs.ptr_ <=> rhs.ptr_;}

    /// @brief Оператор равенства.
    /// @param lhs Левый операнд.
    /// @param rhs Правый операнд.
    /// @return true, если итераторы указывают на одно и то же место, иначе false.
    friend bool operator== (const MatrixIterator& lhs, const MatrixIterator& rhs) 
    noexcept {return (lhs <=> rhs) == 0;}

    /// @brief Оператор сложения итератора и смещения.
    /// @param iter Итератор.
    /// @param n Смещение.
    /// @return Новый итератор с примененным смещением.
    friend MatrixIterator operator+ (MatrixIterator iter, difference_type n) noexcept{
        iter += n;
        return iter;
    }

    /// @brief Оператор сложения смещения и итератора.
    /// @param n Смещение.
    /// @param iter Итератор.
    /// @return Новый итератор с примененным смещением.
    friend MatrixIterator operator+ (difference_type n, MatrixIterator iter) noexcept{
        return iter + n;
    }

    /// @brief Оператор вычитания смещения из итератора.
    /// @param iter Итератор.
    /// @param n Смещение.
    /// @return Новый итератор с примененным смещением.
    friend MatrixIterator operator- (MatrixIterator iter, difference_type n) noexcept{
        iter -= n;
        return iter;
    }

    /// @brief Оператор разницы двух итераторов.
    /// @param lhs Левый операнд.
    /// @param rhs Правый операнд.
    /// @return Смещение между двумя итераторами.
    friend difference_type operator- (const MatrixIterator& lhs, const MatrixIterator& rhs) noexcept{
        return lhs.ptr_ - rhs.ptr_;
    }

private:
    pointer ptr_; ///< Указатель на текущий элемент.
    friend MatrixIterator<T, !is_const>;
};

} // namespace WVM


