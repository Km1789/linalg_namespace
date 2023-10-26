#include <iostream>
#include "matrix.h"
#include "test.h"
using namespace std;

int main()
{
    try
    {
        linalg::help();


        //test_constructors();
        //test_constructors_not_digit();
        //test_copy_and_indexes();
        //test_plus();
        //test_to_cur_plus();
        //test_minus();
        //test_to_cur_minus();
        //test_multiply_matrix();
        //test_multiply_const_to_matrix();
        //test_multiply_to_cur_matrix();
        //test_multiply_const_to_current_matrix();
        //test_equal_matrix();
        //test_not_equal_matrix();
        //test_norm();
        //test_trace();
        //test_det();
        //test_gauss();
        //test_rank();
        //test_concat();
        //test_transpose();
        //test_invert();
        //test_invert_zero_det();
        //test_power();
        //test_solve();
        //test_minor();
        //test_index();
        //test_decompose();
        //test_post_and_pref_incr_and_unar_minus();
        //test_solve_vector_view();
        //test_input_output();
        //test_task();
        //test_reshape();
    }
    catch(linalg_exseption& err) 
    {
        cout << err.What() << endl;
    }
    catch(...)
    {
        cout << "Fatal error!" << endl;
        return -1;
    }
    return 0;
}