// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_print)
{
  Matrix *mat = new Matrix;
  Matrix_init(mat, 6, 5);
  Matrix_fill(mat, 29);
  Matrix_fill_border(mat, 290);
  int *pos = Matrix_at(mat, 2, 0);
  int row = Matrix_row(mat, pos);
  int column = Matrix_column(mat, pos);
  pos  = Matrix_at(mat, row, column);
  *pos = 567;

  ostringstream correct;
  correct << "6 5\n";
  correct << "290 290 290 290 290 290 \n";
  correct << "290 29 29 29 29 290 \n";
  correct << "567 29 29 29 29 290 \n";
  correct << "290 29 29 29 29 290 \n";
  correct << "290 290 290 290 290 290 \n";
  ostringstream s;
  Matrix_print(mat, s);

  ASSERT_EQUAL(s.str(), correct.str());
  delete mat;
}

TEST(test_min_max)
{
  Matrix *mat = new Matrix;
  Matrix_init(mat, 6, 5);
  Matrix_fill(mat, 29);
  *Matrix_at(mat, 2, 3) = 567;
  *Matrix_at(mat, 2, 1) = 13;
  *Matrix_at(mat, 2, 2) = 13;
  *Matrix_at(mat, 2, 5) = 13;
  
  *Matrix_at(mat, 4, 4) = -100;
  *Matrix_at(mat, 0, 1) = -100;
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2,
                                      0, 6), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 3,
                                      0, 6), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2,
                                      0, 6), 13);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3,
                                      0, 6), 29);                                    
  ASSERT_EQUAL(Matrix_max(mat), 567);
  ASSERT_EQUAL(Matrix_height(mat), 5);
  ASSERT_EQUAL(Matrix_width(mat), 6);

  Matrix_fill_border(mat, 1000);  
  int *pos = Matrix_at(mat,0,0);
  
  for(int i = 0; i <Matrix_width(mat)*Matrix_height(mat); i++)
  {    
    int row = Matrix_row(mat, pos);
    int column = Matrix_column(mat, pos);
    if(row == 0 || column == 0 || row == Matrix_height(mat) - 1 || column == Matrix_width(mat) - 1)
    {
      ASSERT_EQUAL(*Matrix_at(mat, row, column), 1000);
    }
    pos++;
  }
  delete mat;
}

TEST(test_const_matrix)
{
  Matrix *mat = new Matrix;
  Matrix_init(mat, 9, 6);
  *Matrix_at(mat, 4,5) = 73;
  *Matrix_at(mat, 5,2) = 73;
  const Matrix *mat1 = mat;
  
  
  ASSERT_EQUAL(Matrix_at(mat, 5, 3), Matrix_at(mat1, 5, 3));
  ASSERT_EQUAL(*Matrix_at(mat, 4, 5), *Matrix_at(mat1, 5, 2));

  delete mat;

}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
