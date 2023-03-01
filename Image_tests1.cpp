// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// Tests setting and getting pixel
TEST(test_Image_get_pixel) 
{
  Image *img = new Image;
  Image_init(img, 8, 4);
  const Pixel red = {255, 230, 120};
  for(int i = 0; i < Image_height(img); i++)
  {
    for(int j = 0; j < Image_width(img); j++)
    {
      Image_set_pixel(img, i, j, red);
    }
  }
  
  const Pixel blue = {0, 0, 255};
  Image_set_pixel(img, 0, 0, blue);
  ASSERT_TRUE(Pixel_equal(blue, Image_get_pixel(img, 0, 0)));

  for(int i = 0; i < Image_height(img); i++)
  {
    for(int j = 1; j < Image_width(img); j++)
    {
      ASSERT_TRUE(Pixel_equal(red, Image_get_pixel(img, i, j)));
    }
  }
  delete img;  
}
// Tests filling up image with pixel
TEST(test_Image_fill) 
{
  Image *img = new Image;
  Image_init(img, 6, 4);
  const Pixel red = {25, 10, 10};
  Image_fill(img, red);
  for(int i = 0; i < Image_height(img); i++)
  {
    for(int j = 0; j < Image_width(img); j++)
    {
      ASSERT_TRUE(Pixel_equal(red, Image_get_pixel(img, i, j)));
    }
  }
  ASSERT_EQUAL(Image_height(img), 4);
  ASSERT_EQUAL(Image_width(img), 6);
  delete img;   
}
// Tests reading image from is stream
TEST(test_Image_init)
{
  Image *img = new Image;  
  string input = "P3 2 3 255 3 4 5 6 7 8 9 0 0 1 2 3 4 5 6 7 8 1";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);  
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  string output_correct = "P3\n2 3\n255\n3 4 5 6 7 8 \n9 0 0 1 2 3 \n4 5 6 7 8 1 \n";
  ASSERT_EQUAL(actual, output_correct);
  delete img;

  
}
TEST(test_Image_horse){
  Image *img1 = new Image;
  ifstream fin("horses.ppm");
  Image_init(img1, fin);
  /*int r = 4;
  int b = 4;
  cout << Image_get_pixel(img1, r, b).r << endl;
  cout << Image_get_pixel(img1, r, b).g << endl;
  cout << Image_get_pixel(img1, r, b).b << endl;*/
  const Pixel red = {52, 46, 48};
  ASSERT_TRUE(Pixel_equal(red, Image_get_pixel(img1, 4, 4)));  
  delete img1;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
