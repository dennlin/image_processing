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

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

TEST(minimumMaximum){
  Matrix *testmatrix = new Matrix;
  
  Matrix_init(testmatrix, 4, 5);
  Matrix_fill(testmatrix, 66);
  
  *Matrix_at(testmatrix, 1, 2) = 77;
  *Matrix_at(testmatrix, 1, 0) = 19;
  *Matrix_at(testmatrix, 1, 1) = 19;
  *Matrix_at(testmatrix, 1, 3) = 19;
  *Matrix_at(testmatrix, 3, 1) = -11;
  *Matrix_at(testmatrix, 4, 2) = -11;
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(testmatrix, 3, 0, 4), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(testmatrix, 4, 0, 4), 2);
  ASSERT_EQUAL(Matrix_min_value_in_row(testmatrix, 1, 0, 4), 19);
  ASSERT_EQUAL(Matrix_min_value_in_row(testmatrix, 4, 0, 4), -11);                                    
  ASSERT_EQUAL(Matrix_max(testmatrix), 77);
  ASSERT_EQUAL(Matrix_width(testmatrix), 4);
  ASSERT_EQUAL(Matrix_height(testmatrix), 5);
  
  Matrix_fill_border(testmatrix, 50);  

  
  for(int i = 0; i<testmatrix->height; ++i){   

    for(int j = 0; j<testmatrix->width; ++j)
    {

      if(i == 0 || j == testmatrix->width - 1 || j == 0 || i == testmatrix->height-1)
      ASSERT_EQUAL(*Matrix_at(testmatrix, i, j), 50);
    } 
    
  }
  delete testmatrix;
}



TEST(printing){
  
  Matrix *testmatrix = new Matrix;
  Matrix_init(testmatrix, 4, 4);
  Matrix_fill(testmatrix, 66);
  Matrix_fill_border(testmatrix, 255);
  int *index = Matrix_at(testmatrix, 3, 1);
  *index = 77;
  ostringstream right;
  right << "4 4\n";
  right << "255 255 255 255 \n";
  right << "255 66 66 255 \n";
  right << "255 66 66 255 \n";
  right << "255 77 255 255 \n";
  ostringstream mat;
  Matrix_print(testmatrix, mat);
  ASSERT_EQUAL(mat.str(), right.str());
  delete testmatrix;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
