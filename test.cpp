#include <iostream>
#include "matrix.h"
#include "test.h"
using namespace std;

static double eps = 1e-10;

void test_constructors()
{
    cout << "-------- TEST CONSTRUCTORS --------" << endl;
    linalg::Matrix m1(4);
    linalg::Matrix m2(4, 6);
    linalg::Matrix m3(m1);
    linalg::Matrix m5 = {{1, 2, 3}, {4, 5, 6}};
    linalg::Matrix m6 = {{1, 2, 3, 4, 5, 6}};
    linalg::Matrix m7 = {1, 2, 3, 4, 5, 6};
    cout << "linalg::Matrix m1(4)" << endl;
    cout << "4 rows and 1 column:" << endl;
    cout << m1;
    cout << "linalg::Matrix m2(4, 6)" << endl;
    cout << "4 rows and 6 columns:" << endl;
    cout << m2;
    cout << "linalg::Matrix m3(m1)" << endl;
    cout << "Copied matrix with 4 rows and 1 column:" << endl;
    cout << m3;
    cout << "linalg::Matrix m4(std::move(m2))" << endl;
    linalg::Matrix m4(std::move(m2));
    cout << "Move-copied matrix with 4 rows and 6 columns:" << endl;
    cout << m4;
    cout << "linalg::Matrix m5 = {{1, 2, 3}, {4, 5, 6}}" << endl;
    cout << "Matrix with 2 rows and 3 columns initialized like {{1, 2, 3}, {4, 5, 6}}:" << endl;
    cout << m5;
    cout << "linalg::Matrix m6 = {{1, 2, 3, 4, 5, 6}}" << endl;
    cout << "Matrix with 1 row and 6 columns initialized like {{1, 2, 3, 4, 5, 6}}:" << endl;
    cout << m6;
    cout << "linalg::Matrix m7 = {1, 2, 3, 4, 5, 6}" << endl;
    cout << "Matrix with 6 rows and 1 columns initialized like {1, 2, 3, 4, 5, 6}:" << endl;
    cout << m7;
    cout << "We can not create matrix with negative or not digit dimension:" << endl;
    cout << "linalg::Matrix m8(-4, 5)" << endl;
    linalg::Matrix m8(-4, 5);
    cout << "------ END TEST CONSTRUCTORS ------" << endl;
}

void test_constructors_not_digit()
{
    cout << "-------- TEST CONSTRUCTORS 2 --------" << endl;
    linalg::Matrix m1(5, 5);
    cout << "linalg::Matrix m1(5, 5)" << endl;
    cout << "Matrix m1:" << endl;
    cout << m1;
    cout << "We can create matrix of different dimensions, but we can not create matrix with not digit dimension" << endl;
    cout << "linalg::Matrix m1(5.5, 6.3)" << endl;
    linalg::Matrix m2(5.5, 6.3);
    cout << "------ END TEST CONSTRUCTORS 2------" << endl;
}

void test_copy_and_indexes()
{
    cout << "---------- TEST ASSIGNMENT AND INDEXING ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "Matrix m1:" << endl;
    cout << m1;
    cout << "Matrix m2:" << endl;
    cout << m2;
    m2 = m1;
    cout << "m2 = m1" << endl;
    cout << "Matrix m1:" << endl;
    cout << m1;
    cout << "Matrix m2:" << endl;
    cout << m2;
    cout << "m2 = {{7, 8, 9}, {10, 11, 12}}" << endl;
    m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "Matrix m2:" << endl;
    cout << m2;
    cout << "m1 = move(m2)" << endl;
    m1 = move(m2);
    cout << "Matrix m1:" << endl;
    cout << m1;
    cout << "m1(1, 1) = " << m1(1, 1) << endl;
    cout << "Do m1(1, 1) = 100" << endl;
    m1(1, 1) = 100;
    cout << "m1(1, 1) = " << m1(1, 1) << endl;
    const linalg::Matrix c_m = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    cout << "Const matrix c_m:" << endl;
    cout << c_m;
    cout << "c_m(1, 2) = " << c_m(1, 2) << endl;
    cout <<  "Incorrect index: c_m(5, 5)" << endl;
    cout << c_m(5, 5) << endl;
    cout << "-------- END TEST ASSIGNMENT AND INDEXING --------" << endl;
}

void test_plus()
{
    cout << "---------- TEST PLUS OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    linalg::Matrix m3 = {{20, 21, 22}, {23, 24, 25}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "m1 + m2: " << endl;
    cout << m1 + m2;
    cout << "We see that m1 m2 did not changed:" << endl;
    cout << "m1: " << endl;
    cout << m1;
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 + m2 + m3: " << endl;
    cout <<  m1 + m2 + m3;
    cout << "(m1 + m2) + m3 + (m2 + m3): " << endl;
    cout << (m1 + m2) + m3 + (m2 + m3);
    linalg::Matrix m4 = {{20, 21, 22, 23}, {24, 25, 26, 27}};
    cout << "m4: " << endl;
    cout << m4;
    cout << "We can not add matrix of different dimesion:" << endl;
    cout << "m1 + m4: " << endl;
    cout << m1 + m4;
    cout << "-------- END TEST PLUS OPERATOR --------" << endl;
}

void test_to_cur_plus()
{
    cout << "---------- TEST PLUS TO CURRENT OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    linalg::Matrix m3 = {{20, 21, 22}, {23, 24, 25}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "m1 += m2: " << endl;
    m1 += m2;
    cout << m1;
    cout << "We see that m1 changed, but m2 did not changed:" << endl;
    cout << "m1: " << endl;
    cout << m1;
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 += m2 + m3: " << endl;
    m1 += m2 + m3;
    cout <<  m1;
    cout << "m2 += (m2 + m3) + m1: " << endl;
    m2 += (m2 + m3) + m1;
    cout << m2;
    linalg::Matrix m4 = {{20, 21, 22, 23}, {24, 25, 26, 27}};
    cout << "m4: " << endl;
    cout << m4;
    cout << "We can not add matrix of different dimesion:" << endl;
    cout << "m1 += m4: " << endl;
    m1 += m4;
    cout << m1;
    cout << "-------- END TEST PLUS TO CURRENT OPERATOR --------" << endl;
}

void test_minus()
{
    cout << "---------- TEST MINUS OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    linalg::Matrix m3 = {{20, 21, 22}, {23, 24, 25}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "m1 - m2: " << endl;
    cout << m1 - m2;
    cout << "We see that m1 m2 did not changed:" << endl;
    cout << "m1: " << endl;
    cout << m1;
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 - m2 - m3: " << endl;
    cout <<  m1 - m2 - m3;
    cout << "(m1 - m2) - m3 - (m2 - m3): " << endl;
    cout << (m1 - m2) - m3 - (m2 - m3);
    linalg::Matrix m4 = {{20, 21, 22, 23}, {24, 25, 26, 27}};
    cout << "m4: " << endl;
    cout << m4;
    cout << "We can not substract matrix of different dimesion:" << endl;
    cout << "m1 - m4: " << endl;
    cout << m1 - m4;
    cout << "-------- END TEST MINUS OPERATOR --------" << endl;
}

void test_to_cur_minus()
{
    cout << "---------- TEST MINUS TO CURRENT OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    linalg::Matrix m3 = {{20, 21, 22}, {23, 24, 25}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "m1 -= m2: " << endl;
    m1 -= m2;
    cout << m1;
    cout << "We see that m1 changed, but m2 did not changed:" << endl;
    cout << "m1: " << endl;
    cout << m1;
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 -= m2 + m3: " << endl;
    m1 -= m2 + m3;
    cout <<  m1;
    cout << "m2 -= (m2 + m3) + m1: " << endl;
    m2 -= (m2 + m3) + m1;
    cout << m2;
    linalg::Matrix m4 = {{20, 21, 22, 23}, {24, 25, 26, 27}};
    cout << "m4: " << endl;
    cout << m4;
    cout << "We can not substract matrix of different dimesion:" << endl;
    cout << "m1 -= m4: " << endl;
    m1 -= m4;
    cout << m1;
    cout << "-------- END TEST MINUS TO CURRENT OPERATOR --------" << endl;
}

void test_multiply_matrix()
{
    cout << "---------- TEST MULTIPLICATION OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    cout << "m2: " << endl;
    cout << m2;
    linalg::Matrix m3 = {{20, 21}, {22, 23}, {24, 25}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "m1 * m2: " << endl;
    cout << m1 * m2;
    cout << "We see that m1 m2 did not changed:" << endl;
    cout << "m1: " << endl;
    cout << m1;
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 * (m2 + m2) * m3" << endl;
    cout << m1 * (m2 + m2) * m3;
    linalg::Matrix m4 = {{20, 21, 22, 23}, {24, 25, 26, 27}};
    cout << "m4: " << endl;
    cout << m4;
    cout << "We can not multiply matrix of incorrect dimesions:" << endl;
    cout << "m1 * m4: " << endl;
    cout << m1 * m4;
    cout << "-------- END TEST MULTIPLICATION OPERATOR --------" << endl;
}

void test_multiply_const_to_matrix()
{
    cout << "---------- TEST MULTIPLICATION TO NUMBER OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "const = ";
    double c = 3;
    cout << c << endl;
    cout << "const * m1:" << endl;
    cout << c * m1;
    cout << "m1 did not changed:" << endl;
    cout << m1;
    cout << "(const + const) * m1:" << endl;
    cout << (c + c) * m1;
    cout << "m1 * const:" << endl;
    cout << m1 * c;
    cout << "m1 * (const + const):" << endl;
    cout << m1 * (c + c);
    cout << "-------- END TEST MULTIPLICATION TO NUMBER OPERATOR --------" << endl;
}

void test_multiply_to_cur_matrix()
{
    cout << "---------- TEST MULTIPLICATION TO CURRENT MATRIX OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    cout << "m2: " << endl;
    cout << m2;
    linalg::Matrix m3 = {{20, 21}, {22, 23}, {24, 25}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "m1 *= m2: " << endl;
    m1 *= m2;
    cout << m1;
    cout << "We see that m1 changed, but m2 did not changed:" << endl;
    cout << "m1: " << endl;
    cout << m1;
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 *= (m2 + m2) * m3" << endl;
    m1 *= (m2 + m2) * m3;
    cout << m1;
    linalg::Matrix m4 = {{20, 21, 22, 23}, {24, 25, 26, 27}, {28, 29, 30, 31}};
    cout << "m4: " << endl;
    cout << m4;
    cout << "We can not multiply matrix of incorrect dimesions:" << endl;
    cout << "m1 *= m4: " << endl;
    m1 *= m4;
    cout << m1;
    cout << "-------- END TEST MULTIPLICATION TO CURRENT MATRIX OPERATOR --------" << endl;
}

void test_multiply_const_to_current_matrix()
{
    cout << "---------- TEST MULTIPLICATION CURRENT MATRIX TO NUMBER OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "const = " << endl;
    double c = 3;
    cout << c << endl;
    cout << "m1 *= const" << endl;
    m1 *= c;
    cout << m1;
    cout << "m1 changed:" << endl;
    cout << m1;
    cout << " m1 *= (const + const) :" << endl;
    m1 *= (c + c);
    cout << m1;
    cout << "-------- END TEST MULTIPLICATION CURRENT MATRIX TO NUMBER OPERATOR --------" << endl;
}

void test_equal_matrix()
{
    cout << "---------- TEST EQUAL MATRIX OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 == m1:" << endl;
    if (m1 == m1)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "m1 == m2" << endl;
    if (m1 == m2)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "(m1 + m2) == (m1 + m2)" << endl;
    if ((m1 + m2) == (m1 + m2))
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    linalg::Matrix m3 = {{20, 21, 22}, {23, 24, 25}, {26, 27, 28}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "Matrix of different dimensions can not be equal:" <<  endl;
    cout << "m1 == m3" << endl;
    if (m1 == m3)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "-------- END TEST EQUAL MATRIX OPERATOR --------" << endl;
}

void test_not_equal_matrix()
{
    cout << "---------- TEST NOT EQUAL MATRIX OPERATOR ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1 != m1:" << endl;
    if (m1 != m1)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "m1 != m2" << endl;
    if (m1 != m2)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "(m1 + m2) != (m1 + m2)" << endl;
    if ((m1 + m2) != (m1 + m2))
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    linalg::Matrix m3 = {{20, 21, 22}, {23, 24, 25}, {26, 27, 28}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "Matrix of different dimensions can not be equal:" <<  endl;
    cout << "m1 != m3" << endl;
    if (m1 != m3)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "-------- END TEST NOT EQUAL MATRIX OPERATOR --------" << endl;
}

void test_norm()
{
    cout << "---------- TEST NORM MATRIX ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "m1.norm():" << endl;
    cout << m1.norm() << endl;
    cout << "m2.norm():" << endl;
    cout << m2.norm() << endl;
    cout << "(m1 + m1).norm():" << endl;
    cout << (m1 + m1).norm() << endl;
    cout << "-------- END TEST NORM MATRIX --------" << endl;
}

void test_trace()
{
    cout << "---------- TEST TRACE MATRIX ----------" << endl;
    linalg::Matrix m1 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "m1.trace()" << endl;
    cout << m1.trace() << endl;
    cout << "(m1 + m1).trace()" << endl;
    cout << (m1 + m1).trace() << endl;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "We can not get trace from not square matrix" << endl;
    cout << "m2.trace()" << endl;
    cout << m2.trace() << endl;
    cout << "-------- END TEST TRACE MATRIX --------" << endl;
}

void test_det()
{
    cout << "---------- TEST DETERMINANT MATRIX ----------" << endl;
    linalg::Matrix m1 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 16}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "m1.det()" << endl;
    cout << m1.det() << endl;
    cout << "(m1 + m1).det()" << endl;
    cout << (m1 + m1).det() << endl;
    linalg::Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "We can not get determinant from not square matrix" << endl;
    cout << "m2.det()" << endl;
    cout << m2.det() << endl;
    cout << "-------- END TEST DETERMINANT MATRIX --------" << endl;
}

void test_gauss()
{
    cout << "---------- TEST GAUSS MATRIX ----------" << endl;
    linalg::Matrix m1 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 16}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "m1.gauss_forward()" << endl;
    cout << m1.gauss_forward();
    cout << "m1.gauss_backward()" << endl;
    cout << m1.gauss_backward();
    linalg::Matrix m2 = {{7, 8, 9, 11}, {10, 11, 12, 15}, {13, 14, 16, 17}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "m2.gauss_forward()" << endl;
    cout << m2.gauss_forward();
    cout << "m2.gauss_backward()" << endl;
    cout << m2.gauss_backward();
    linalg::Matrix m3 = {{1, 2, 3, 4}, {10, 11, 12, 15}, {13, 14, 16, 17}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "We can not get gauss_backward() to not traingl matrix" << endl;
    cout << "m3.gauss_backward()" << endl;
    cout << m3.gauss_backward() << endl;
    cout << "-------- END TEST GAUSS MATRIX --------" << endl;
}

void test_rank()
{
    cout << "---------- TEST RANK MATRIX ----------" << endl;
    linalg::Matrix m1 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 16}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "m1.rank()" << endl;
    cout << m1.rank() << endl;
    linalg::Matrix m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "m2.rank()" << endl;
    cout << m2.rank() << endl;
    cout << "-------- END TEST RANK MATRIX --------" << endl;
}

void test_concat()
{
    cout << "---------- TEST CONCATENATION MATRIX ----------" << endl;
    linalg::Matrix m1 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 16}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "linalg::concatenate(m1, m2)" << endl;
    cout << linalg::concatenate(m1, m2);
    cout << "linalg::concatenate(m1 + m1, m2 + m2)" << endl;
    cout << linalg::concatenate(m1 + m1, m2 + m2);
    linalg::Matrix m3 = {{11, 21, 31}, {41, 51, 61}, {71, 81, 91}, {12, 13, 14}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "We can not concatenate matrix with different dimension" << endl;
    cout << "linalg::concatenate(m1, m3)" << endl;
    cout << linalg::concatenate(m1, m3) << endl;
    cout << "-------- END TEST CONCATENATION MATRIX --------" << endl;
}

void test_transpose()
{
    cout << "---------- TEST TRANSPOSE MATRIX ----------" << endl;
    linalg::Matrix m1 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 16}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "linalg::transpose(m1)" << endl;
    cout << linalg::transpose(m1);
    cout << "linalg::transpose(m2)" << endl;
    cout << linalg::transpose(m2);
    cout << "linalg::transpose(m1 + m2)" << endl;
    cout << linalg::transpose(m1 + m2);
    cout << "-------- END TEST TRANSPOSE MATRIX --------" << endl;
}

void test_invert()
{
    cout << "---------- TEST INVERT MATRIX ----------" << endl;
    linalg::Matrix m1 = {{7, 8, 9}, {10, 11, 12}, {13, 14, 16}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 11}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "linalg::invert(m1)" << endl;
    cout << linalg::invert(m1);
    cout << "linalg::invert(m2)" << endl;
    cout << linalg::invert(m2);
    cout << "linalg::invert(m1 + m2)" << endl;
    cout << linalg::invert(m1 + m2);
    linalg::Matrix m3 = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "We can not find invert matrix for not square matrix and matrix with zero determinant" << endl;
    cout << "linalg::invert(m3)" << endl;
    cout << linalg::invert(m3) << endl;
    cout << "-------- END TEST INVERT MATRIX --------" << endl;
}

void test_invert_zero_det()
{
    cout << "---------- TEST INVERT ZERO DET MATRIX ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "We can not find invert matrix for not square matrix and matrix with zero determinant" << endl;
    cout << "m1.det():" << endl;
    cout << m1.det() << endl;
    cout << "linalg::invert(m1)" << endl;
    cout << linalg::invert(m1) << endl;
    cout << "-------- END TEST INVERT ZERO DET MATRIX --------" << endl;
}

void test_power()
{
    cout << "---------- TEST RAISE POWER MATRIX ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "linalg::power(m1, 0)" << endl;
    cout << linalg::power(m1, 0) << endl;
    cout << "linalg::power(m1, 1)" << endl;
    cout << linalg::power(m1, 1) << endl;
    cout << "linalg::power(m1, 3)" << endl;
    cout << linalg::power(m1, 3) << endl;
    linalg::Matrix m2 = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "We can not raise to power not square matrix" << endl;
    cout << "linalg::power(m2, 4)" << endl;
    cout << linalg::power(m2, 4) << endl;
    cout << "-------- END TEST RAISE POWER MATRIX --------" << endl;
}

void test_solve()
{
    cout << "---------- TEST SOLVE SLAU ----------" << endl;
    linalg::Matrix m1 = {{1, -1}, {2, 1}};
    linalg::Matrix f1 = {-5, -7};
    cout << "m1: " << endl;
    cout << m1;
    cout << "f1: " << endl;
    cout << f1;
    cout << "linalg::solve(m1, f1)" << endl;
    cout << linalg::solve(m1, f1);
    linalg::Matrix m2 = {{3, 2, -5}, {2, -1, 3}, {1, 2, -1}};
    linalg::Matrix f2 = {-1, 13, 9};
    cout << "m2: " << endl;
    cout << m2;
    cout << "f2: " << endl;
    cout << f2;
    cout << "linalg::solve(m2, f2)" << endl;
    cout << linalg::solve(m2, f2);
    linalg::Matrix m3 = {{4, 2, -1}, {5, 3, -2}, {3, 2, -3}};
    linalg::Matrix f3 = {1, 2, 0};
    cout << "m3: " << endl;
    cout << m3;
    cout << "f3: " << endl;
    cout << f3;
    cout << "linalg::solve(m3, f3)" << endl;
    cout << linalg::solve(m3, f3);
    linalg::Matrix m4 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    linalg::Matrix f4 = {1, 2, 0};
    cout << "m4: " << endl;
    cout << m4;
    cout << "f4: " << endl;
    cout << f4;
    cout << "We can not solve system if the rank of the original system does not match the rank of the extended one" << endl;
    cout << "linalg::solve(m4, f4)" << endl;
    cout << linalg::solve(m4, f4);
    cout << "-------- END TEST SOLVE SLAU--------" << endl;
}

void test_minor()
{
    cout << "---------- TEST MINOR ----------" << endl;
    linalg::Matrix m1 = {{1, -1}, {2, 1}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "linalg::minor(m1, 0, 0):" << endl;
    cout << linalg::minor(m1, 0, 0) << endl;
    cout << "linalg::minor(m1, 0, 1):" << endl;
    cout << linalg::minor(m1, 0, 1) << endl;
    linalg::Matrix m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    cout << "m2: " << endl;
    cout << m2;
    cout << "linalg::minor(m2, 0, 0):" << endl;
    cout << linalg::minor(m2, 0, 0) << endl;
    cout << "linalg::minor(m2, 1, 1):" << endl;
    cout << linalg::minor(m2, 1, 1) << endl;
    linalg::Matrix m3 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    cout << "m3: " << endl;
    cout << m3;
    cout << "We can not find minor from not square matrix:" << endl;
    cout << "linalg::minor(m3, 1, 1):" << endl;
    cout << linalg::minor(m3, 1, 1) << endl;
    cout << "-------- END TEST MINOR--------" << endl;
}

void test_index()
{
    cout << "---------- TEST INDEX ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "m1(1, 1)" << endl;
    cout << m1(1, 1) << endl;
    cout << "m1[1][1]" << endl;
    cout << m1[1][1] << endl;
    cout << "m1(i, j) == m1[i][j]?" << endl;
    int f = 0;
    for (int i = 0; i < m1.rows(); i++)
    {
        for (int j = 0; j < m1.columns(); j++)
        {
            if (fabs(m1(i, j) - m1[i][j]) > eps)
            {
                f = 1;
                cout << "FALSE" << endl;
                break;
            }
        }
        if (f == 1)
        {
            break;
        }
    }
    if (f == 0)
    {
        cout << "TRUE" << endl;
    }
    cout << "We can change elements by index:" << endl;
    cout << "m1[1][1] = 100" << endl;
    m1[1][1] = 100;
    cout << m1;
    cout << "We can not to call element by not real index:" << endl;
    cout << "m1[5][5]:" << endl;
    cout << m1[5][5];
    cout << "-------- END TEST INDEX --------" << endl;
}

void test_decompose()
{
    cout << "---------- TEST DECOMPOSE ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "decomposeBilinearForm(m1)" << endl;
    linalg::decomposeBilinearForm(m1);
    cout << "We can find only one part:" << endl;
    cout << "linalg::symmetric_part(m1)" << endl;
    cout << linalg::symmetric_part(m1);
    cout << "linalg::skew_symmetric_part(m1)" << endl;
    cout << linalg::skew_symmetric_part(m1);
    cout << "We can not decompose not square matrix:" << endl;
    linalg::Matrix m2 = {{1, 2, 3, 5}, {4, 5, 6, 8}, {7, 8, 9, 10}};
    cout << "m2: " << endl;
    cout << m2; 
    cout << "decomposeBilinearForm(m2)" << endl;
    linalg::decomposeBilinearForm(m2);
    cout << "-------- END TEST DECOMPOSE --------" << endl;
}

void test_post_and_pref_incr_and_unar_minus()
{
    cout << "---------- TEST POSTFIX AND PREFIX INCREMENTS ----------" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "m1++" << endl;
    cout << m1++;
    cout << "++m1" << endl;
    cout << ++m1;
    cout << "m1--" << endl;
    cout << m1--;
    cout << "--m1" << endl;
    cout << --m1;
    cout << "(m1 + m1)++" << endl;
    cout << (m1 + m1)++ << endl;
    cout << "++(m1 + m1)" << endl;
    cout << ++(m1 + m1) << endl;
    cout << "(m1 + m1)--" << endl;
    cout << (m1 + m1)-- << endl;
    cout << "--(m1 + m1)" << endl;
    cout << --(m1 + m1) << endl;
    cout << "Unary minus:" << endl;
    cout << "-m1" << endl;
    cout << -m1;
    cout << "-------- END TEST POSTFIX AND PREFIX INCREMENTS --------" << endl;
}

void test_solve_vector_view()
{
    cout << "---------- TEST SOLVE VECTOR VIEW ----------" << endl;
    linalg::Matrix m1 = {{1, 0, 0}, {0, 1, 1}};
    cout << "m1: " << endl;
    cout << m1;
    linalg::Matrix f1 = {1, 1};
    cout << "f1: " << endl;
    cout << f1;
    cout << "linalg::solve_vector_view(m1, f1)" << endl;
    linalg::solve_vector_view(m1, f1);
    linalg::Matrix m2 = {{1, 3, 5}, {1, 2, 4}, {2, 4, 8}};
    cout << "m2: " << endl;
    cout << m2;
    linalg::Matrix f2 = {10, 1, 2};
    cout << "f2: " << endl;
    cout << f2;
    cout << "linalg::solve_vector_view(m2, f2)" << endl;
    linalg::solve_vector_view(m2, f2);
    linalg::Matrix m3 = {{3, 2, -5}, {2, -1, 3}, {1, 2, -1}};
    cout << "m3: " << endl;
    cout << m3;
    linalg::Matrix f3 = {-1, 13, 9};
    cout << "f3: " << endl;
    cout << f3;
    cout << "linalg::solve_vector_view(m3, f3)" << endl;
    linalg::solve_vector_view(m3, f3);
    cout << "-------- END TEST SOLVE VECTOR VIEW --------" << endl;
}

void test_input_output()
{
    cout << "---------- TEST INPUT/OUTPUT ----------" << endl;
    cout << "We create and output matrix:" << endl;
    linalg::Matrix m1 = {{1, 0, 0}, {0, 1, 1}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "We can input matrix:" << endl;
    linalg::Matrix m2(1, 1);
    cout << "Matrix m2 from one element (correct input):" << endl;
    cin >> m2;
    cout << "m2:" << endl;
    cout << m2;
    cout << "Matrix m2 from one element (incorrect input) -- we will have an exception:" << endl;
    cin >> m2;
    cout << "-------- END TEST INPUT/OUTPUT --------" << endl;   
}

void test_reshape()
{
    cout << "---------- TEST RESHAPE ----------" << endl;
    cout << "We create and output matrix:" << endl;
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    cout << "m1: " << endl;
    cout << m1;
    cout << "m1.reshape(1, 6)" << endl;
    m1.reshape(1, 6);
    cout << m1;
    cout << "m1.reshape(3, 2)" << endl;
    m1.reshape(3, 2);
    cout << m1;
    cout << "Incorrect reshape:" << endl;
    cout << "m1.reshape(10, 1)" << endl;
    m1.reshape(10, 1);
    cout << "-------- END TEST RESHAPE --------" << endl;   
}

void test_task()
{
    cout << "---------- TEST TASKS ----------" << endl;
    cout << "1) A^0 = E" << endl;
    linalg::Matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    linalg::Matrix E = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    cout << "A^0:" << endl;
    cout << linalg::power(A, 0);
    cout << "A^0 == E?" << endl;
    if (linalg::power(A, 0) == E)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "2) (A^T)^-1 = (A^-1)^T" << endl;
    linalg::Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    linalg::Matrix m1 = linalg::invert(linalg::transpose(m));
    linalg::Matrix m2 = linalg::transpose(linalg::invert(m));
    cout << "A: " << endl;
    cout << m;
    cout << "(A^T)^-1: " << endl;
    cout << m1;
    cout << "(A^-1)^T: " << endl;
    cout << m2;
    cout << "m1 == m2?" << endl;
    if (m1 == m2)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "3) (A1 * A2)^-1 = A2^-1 *A1^-1" << endl;
    linalg::Matrix A1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    linalg::Matrix A2 = {{1, 2, 4}, {4, 5, 9}, {7, 8, 11}};
    cout << "A1: " << endl;
    cout << A1;
    cout << "A2: " << endl;
    cout << A2;
    linalg::Matrix l = linalg::invert(A1 * A2);
    linalg::Matrix r = linalg::invert(A2) * linalg::invert(A1);
    cout << "(A1 * A2)^-1:" << endl;
    cout << l;
    cout << "A2^-1 *A1^-1:" << endl; 
    cout << r;
    cout << "(A1 * A2)^-1 == A2^-1 * A1^-1?" << endl;
    if (l == r)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "4) (A^-1)^6 = (A^-1^2)^3" << endl;
    linalg::Matrix A3 = {{1, 2, 4}, {4, 5, 9}, {7, 8, 11}};
    cout << "A: " << endl;
    cout << A3;
    linalg::Matrix l1 = linalg::power(linalg::invert(A3), 6);
    linalg::Matrix r1 = linalg::power(linalg::power(linalg::invert(A3), 2), 3);
    cout << "(A^-1)^6:" << endl;
    cout << l1;
    cout << "(A^-1^2)^3:" << endl; 
    cout << r1;
    cout << "(A^-1)^6 == (A^-1^2)^3?" << endl;
    if (l1 == r1)
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }
    cout << "-------- END TEST TASKS--------" << endl;
}
