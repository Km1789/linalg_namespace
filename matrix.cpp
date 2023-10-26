#include <iostream>
#include "matrix.h"
#include <limits>
using namespace std;

static double eps = 1e-10;

linalg_exseption::linalg_exseption(linalg_exseption_type type, double n1, double n2, int n3, int n4, int n5, int n6)
{
    // Throws an exception depending on what went wrong
    switch(type)
    {
        case linalg_exseption_type::IncorrectDimensionType:
            sprintf(sout_, "One of metrix (%f) is not integer", n1);
            break;
        case linalg_exseption_type::IncorrectDimension:
            sprintf(sout_, "Cannot change matrix dimension to (%d)(%d)", n3, n4);
            break;
        case linalg_exseption_type::NegativeDimension:
            sprintf(sout_, "One of metrix is not positive: (%lf)", n1);
            break;
        case linalg_exseption_type::OutOfScope:
            sprintf(sout_, "Out of Scope (%d, %d) from size (%d, %d)", n3, n4, n5, n6);
            break;
        case linalg_exseption_type::IncorrectIndexType:
            sprintf(sout_, "Attempting to access an element by a non-integer index (%lf)", n1);
            break;
        case linalg_exseption_type::NotInitMatrix:
            sprintf(sout_, "Attempting to do something with an uninitialized matrix");
            break;
        case linalg_exseption_type::IncorrectSizeForSum:
            sprintf(sout_, "Attempting to add two matrices of different sizes: (%d)*(%d) and (%d)*(%d)", n3, n4, n5, n6);
            break;
        case linalg_exseption_type::IncorrectSizeForDifference:
            sprintf(sout_, "Attempting to sub two matrices of different sizes: (%d)*(%d) and (%d)*(%d)", n3, n4, n5, n6);
            break;
        case linalg_exseption_type::IncorrectSizeForMultiplication:
            sprintf(sout_, "Attempting to multiply two matrices of incorrect sizes: (%d)*(%d) and (%d)*(%d)", n3, n4, n5, n6);
            break;
        case linalg_exseption_type::IncorrectSizeForComparsion:
            sprintf(sout_, "Attempting to compare two matrices of different sizes: (%d)*(%d) and (%d)*(%d)", n3, n4, n5, n6);
            break;
        case linalg_exseption_type::IncorrectSizeForTrace:
            sprintf(sout_, "An attempt to take a trace from matrice that are not square: (%d)*(%d)", n3, n4);
            break;
        case linalg_exseption_type::IncorrectSizeForDet:
            sprintf(sout_, "An attempt to take a determinant from matrice that are not square: (%d)*(%d)", n3, n4);
            break;
        case linalg_exseption_type::DivisionByZero:
            sprintf(sout_, "Division by zero: (%lf)/(%lf)", n1, n2);
            break;
        case linalg_exseption_type::NotTrianglMatrix:
            sprintf(sout_, "An attempt to reverse the Gaussian method to a non-triangular matrix: a(%d, %d) != 0", n3, n4);
            break;      
        case linalg_exseption_type::ImpossibleConcat:
            sprintf(sout_, "An attempt to concatenate two matrices with different numbers of rows, first: %d, second: %d", n3, n4);
            break;
        case linalg_exseption_type::NotSquareInvert:
            sprintf(sout_, "An attempt to find the inverse of a non-square matrix: a[%d, %d]", n3, n4);
            break;      
        case linalg_exseption_type::SingMatrixInvert:
            sprintf(sout_, "An attempt to find the inverse of a matrix with zero determinant");
            break;
        case linalg_exseption_type::IncorrectSizeForPower:
            sprintf(sout_, "An attempt to exponentiate a non-square matrix: a[%d, %d]", n3, n4);
            break;
        case linalg_exseption_type::NonCooperativeSystem:
            sprintf(sout_, "This system has more, than one solution");
            break;
        case linalg_exseption_type::NotSquareMinor:
            sprintf(sout_, "An attempt to find a minor for a non-square matrix a[%d, %d]", n3, n4);
            break;
        case linalg_exseption_type::IncorrectInput:
            sprintf(sout_, "Incorrect input to matrix element");
            break;
        case linalg_exseption_type::OutOfScopeRow:
            sprintf(sout_, "An attempt to call to element in index %d column/%d columns", n3, n4);
            break;
        case linalg_exseption_type::NotSquareBilinear:
            sprintf(sout_, "An attempt to expand a non-square bilinear shape: (%d)*(%d)", n3, n4);
            break;
        case linalg_exseption_type::NotCompatibleSystem:
            sprintf(sout_, "This system is not compatible");
            break;
    }
}

const char * linalg_exseption::What()const
{
    // Returns a text description of the exception
    return sout_;
}

linalg::Matrix::Rows::Rows(int a)
{
    // constructot of class Rows
    this->count = a;
    this->row_ptr = nullptr;
}

double &linalg::Matrix::Rows::operator[](int i)
{
    if (i >= this->count)
    {
        throw linalg_exseption(linalg_exseption_type::OutOfScopeRow, 0, 0, i, this->count);
    }
    else if (i < 0)
    {
        throw linalg_exseption(linalg_exseption_type::NegativeDimension, i);
    }
    return this->row_ptr[i];
}

linalg::Matrix::Matrix(double n)
{
    // Creates a matrix with n rows and 1 column
    if (abs(round(n) - n) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimensionType, n);
    }
    else if (n <= 0)
    {
        throw linalg_exseption(linalg_exseption_type::NegativeDimension, n);
    }
    this->m_rows = static_cast<int>(n);
    this->m_columns = 1;
    this->m_ptr = new double[this->m_rows];
    PullZeros();
}

linalg::Matrix::Matrix(double a, double b)
{
    // Creates a matrix with a rows and b columns
    if (abs(round(a) - a) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimensionType, a);
    }
    else if (abs(round(b) - b) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimensionType, b);
    }
    else if (a <= 0)
    {
        throw linalg_exseption(linalg_exseption_type::NegativeDimension, a);
    }
    else if (b <= 0)
    {
        throw linalg_exseption(linalg_exseption_type::NegativeDimension, b);
    }
    this->m_rows = static_cast<int>(a);
    this->m_columns = static_cast<int>(b);
    this->m_ptr = new double[this->m_rows * this->m_columns];
    PullZeros();
}

linalg::Matrix::Matrix(const initializer_list<initializer_list<double>> &data)
{
    // Initialization using initializer_list<initializer_list<double>>
    this->m_rows = static_cast<int>(data.size());
    int i = 0, j = 0;
    for (auto &l : data)
    {
        if (this->m_columns == 0)
        {
            this->m_columns = static_cast<int>(l.size());
            this->m_ptr = new double[this->m_rows * this->m_columns];
            PullZeros();
        }
        for (auto &el : l)
        {
            this->operator()(i, j) = el;
            j += 1;
        }
        i += 1;
        j = 0;
    }
}

linalg::Matrix::Matrix(const initializer_list<double> &data)
{
    // Initialization using initializer_list<double>
    this->m_rows = static_cast<int>(data.size());
    this->m_columns = 1;
    int i = 0, j = 0;
    this->m_ptr = new double[this->m_rows * this->m_columns];
    PullZeros();
    for (auto &l : data)
    {
        this->operator()(i, j) = l;
        i++;
    }
}

void linalg::Matrix::PullZeros()
{
    // Fills a matrix with zeros
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;

    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) = 0;
        }
    }
    *this = m;
}

void linalg::Matrix::CopyOnly(const Matrix &b)
{
    // Function for copying (copy constractor)
    SetZero();
    if (!b.empty())
    {
        this->m_columns = b.m_columns;
        this->m_rows = b.m_rows;
        memcpy(this->m_ptr = new double[this->m_columns * this->m_rows], b.m_ptr, (b.m_columns * b.m_rows) * sizeof(*b.m_ptr));
    }
}

linalg::Matrix::Matrix(const Matrix &b)
{
    // Copy constructor
    CopyOnly(b);
}

linalg::Matrix::Matrix(Matrix &&b)
{
    // Move constructor
    this->m_rows = b.m_rows;
    this->m_columns = b.m_columns;
    this->m_ptr = b.m_ptr;
    b.SetZero();
}

linalg::Matrix& linalg::Matrix::operator=(const Matrix & b)
{
    // Assignment operator
    if (&b != this)
    {
        Clean();
        CopyOnly(b);
    }
    return *this;
}

linalg::Matrix& linalg::Matrix::operator=(Matrix &&b)
{
    // Move assignment operator
    if (&b != this)
    {
        Clean();
        this->m_rows = b.m_rows;
        this->m_columns = b.m_columns;
        this->m_ptr = b.m_ptr;
        b.SetZero();
    }
    return *this; 
}

linalg::Matrix::Rows linalg::Matrix::operator[](int i)
{
    Rows a(this->m_columns);
    a.row_ptr = this->m_ptr + i * this->m_columns;
    return a;
}

double &linalg::Matrix::operator()(double i, double j)
{
    // Operator (i, j)for accessing a matrix element by two indices
    if (abs(round(i) - i) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectIndexType, i);
    }
    else if ((round(j) - j) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectIndexType, j);
    }
    else if (i >= this->m_rows || i < 0)
    {
        throw linalg_exseption(linalg_exseption_type::OutOfScope, 0, 0, i, j, this->m_rows, this->m_columns);
    }
    else if (j >= this->m_columns || j < 0)
    {
        throw linalg_exseption(linalg_exseption_type::OutOfScope, 0, 0, i, j, this->m_rows, this->m_columns);
    }
    return this->m_ptr[static_cast<int>(i) * m_columns + static_cast<int>(j)];
}

const double &linalg::Matrix::operator()(double i, double j)const
{
    // Const operator (i, j)for accessing a matrix element by two indices
    if (abs(round(i) - i) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectIndexType, i);
    }
    else if ((round(j) - j) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectIndexType, j);
    }
    else if (i >= this->m_rows || i < 0)
    {
        throw linalg_exseption(linalg_exseption_type::OutOfScope, 0, 0, i, j, this->m_rows, this->m_columns);
    }
    else if (j >= this->m_columns || j < 0)
    {
        throw linalg_exseption(linalg_exseption_type::OutOfScope, 0, 0, i, j, this->m_rows, this->m_columns);
    }
    return this->m_ptr[static_cast<int>(i) * m_columns + static_cast<int>(j)];
}

linalg::Matrix &&linalg::Matrix::operator+(const Matrix &b)&&
{
    // operator + for Rvalue and Lvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForSum, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) += b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &&>(*this);
}

linalg::Matrix &&linalg::Matrix::operator+(Matrix &&b)&&
{
    // operator + for Rvalue and Rvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForSum, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) += b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &&>(*this);
}

linalg::Matrix &&linalg::Matrix::operator+(Matrix &&b)const&
{
    // operator + for Lvalue and Rvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForSum, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = b;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            b(i, j) += this->operator()(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    b = m;
    return const_cast<Matrix &&>(b);
}

linalg::Matrix linalg::Matrix::operator+(const Matrix &b)const&
{
    // operator + for Lvalue and Lvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForSum, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix t(*this);
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            t(i, j) += b(i, j);
            if (fabs(t(i, j)) < eps)
            {
                t(i, j) = 0;
            }
        }
    }
    return t;
}

linalg::Matrix linalg::Matrix::operator-()const&
{
    // operator unar - for Lvaluex
    Matrix m = *this;
    try
    {
    for (int i = 0; i < this->m_rows; i++)
    {
        for(int j = 0; j < this->m_columns; j++)
        {
            m(i, j) = -1 * m(i, j);
        }
    }
    }
    catch(const std::exception& err)
    {
        std::cerr << err.what() << endl;
    }
    return m;
}

linalg::Matrix linalg::Matrix::operator-()&&
{
    // operator unar - for Rvalue
    Matrix m = *this;
    try
    {
    for (int i = 0; i < this->m_rows; i++)
    {
        for(int j = 0; j < this->m_columns; j++)
        {
            m(i, j) = -1 * m(i, j);
        }
    }
    }
    catch(const std::exception& err)
    {
        std::cerr << err.what() << endl;
    }
    return m;
}

linalg::Matrix &&linalg::Matrix::operator-(const Matrix &b)&&
{
    // operator - for Rvalue and Lvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDifference, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) -= b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &&>(*this);
}

linalg::Matrix &&linalg::Matrix::operator-(Matrix &&b) &&
{
    // operator - for Rvalue and Rvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDifference, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) -= b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &&>(*this);
}

linalg::Matrix &&linalg::Matrix::operator-(Matrix &&b) const &
{
    // operator - for Lvalue and Rvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDifference, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = b;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) = this->operator()(i, j) - b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    b = m;
    return const_cast<Matrix &&>(b);
}

linalg::Matrix linalg::Matrix::operator-(const Matrix &b) const &
{
    // operator - for Lvalue and Lvalue
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDifference, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix t(*this);
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            t(i, j) -= b(i, j);
            if (fabs(t(i, j)) < eps)
            {
                t(i, j) = 0;
            }
        }
    }
    return t;
}

linalg::Matrix &linalg::Matrix::operator+=(const Matrix &b) &
{
    // operator += for Lvalue right operand
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForSum, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) += b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &>(*this);
}

linalg::Matrix &linalg::Matrix::operator+=(Matrix &&b) &
{
    // operator += for Lvalue right operand
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForSum, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) += b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &>(*this);
}

linalg::Matrix& linalg::Matrix::operator++()&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            ++m(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix& linalg::Matrix::operator++()&&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            ++m(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix& linalg::Matrix::operator++(int)&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j)++;
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix& linalg::Matrix::operator++(int)&&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j)++;
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix& linalg::Matrix::operator--()&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            --m(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix& linalg::Matrix::operator--()&&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            --m(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix& linalg::Matrix::operator--(int)&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j)--;
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix& linalg::Matrix::operator--(int)&&
{
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j)--;
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix &linalg::Matrix::operator-=(const Matrix &b) &
{
    // operator -= for Lvalue right operand
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDifference, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) -= b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &>(*this);
}

linalg::Matrix &linalg::Matrix::operator-=(Matrix &&b) &
{
    // operator -= for Lvalue right operand
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDifference, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) -= b(i, j);
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return const_cast<Matrix &>(*this);
}

linalg::Matrix linalg::Matrix::operator*(Matrix &&b) const &
{
    // operator * for Rvalue operand on right
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_columns != b.m_rows)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForMultiplication, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix multiply(this->m_rows, b.m_columns);
    multiply.PullZeros();
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < b.m_columns; j++)
        {
            for (int k = 0; k < this->m_columns; k++)
            {
                multiply(i, j) += this->operator()(i, k) * b(k, j);
                if (fabs(multiply(i, j)) < eps)
                {
                    multiply(i, j) = 0;
                }
            }
        }
    }
    return multiply;
}

linalg::Matrix linalg::Matrix::operator*(Matrix &&b) &&
{
    // operator * for Rvalue operands
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_columns != b.m_rows)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForMultiplication, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix multiply(this->m_rows, b.m_columns);
    multiply.PullZeros();
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < b.m_columns; j++)
        {
            for (int k = 0; k < this->m_columns; k++)
            {
                multiply(i, j) += this->operator()(i, k) * b(k, j);
                if (fabs(multiply(i, j)) < eps)
                {
                    multiply(i, j) = 0;
                }
            }
        }
    }
    return multiply;
}

linalg::Matrix linalg::Matrix::operator*(const Matrix &b) &&
{
    // operator * for Rvalue operand on right
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_columns != b.m_rows)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForMultiplication, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix multiply(this->m_rows, b.m_columns);
    multiply.PullZeros();
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < b.m_columns; j++)
        {
            for (int k = 0; k < this->m_columns; k++)
            {
                multiply(i, j) += this->operator()(i, k) * b(k, j);
                if (fabs(multiply(i, j)) < eps)
                {
                    multiply(i, j) = 0;
                }
            }
        }
    }
    return multiply;
}

linalg::Matrix linalg::Matrix::operator*(const Matrix &b) const &
{
    // operator * for Lvalue operands
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_columns != b.m_rows)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForMultiplication, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix multiply(this->m_rows, b.m_columns);
    multiply.PullZeros();
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < b.m_columns; j++)
        {
            for (int k = 0; k < this->m_columns; k++)
            {
                multiply(i, j) += this->operator()(i, k) * b(k, j);
                if (fabs(multiply(i, j)) < eps)
                {
                    multiply(i, j) = 0;
                }
            }
        }
    }
    return multiply;
}

linalg::Matrix linalg::Matrix::operator*=(const Matrix &b) &
{
    // operator *= for Lvalue and Lvalue operands
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_columns != b.m_rows)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForMultiplication, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix multiply(this->m_rows, b.m_columns);
    multiply.PullZeros();
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < b.m_columns; j++)
        {
            for (int k = 0; k < this->m_columns; k++)
            {
                multiply(i, j) += this->operator()(i, k) * b(k, j);
                if (fabs(multiply(i, j)) < eps)
                {
                    multiply(i, j) = 0;
                }
            }
        }
    }
    *this = multiply;
    return *this;
}

linalg::Matrix linalg::Matrix::operator*=(const Matrix &&b) &
{
    // operator *= for Lvalue and Rvalue operands
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_columns != b.m_rows)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForMultiplication, 0, 0, this->m_rows, this->m_columns, b.m_rows, b.m_columns);
    }
    Matrix multiply(this->m_rows, b.m_columns);
    multiply.PullZeros();
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < b.m_columns; j++)
        {
            for (int k = 0; k < this->m_columns; k++)
            {
                multiply(i, j) += this->operator()(i, k) * b(k, j);
                if (fabs(multiply(i, j)) < eps)
                {
                    multiply(i, j) = 0;
                }
            }
        }
    }
    *this = multiply;
    return *this;
}

linalg::Matrix linalg::Matrix::operator*(const double coef) const &
{
    // operator * for Lvalue matrix and const Lvalue double
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m(*this);
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) *= coef;
            if (fabs(m(i, j)) <= eps)
            {
                m(i, j) = 0;
            }
        }
    }
    return m;
}

linalg::Matrix linalg::Matrix::operator*(const double coef) &&
{
    // operator * for Rvalue matrix and const Lvalue double
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m(*this);
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) *= coef;
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    return m;
}

linalg::Matrix linalg::Matrix::operator*=(const double coef) &
{
    // operator *= for Lvalue matrix and const Lvalue double
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    Matrix m = *this;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            m(i, j) *= coef;
            if (fabs(m(i, j)) < eps)
            {
                m(i, j) = 0;
            }
        }
    }
    *this = m;
    return *this;
}

bool linalg::Matrix::operator==(const Matrix &b) const &
{
    // operator == for const Lvalue matrix and const Lvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 0;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 0;
            }
        }
    }
    return 1;
}

bool linalg::Matrix::operator==(const Matrix &b) &&
{
    // operator == for Rvalue matrix and const Lvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 0;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 0;
            }
        }
    }
    return 1;
}

bool linalg::Matrix::operator==(Matrix &&b) &&
{
    // operator == for Rvalue matrix and Rvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 0;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 0;
            }
        }
    }
    return 1;
}

bool linalg::Matrix::operator==(Matrix &&b) const &
{
    // operator == for const Lvalue matrix and Rvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 0;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 0;
            }
        }
    }
    return 1;
}

bool linalg::Matrix::operator!=(const Matrix &b) const &
{
    // operator == for const Lvalue matrix and const Lvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 1;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 1;
            }
        }
    }
    return 0;
}

bool linalg::Matrix::operator!=(const Matrix &b) &&
{
    // operator == for Rvalue matrix and const Lvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 1;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 1;
            }
        }
    }
    return 0;
}

bool linalg::Matrix::operator!=(Matrix &&b) const &
{
    // operator == for const Lvalue matrix and Rvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 1;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 1;
            }
        }
    }
    return 0;
}

bool linalg::Matrix::operator!=(Matrix &&b) &&
{
    // operator == for Rvalue matrix and Rvalue matrix
    if (this->m_ptr == nullptr || b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    if (this->m_rows != b.m_rows || this->m_columns != b.m_columns)
    {
        return 1;
    }
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            if (fabs(this->operator()(i, j) - b(i, j)) > eps)
            {
                return 1;
            }
        }
    }
    return 0;
}

double linalg::Matrix::norm() const &
{
    // return Frobenius norm (root of the sum of squares of the elements) for Lvalue
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    double r = 0;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            r += this->operator()(i, j) * this->operator()(i, j);
        }
    }
    return sqrt(r);
}

double linalg::Matrix::norm()&&
{
    // return Frobenius norm (root of the sum of squares of the elements) for Rvalue
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    double r = 0;
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            r += this->operator()(i, j) * this->operator()(i, j);
        }
    }
    return sqrt(r);
}

double linalg::Matrix::trace() const &
{
    // return trace for Lvalue squared matrix
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != this->m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForTrace, 0, 0, this->m_rows, this->m_columns);
    }
    double r = 0;
    for (int i = 0; i < this->m_rows; i++)
    {
        r += this->operator()(i, i);
    }
    return r;
}

double linalg::Matrix::trace() &&
{
    // return trace for Rvalue squared matrix
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != this->m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForTrace, 0, 0, this->m_rows, this->m_columns);
    }
    double r = 0;
    for (int i = 0; i < this->m_rows; i++)
    {
        r += this->operator()(i, i);
    }
    return r;
}

double linalg::Matrix::det() const &
{
    // return determinant for Lvalue squared matrix
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != this->m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDet, 0, 0, this->m_rows, this->m_columns);
    }
    Matrix m(*this);
    double d = m_Det(m);
    return d;
}

double linalg::Matrix::det() &&
{
    // return determinant for Rvalue squared matrix
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    else if (this->m_rows != this->m_columns)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForDet,0, 0, this->m_rows, this->m_columns);
    }
    Matrix m(*this);
    double d = m_Det(m);
    return d;
}

linalg::Matrix linalg::Matrix::remove_repeat()&
{
    // removes duplicate rows in a Lvalue matrix
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    int rows = this->m_rows;
    int f = 0;
    Matrix m1 = *this;
    try
    {
        for (int i = 0; i < rows - 1; i++)
        {
            for (int j = i + 1; j < rows; j++)
            {
                for (int k = 0; k < m1.m_columns; k++)
                {
                    if (fabs(m1(i, k) - m1(j, k)) > eps)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 0)
                {
                    for (int g = j; g < rows - 1; g++)
                    {
                        for (int k = 0; k < m1.m_columns; k++)
                        {
                            swap(m1(g, k), m1(g + 1, k));
                        }
                    }
                    rows -= 1;
                }
                f = 0;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    Matrix m(rows, m1.m_columns);
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j) = m1(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix linalg::Matrix::remove_repeat()&&
{
    // removes duplicate rows in a Rvalue matrix
    if (this->m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    int rows = this->m_rows;
    int f = 0;
    Matrix m1 = *this;
    try
    {
        for (int i = 0; i < rows - 1; i++)
        {
            for (int j = i + 1; j < rows; j++)
            {
                for (int k = 0; k < m1.m_columns; k++)
                {
                    if (fabs(m1(i, k) - m1(j, k)) > eps)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 0)
                {
                    for (int g = j; g < rows - 1; g++)
                    {
                        for (int k = 0; k < m1.m_columns; k++)
                        {
                            swap(m1(g, k), m1(g + 1, k));
                        }
                    }
                    rows -= 1;
                }
                f = 0;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    Matrix m(rows, m1.m_columns);
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j) = m1(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix linalg::Matrix::remove_zeros_rows()&
{
    // removes zero rows in a matrix
    int rows = this->m_rows;
    int f = 0;
    Matrix m1 = *this;
    try
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < m1.m_columns; j++)
            {
                if (fabs(m1(i, j)) > eps)
                {
                    f = 1;
                    break;
                }
            }
            if (f == 0)
            {
                for (int k = i; k < rows - 1; k++)
                {
                    for (int j = 0; j < m1.m_columns; j++)
                    {
                        swap(m1(k, j), m1(k + 1, j));
                    }
                }
                rows -= 1;
            }
            f = 0;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    Matrix m(rows, m1.m_columns);
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j) = m1(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix linalg::Matrix::remove_zeros_rows()&&
{
    // removes zero rows in a matrix
    int rows = this->m_rows;
    int f = 0;
    Matrix m1 = *this;
    try
    {
        for (int i = 0; i < rows; i++)
        {

            for (int j = 0; j < m1.m_columns; j++)
            {
                if (fabs(m1(i, j)) > eps)
                {
                    f = 1;
                    break;
                }
            }
            if (f == 0)
            {
                for (int k = i; k < rows - 1; k++)
                {
                    for (int j = 0; j < m1.m_columns; j++)
                    {
                        swap(m1(k, j), m1(k + 1, j));
                    }
                }
                rows -= 1;
            }
            f = 0;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    Matrix m(rows, m1.m_columns);
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            m(i, j) = m1(i, j);
        }
    }
    *this = m;
    return *this;
}

linalg::Matrix linalg::Matrix::gauss_forward()&
{
    // direct stroke of the Gaussian method
    this->remove_repeat();
    this->remove_zeros_rows();
    Matrix m1 = *this;
    int c = min(m1.m_columns, m1.m_rows);
    for (int i = 0; i < c; i++)
    {
        int maxRow = i;
        double maxElem = m1(i, i);
        for (int j = i + 1; j < m1.m_rows; j++)
        {
            if (abs(m1(j, i)) - abs(maxElem) > eps)
            {
                maxElem = m1(j, i);
                maxRow = j;
            }
        }
        if (maxElem == 0)
        {
            continue;
        }
        if (maxRow != i)
        {
            for (int k = 0; k < m1.m_columns; k++)
            {
                swap(m1(i, k), m1(maxRow, k));
            }
        }
        for (int j = i + 1; j < m1.m_rows; j++)
        {
            if (fabs(m1(i, i)) <= eps)
            {
                throw linalg_exseption(linalg_exseption_type::DivisionByZero, m1(j, i), m1(i, i));
            }
            double f = m1(j, i) / m1(i, i);
            for (int k = i; k < m1.m_columns; k++)
            {
                m1(j, k) -= f * m1(i, k);
                if (abs(m1(j, k)) <= eps)
                {
                    m1(j, k) = 0;
                }
            }
        }
    }
    m1.remove_repeat();
    m1.remove_zeros_rows();
    *this = m1;
    return *this;
}

linalg::Matrix linalg::Matrix::gauss_backward()&
{
    // reverse stroke of the Gaussian method
    Matrix m1 = *this;
    m1.remove_zeros_rows();
    m1.remove_repeat();
    m1.remove_zeros_rows();
    for (int i = 0; i < m1.m_columns; i++)
    {
        for (int j = i + 1; j < m1.m_rows; j++)
        {
            if ((m1(j, i)) > eps)
            {
                throw linalg_exseption(linalg_exseption_type::NotTrianglMatrix, 0, 0, j, i);
            }
        }
    }
    int i = m1.m_rows - 1;
    int j = m1.m_columns - 1;
    while (1)
    {
        if ((m1(i, j) != 0) || (m1(i, j) == 0 && j == m1.m_columns - 1))
        {
            j -= 1;
        }
        else
        {
            j += 1;
            double d = m1(i, j);
            for (int k = i - 1; k >= 0; k--)
            {
                if (fabs(d) < eps)
                {
                    throw linalg_exseption(linalg_exseption_type::DivisionByZero, m1(k, j), d);
                }
                double f = m1(k, j) / d;
                for (int g = j; g < m1.m_columns; g++)
                {
                    m1(k, g) -= f * m1(i, g);
                    if (abs(m1(j, k)) <= eps)
                    {
                        m1(j, k) = 0;
                    }
                    if (fabs(m1(k, g)) < eps)
                    {
                        m1(k, g) = 0;
                    }
                }
            }
            j -= 1;
            i -= 1;
        }
        m1.remove_zeros_rows();
        m1.remove_repeat();
        m1.remove_zeros_rows();
        if (i == 0 && j == 0)
        {
            break;
        }
    }
    m1.remove_repeat();
    m1.remove_zeros_rows();
    int s = 0;
    double d = 0;
    for (int i = 0; i < m1.m_rows; i++)
    {
        for (int j = 0; j < m1.m_columns; j++)
        {
            if (fabs(m1(i, j)) > eps && s == 0)
            {
                d = m1(i, j);
                s = 1;
                m1(i, j) = 1;
            }
            else if (fabs(m1(i, j)) > eps && s == 1)
            {
                m1(i, j) = m1(i, j) / d;
            }
        }
        s = 0;
    }
    *this = m1;
    return *this;
}

int linalg::Matrix::rank()
{
    // returns the rank of a matrix
    Matrix m(*this);
        m.gauss_forward();
        int s = 0;
        double d = 0;
        for (int i = 0; i < m.m_rows; i++)
        {
            s = 0;
            for (int j = 0; j < m.m_columns; j++)
            {
                if (fabs(m(i, j)) > eps && s == 0)
                {
                    s = 1;
                    d = m(i, j);
                }
                m(i, j) = m(i, j) / d;
                if (abs(m(i, j)) <= eps)
                {
                    m(i, j) = 0;
                }
            }
        }
        m.remove_repeat();
        return m.rows();
}

linalg::Matrix linalg::invert(const Matrix &a)
{
    // returns the inverse matrix
    if (a.rows() != a.columns())
    {
        throw linalg_exseption(linalg_exseption_type::NotSquareInvert, 0, 0, a.rows(), a.columns());
    }
    else if (fabs(a.det()) < eps)
    {
        throw linalg_exseption(linalg_exseption_type::SingMatrixInvert);
    }
    Matrix e(a.rows(), a.columns());
    for (int i  = 0; i < e.rows(); i++)
    {
        for (int j = 0; j < e.columns(); j++)
        {
            if (i == j)
            {
                e(i, j) = 1;
            }
        }
    }
    Matrix m = concatenate(a, e);
    m.gauss_forward();
    m.gauss_backward();
    Matrix r(a.rows(), a.columns());
    for (int i = 0; i < r.rows(); i++)
    {
        for (int j = 0; j < r.columns(); j++)
        {
            r(i, j) = m(i, r.columns() +  j);
        }
    }
    return r;
}

void linalg::Matrix::SetZero()
{
    // Function for nulling class fields
    this->m_columns = 0;
    this->m_rows = 0;
    this->m_ptr = nullptr;
}

int linalg::Matrix::rows() const
{
    // Returns the number of rows of a matrix
    return this->m_rows;
}

int linalg::Matrix::columns() const
{
    // Returns the number of columns of a matrix
    return this->m_columns;
}

bool linalg::Matrix::empty() const
{
    // Checking the matrix for emptiness
    if (m_rows == 0)
    {
        return 1;
    }
    return 0;
}

void linalg::Matrix::reshape(double rows, double cols)
{
    // Changes the dimension of the matrix
    if (fabs(round(rows) - rows) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimensionType, rows);
    }
    else if (fabs(round(rows) - rows) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimensionType, cols);
    }
    else if ((rows * cols) != (this->m_rows * this->m_columns) || rows < 0 || cols < 0)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimension, 0, cols, rows);
    }
    this->m_columns = static_cast<int>(cols);
    this->m_rows = static_cast<int>(rows);
}

void linalg::Matrix::Clean()
{
    // Function for clearing dynamic memory and clearing class fields
    delete[] this->m_ptr;
    SetZero();
}

void linalg::Matrix::print_matrix()
{
    // Displaying the matrix on the screen
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            cout << this->operator()(i, j) << " ";
        }
        cout << endl;
    }
}

int linalg::Matrix::max_of_matrix() const
{
    // Finds the longest number in a matrix
    int m = 0, k = 0;
    string str;
    Matrix m1 = *this;
    try
    {
        for (int i = 0; i < m1.m_rows; i++)
        {
            for (int j = 0; j < m1.m_columns; j++)
            {
                str = to_string(m1(i, j));
                k = str.length();
                for (int g = k - 1; k >= 0; g--)
                {
                    if (str[g] != '0')
                    {
                        if ((g + 1) > m)
                        {
                            m = g + 1;
                        }
                        break;
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    return m;
}

linalg::Matrix::~Matrix()
{
    // Destructor
    Clean();
}

void linalg::delRowAndCol(Matrix &m, int row, int col, Matrix &m1)
{
    // removes a row and column to search for a determinant
    int move_row = 0;
    int move_col = 0;
    for (int i = 0; i < m.rows() - 1; i++)
    {
        if (i == row)
        {
            move_row = 1;
        }
        move_col = 0;
        for (int j = 0; j < m.rows() - 1; j++)
        {
            if (j == col)
            {
                move_col = 1;
            }
            m1(i, j) = m(i + move_row, j + move_col);
        }
    }
}

double linalg::m_Det(Matrix &m)
{
    // Returns a determinant
    double det = 0;
    int degree = 1;
    if (m.rows() == 1)
    {
        return m(0, 0);
    }
    else if (m.rows() == 2)
    {
        return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
    }
    Matrix m1(m.rows() - 1, m.columns() - 1);
    for (int j = 0; j < m.rows(); j++)
    {
        delRowAndCol(m, 0, j, m1);
        det += (degree * m(0, j) * m_Det(m1));
        degree = -1 * degree;
    }
    m1.Clean();
    return det;
}

linalg::Matrix linalg::operator*(const double coef, const Matrix &b)
{
    // Multiplying a Lvalue number by a Lvalue matrix
    Matrix m(b);
    for (int i = 0; i < b.rows(); i++)
    {
        for (int j = 0; j < b.columns(); j++)
        {
            m(i, j) *= coef;
            if (fabs(m(i, j)) <= eps)
            {
                m(i, j) = 0;
            }
        }
    }
    return m;
}

linalg::Matrix linalg::operator*(const double coef, Matrix &&b)
{
    // Multiplying a Lvalue number by a Rvalue matrix
    Matrix m(b);
    for (int i = 0; i < b.rows(); i++)
    {
        for (int j = 0; j < b.columns(); j++)
        {
            m(i, j) *= coef;
            if (fabs(m(i, j)) <= eps)
            {
                m(i, j) = 0;
            }
        }
    }
    return m;
}

linalg::Matrix linalg::concatenate(const Matrix& a, const Matrix& b)
{
    // Concatenation of two Lvalue matrix
    if (a.rows() != b.rows())
    {
        throw linalg_exseption(linalg_exseption_type::ImpossibleConcat, 0, 0, a.rows(), b.rows());
    }
    Matrix m(a.rows(), a.columns() + b.columns());
    for (int i = 0; i < a.rows(); i++)
    {
        for (int j = 0; j < a.columns(); j++)
        {
            m(i, j) = a(i, j);
        }
    }
    for (int i = 0; i < b.rows(); i++)
    {
        for (int j = 0; j < b.columns(); j++)
        {
            m(i, a.columns() + j) = b(i, j);
        }
    }
    return m;
}

linalg::Matrix linalg::concatenate(Matrix&& a, const Matrix& b)
{
    // Concatenation of Rvalue and Lvalue matrix
    if (a.rows() != b.rows())
    {
        throw linalg_exseption(linalg_exseption_type::ImpossibleConcat, 0, 0, a.rows(), b.rows());
    }
    Matrix m(a.rows(), a.columns() + b.columns());
    for (int i = 0; i < a.rows(); i++)
    {
        for (int j = 0; j < a.columns(); j++)
        {
            m(i, j) = a(i, j);
        }
    }
    for (int i = 0; i < b.rows(); i++)
    {
        for (int j = 0; j < b.columns(); j++)
        {
            m(i, a.columns() + j) = b(i, j);
        }
    }
    return m;
}

linalg::Matrix linalg::concatenate(const Matrix& a, Matrix&& b)
{
    // Concatenation of Lvalue and Rvalue matrix
    if (a.rows() != b.rows())
    {
        throw linalg_exseption(linalg_exseption_type::ImpossibleConcat, 0, 0, a.rows(), b.rows());
    }
    Matrix m(a.rows(), a.columns() + b.columns());
    for (int i = 0; i < a.rows(); i++)
    {
        for (int j = 0; j < a.columns(); j++)
        {
            m(i, j) = a(i, j);
        }
    }
    for (int i = 0; i < b.rows(); i++)
    {
        for (int j = 0; j < b.columns(); j++)
        {
            m(i, a.columns() + j) = b(i, j);
        }
    }
    return m;
}

linalg::Matrix linalg::concatenate(Matrix&& a, Matrix&& b)
{
    // Concatenation of Rvalue and Rvalue matrix
    if (a.rows() != b.rows())
    {
        throw linalg_exseption(linalg_exseption_type::ImpossibleConcat, 0, 0, a.rows(), b.rows());
    }
    Matrix m(a.rows(), a.columns() + b.columns());
    for (int i = 0; i < a.rows(); i++)
    {
        for (int j = 0; j < a.columns(); j++)
        {
            m(i, j) = a(i, j);
        }
    }
    for (int i = 0; i < b.rows(); i++)
    {
        for (int j = 0; j < b.columns(); j++)
        {
            m(i, a.columns() + j) = b(i, j);
        }
    }
    return m;
}

linalg::Matrix linalg::transpose(const Matrix& a)
{
    // Transpose Lvalue matrix
    Matrix m(a.columns(), a.rows());
    for(int i = 0; i < a.rows(); i++)
    {
        for (int j = 0; j < a.columns(); j++)
        {
            m(j, i) = a(i, j);
        }
    }
    return m;
}

linalg::Matrix linalg::transpose(Matrix&& a)
{
    // Transpose Rvalue matrix
    Matrix m(a.columns(), a.rows());
    for(int i = 0; i < a.rows(); i++)
    {
        for (int j = 0; j < a.columns(); j++)
        {
            m(j, i) = a(i, j);
        }
    }
    return m;
}

linalg::Matrix linalg::power(const Matrix& a, int b)
{
    // Raises a Lvalue matrix to a power
    if (a.rows() != a.columns())
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForPower, 0, 0, a.rows(), a.columns());
    }
    Matrix m(a.rows(), a.columns());
    try
    {
        if (b == 0)
        {
            for (int i = 0; i < m.rows(); i++)
            {
                for (int j = 0; j < m.columns(); j++)
                {
                    if (i == j)
                    {
                        m(i, j) = 1;
                    }
                }
            }
            return m;
        }
        m = a;
        for (int i = 1; i < b; i++)
        {
            m = m * a;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    return m;
}

linalg::Matrix linalg::power(Matrix&& a, int b)
{
    // Raises a Rvalue matrix to a power
    if (a.rows() != a.columns())
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectSizeForPower, 0, 0, a.rows(), a.columns());
    }
    Matrix m(a.rows(), a.columns());
    try
    {
        if (b == 0)
        {
            for (int i = 0; i < m.rows(); i++)
            {
                for (int j = 0; j < m.columns(); j++)
                {
                    if (i == j)
                    {
                        m(i, j) = 1;
                    }
                }
            }
            return m;
        }
        m = a;
        for (int i = 1; i < b; i++)
        {
            m = m * a;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    return m;
}

linalg::Matrix linalg::solve(Matrix& a, Matrix& f)
{
    // Solves the system Ax = f
    if (a.rank() != a.rows() && concatenate(a, f).rank() != a.rows())
    {
        throw linalg_exseption(linalg_exseption_type::NonCooperativeSystem);
    }
    Matrix m = concatenate(a, f);
    m.gauss_forward();
    m.gauss_backward();
    Matrix r(f.rows(), 1);
    r.PullZeros();
    double s = 0;
    for (int i = m.rows() - 1; i >= 0; i--)
    {
        s = 0;
        for (int j = i + 1; j < a.columns(); j++)
        {
            s += m(i, j) * f(j, 0);
        }
        r(i, 0) = (m(i, a.columns()) - s) / m(i, i);
        if (abs(r(i, 0)) <= eps)
        {
            r(i, 0) = 0;
        }
    }
    return r;
}

void linalg::solve_vector_view(Matrix& a, Matrix& f)
{
    // Prints silution in vector form
    if (a.rank() != concatenate(a, f).rank())
    {
        throw linalg_exseption(linalg_exseption_type::NotCompatibleSystem);
    }
    Matrix m = concatenate(a, f);
    m.gauss_forward();
    m.gauss_backward();
    int s = 0;
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = i; j < m.columns() - 1; j++)
        {
            if (fabs(m[i][j] - 1) < eps && s == 0)
            {
                cout << "x_" << j + 1 << " = " << m(i, m.columns() - 1) << " ";
                s = 1;
            }
            else if (fabs(m(i, j)) > 0 && s == 1)
            {
                if (fabs(m(i, j) - 1) < eps)
                {
                    cout << "- x_" << j + 1 << " ";
                }
                else
                {
                    cout << "- " << m(i, j) << "x_" << j + 1 << " ";
                }
            }
        }
        s = 0;
        cout << endl;
    }
}

double linalg::minor(Matrix&A, double a, double b)
{
    // Finds minor of element A(i, j)
    if (abs(round(a) - a) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimensionType, a);
    }
    else if (abs(round(b) - b) > eps)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectDimensionType, b);
    }
    else if (a < 0 || b < 0 || a >= A.rows() || b >= A.columns())
    {
        throw linalg_exseption(linalg_exseption_type::OutOfScope, 0, 0, a, b);
    }
    else if (A.rows() != A.columns())
    {
        throw linalg_exseption(linalg_exseption_type::NotSquareMinor, 0, 0, A.rows(), A.columns());
    }
    Matrix minor(A.rows() - 1, A.columns() - 1);
    Matrix m = A;
    try
    {
        int min_row = 0;
        for (int i = 0; i < m.rows(); i++)
        {
            if (i == a)
            {
                continue;
            }
            int min_col = 0;
            for (int j = 0; j < m.columns(); j++)
            {
                if (j == b)
                {
                    continue;
                }
                minor(min_row, min_col) = m(i, j);
                min_col++;
            }
            min_row++;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    return minor.det();
}

void linalg::decomposeBilinearForm(const linalg::Matrix& a)
{
    Matrix m = a;
    if (m.rows() != m.columns())
    {
        throw linalg_exseption(linalg_exseption_type::NotSquareBilinear, 0, 0, m.columns(), m.rows());
    }
    Matrix symmetric(m.rows(), m.columns());
    Matrix skew_symmetric(m.rows(), m.columns());
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            symmetric(i, j) = (1.0 / 2.0) * (m(i, j) + m(j, i));
            skew_symmetric(i, j) = (1.0 / 2.0) * (m(i, j) - m(j, i));
        }
    }
    cout << "symmetric:" << endl;
    cout << symmetric;
    cout << "skew_symmetric:" << endl;
    cout << skew_symmetric;
}

linalg::Matrix linalg::symmetric_part(const linalg::Matrix &b)
{
    Matrix m = b;
    if (m.rows() != m.columns())
    {
        throw linalg_exseption(linalg_exseption_type::NotSquareBilinear, 0, 0, m.columns(), m.rows());
    }
    Matrix symmetric(m.rows(), m.columns());
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            symmetric(i, j) = (1.0 / 2.0) * (m(i, j) + m(j, i));
        }
    }
    return symmetric;
}

linalg::Matrix linalg::skew_symmetric_part(const linalg::Matrix &a)
{
    Matrix m = a;
    if (m.rows() != m.columns())
    {
        throw linalg_exseption(linalg_exseption_type::NotSquareBilinear, 0, 0, m.columns(), m.rows());
    }
    Matrix skew_symmetric(m.rows(), m.columns());
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.columns(); j++)
        {
            skew_symmetric(i, j) = (1.0 / 2.0) * (m(i, j) - m(j, i));
        }
    }
    return skew_symmetric;
}

ostream &linalg::operator<<(ostream &cout, const linalg::Matrix &b)
{
    // Displaying the matrix on the screen
    int m = b.max_of_matrix();
    for (int i = 0; i < b.rows(); i++)
    {
        cout << "|";
        for (int j = 0; j < b.columns(); j++)
        {
            cout << setw(m) << b(i, j) << " ";
        }
        cout << "|";
        cout << endl;
    }
    return cout;
}



istream& linalg::operator>>(istream &cin, linalg::Matrix &b)
{
    if (b.m_ptr == nullptr)
    {
        throw linalg_exseption(linalg_exseption_type::NotInitMatrix);
    }
    cout << "Input matrix:" << endl;
    Matrix m = b;
    double a;
    cin.exceptions(std::ios_base::failbit);
    try
    {
        for (int i = 0; i < m.rows(); i++)
        {
            for (int j = 0; j < m.columns(); j++)
            {
                cin >> a;
                m(i, j) = a;
            }
        }
    }
    catch(std::ios_base::failure const& e)
    {
        throw linalg_exseption(linalg_exseption_type::IncorrectInput);
    }
    b = m;
    return cin;
}

void linalg::help()
{
    // print info about linalg and Matrix
    cout << "======================== HELP ========================" << endl;
    cout << "In the linalg namespace, developed a linear algebra library, allowing you to work with matrices of arbitrary dimensions." << endl;
    cout << "======================================================" << endl;
    cout << "In class Matrix are implemented following constructors, methods, operators and functions:" << endl;
    cout << "---------------------Constructors---------------------"<< endl;
    cout << ">> linalg::Matrix m0; -- default constructor" << endl;
    cout << ">> linalg::Matrix m1(4); -- matrix: 4 rows, 1 column" << endl;
    cout << ">> linalg::Matrix m2(4, 6); -- matrix: 4 rows, 6 columns" << endl;
    cout << ">> linalg::Matrix m3(m1); -- copy constructor" << endl;
    cout << ">> linalg::Matrix m4(std::move(m2)); -- move copy constructor" << endl;
    cout << ">> linalg::Matrix m5 = {{1, 2, 3}, {4, 5, 6}}; -- matrix: 2 rows, 3 columns" << endl;
    cout << ">> linalg::Matrix m6 = {{1, 2, 3, 4, 5, 6}}; -- matrix: 1 row, 6 columns" << endl;
    cout << ">> linalg::Matrix m7 = {1, 2, 3, 4, 5, 6}; -- matrix: 6 rows, 1 column" << endl;
    cout << "------------------------Methods-----------------------" << endl;
    cout << ">> m.PullZeros(); -- fills a matrix with zeros" << endl;
    cout << ">> m.SetZero(); -- makes matrix characteristic zeroes" << endl;
    cout << ">> m.CopyOnly(b); -- copy matrix b to m" << endl;
    cout << ">> m.rows(); -- number of rows" << endl;
    cout << ">> m.columns(); -- number of columns" << endl;
    cout << ">> m.empty(); -- checking the matrix for emptiness" << endl;
    cout << ">> m.reshape(); -- resizing a matrix with the current set of elements" << endl;
    cout << ">> m.Clean(); -- Memory clearing" << endl;
    cout << ">> m.print_matrix(); -- easy displaying the matrix on the screen" << endl;
    cout << ">> m.max_of_matrix(); -- length of the largest number in the matrix" << endl;
    cout << ">> m.norm(); -- norm Frobenius" << endl;
    cout << ">> m.trace(); -- matrix trace" << endl;
    cout << ">> m.det(); -- matrix determinant" << endl;
    cout << ">> m.gauss_forward(); -- direct stroke of the Gaussian method" << endl;
    cout << ">> m.gauss_backward(); -- reverse stroke of the Gaussian method" << endl;
    cout << ">> m.remove_repeat(); -- removing duplicate rows from a matrix" << endl;
    cout << ">> m.remove_zeros_rows(); -- removing zero rows from a matrix" << endl;
    cout << ">> m.rank(); -- matrix rank" << endl;
    cout << "-----------------------Operators----------------------"<< endl;
    cout << ">> m = b; -- copy and move assignments" << endl;
    cout << ">> m(i, j); -- accessing matrix elements by indexes" << endl;
    cout << ">> a + (b + c) + (d + e) + f; -- matrix addition" << endl;
    cout << ">> a - (b - c) - (d - e) - f; -- matrix subtraction" << endl;
    cout << ">> a += (b + c - d); -- add to current matrix" << endl;
    cout << ">> a -= (b + c - d); -- subtract from the current matrix" << endl;
    cout << ">> a * (b + c); -- matrix multiplication" << endl;
    cout << ">> a *= (b + c); -- matrix multiplication on current matrix" << endl;
    cout << ">> a * const; -- multiplying a matrix by a number" << endl;
    cout << ">> const * a; -- multiplying a matrix by a number" << endl;
    cout << ">> a *= (const + const); -- multiplying a matrix by a number to current matrix" << endl;
    cout << ">> a == b; -- checking matrices for equality" << endl;
    cout << ">> a != b; -- checking matrices for inequality" << endl;
    cout << ">> -a; -- unary minus" << endl;
    cout << ">> (a + b)++; -- postfix increment ++" << endl;
    cout << ">> ++(a + b); -- prefix increment ++" << endl;
    cout << ">> (a + b)--; -- postfix increment --" << endl;
    cout << ">> --(a + b); -- prefix increment --" << endl;
    cout << ">> cout << a; -- beautiful display of the matrix on the screen" << endl;
    cout << ">> cin >> a; -- entering a matrix from the keyboard" << endl;
    cout << ">> a(i, j); -- returns element on (i, j) position" << endl;
    cout << ">> a[i][j]; -- returns element on (i, j) position" << endl;
    cout << "-----------------------Functions----------------------" << endl;
    cout << ">> delRowAndCol(m, i, j, m1); -- removes a i row and j column from a matrix m and remembers it in the matrix m1"  << endl;
    cout << ">> m_Det(m); -- determinant of matrix m"  << endl;
    cout << ">> concatenate(a, b); -- concatenates matrices a and b"  << endl;
    cout << ">> transpose(a); -- transposes a matrix"  << endl;
    cout << ">> invert(a); -- finds the inverse of a matrix"  << endl;
    cout << ">> power(a, b); -- raises matrix a to power b"  << endl;
    cout << ">> solve(a, f); -- Solves a system of linear homogeneous equations of the form Ax=f with only one solution"  << endl;
    cout << ">> solve_vector_view(a, f); -- Displays the solution to the Ax=f in vector form"  << endl;
    cout << ">> minor(A, i, j); -- Returns the minor of the matrix A of the element with indices i, j"  << endl;
    cout << ">> decomposeBilinearForm(A); -- Displays the decomposition of a bilinear form into symmetric and skew-symmetric"  << endl;
    cout << ">> symmetric_part(A); -- Returns a symmetric matrix from the decomposition of a bilinear form into symmetric and skew-symmetric"  << endl;
    cout << ">> skew_symmetric_part(A); -- Returns a skew-symmetric matrix from the decomposition of a bilinear form into symmetric and skew-symmetric"  << endl;
    cout << "======================================================" << endl;
}
