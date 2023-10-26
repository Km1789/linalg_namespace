#pragma once
#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>

using namespace std;

enum linalg_exseption_type
{
    IncorrectDimensionType = 1,
    IncorrectDimension = 2,
    OutOfScope = 3,
    IncorrectIndexType = 4,
    NotInitMatrix = 5,
    NegativeDimension = 6,
    IncorrectSizeForSum = 7,
    IncorrectSizeForDifference = 8,
    IncorrectSizeForMultiplication = 9,
    IncorrectSizeForComparsion = 10,
    IncorrectSizeForTrace = 11,
    IncorrectSizeForDet = 12,
    DivisionByZero = 13,
    NotTrianglMatrix = 14,
    ImpossibleConcat = 15,
    NotSquareInvert = 16,
    SingMatrixInvert = 17,
    IncorrectSizeForPower = 18,
    NonCooperativeSystem = 19,
    NotSquareMinor = 20,
    IncorrectInput = 21,
    OutOfScopeRow = 22,
    NotSquareBilinear = 23,
    NotCompatibleSystem = 24,
};

class linalg_exseption
{
    char sout_[128] = "";
    public:
        linalg_exseption(linalg_exseption_type type, double n1 = 0.0, double n2 = 0.0, int n3 = 0, int n4 = 0, int n5 = 0, int n6 = 0);
        const char * What() const;
};

namespace linalg
{
    class Matrix
    {
        double * m_ptr = nullptr;
        int m_rows = 0;
        int m_columns = 0;
        class Rows
        {
            double *row_ptr = nullptr;
            int count = 0;

        public:
            Rows() = default;

            Rows(int a);

            double &operator[](int i);

            friend Matrix;
        };

        public:
            Matrix()=default;

            Matrix(double n);

            Matrix(double a, double b);

            Matrix(const initializer_list<initializer_list<double>> & data);

            Matrix(const initializer_list<double> & data);

            void PullZeros();

            void CopyOnly(const Matrix &b);

            Matrix(const Matrix& b);

            Matrix(Matrix &&b);

            Matrix& operator=(const Matrix &b);

            Matrix& operator=(Matrix &&b);

            double& operator()(double i, double j);

            const double& operator()(double i, double j)const;

            Rows operator[](int i);

            Matrix &&operator+(const Matrix &b)&&;

            Matrix &&operator+(Matrix &&b)&&;

            Matrix &&operator+(Matrix &&b)const&;

            Matrix operator+(const Matrix &b)const&;

            Matrix &&operator-(const Matrix &b)&&;

            Matrix &&operator-(Matrix &&b)&&;

            Matrix &&operator-(Matrix &&b)const&;

            Matrix operator-(const Matrix &b)const&;

            Matrix operator-()const&;

            Matrix operator-()&&;

            Matrix& operator+=(const Matrix& b)&;

            Matrix& operator+=(Matrix&& b)&;

            Matrix& operator++()&;

            Matrix& operator++()&&;

            Matrix& operator++(int)&;

            Matrix& operator++(int)&&;

            Matrix& operator--()&;

            Matrix& operator--()&&;

            Matrix& operator--(int)&;

            Matrix& operator--(int)&&;

            Matrix& operator-=(const Matrix& b)&;

            Matrix& operator-=(Matrix&& b)&;

            Matrix operator*(Matrix&& b)const&;

            Matrix operator*(Matrix&& b)&&;

            Matrix operator*(const Matrix& b)&&;

            Matrix operator*(const Matrix& b)const &;

            Matrix operator*=(const Matrix& b)&;

            Matrix operator*=(const Matrix&& b)&;

            Matrix operator*(const double coef)const&;

            Matrix operator*(const double coef)&&;

            Matrix operator*=(const double coef)&;

            bool operator==(const Matrix &b)const&;

            bool operator==(const Matrix &b)&&;

            bool operator==(Matrix &&b)&&;

            bool operator==(Matrix &&b)const&;

            bool operator !=(const Matrix &b)const&;

            bool operator !=(const Matrix &b)&&;

            bool operator !=(Matrix &&b)const&;

            bool operator !=(Matrix &&b)&&;

            double norm()const&;

            double norm()&&;

            double trace()const&;

            double trace()&&;

            double det()const&;

            double det()&&;

            Matrix gauss_forward()&;

            Matrix remove_repeat()&;

            Matrix remove_repeat()&&;

            Matrix remove_zeros_rows()&;

            Matrix remove_zeros_rows()&&;

            Matrix gauss_backward()&;

            int rank();

            void SetZero();

            int rows()const;

            int columns()const;

            bool empty()const;

            void reshape(double rows, double cols);

            void Clean();

            void print_matrix();

            int max_of_matrix()const;

            ~Matrix();

            friend ostream & operator<<(ostream &cout, const Matrix &b);
            friend istream& operator>>(istream &cin, linalg::Matrix &b);
    };

    void delRowAndCol(Matrix &m, int row, int col, Matrix &m1);

    double m_Det(Matrix &m);

    Matrix operator*(const double coef, const Matrix &b);

    Matrix operator*(const double coef, Matrix &&b);

    Matrix concatenate(const Matrix& a, const Matrix& b);

    Matrix concatenate(const Matrix& a, Matrix&& b);

    Matrix concatenate(Matrix&& a, const Matrix& b);

    Matrix concatenate(Matrix&& a, Matrix&& b);

    Matrix transpose(const Matrix& a);

    Matrix transpose(Matrix&& a);

    Matrix invert(const Matrix& a);

    Matrix power(const Matrix& a, int b);

    Matrix power(Matrix&& a, int b);

    Matrix solve(Matrix& a, Matrix& f);

    void solve_vector_view(Matrix& a, Matrix& f);

    void decomposeBilinearForm(const Matrix& a);

    Matrix symmetric_part(const Matrix& a);

    Matrix skew_symmetric_part(const Matrix& a);

    double minor(Matrix& A, double a, double b);
    
    ostream& operator<<(ostream &cout, const linalg::Matrix &b);

    istream& operator>>(istream &cin, linalg::Matrix &b);

    void help();
}