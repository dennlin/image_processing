// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  Matrix_init(energy, img->width, img->height);
  Matrix_fill(energy, 0);
    for (int row = 1; row < img->height - 1; ++row) {
      for (int column = 1; column < img->width - 1; ++column) {
        Pixel north = Image_get_pixel(img, row-1, column);
        Pixel south = Image_get_pixel(img, row+1, column);
        Pixel west = Image_get_pixel(img, row, column-1);
        Pixel east = Image_get_pixel(img, row, column+1);
        int result = squared_difference(north, south) + squared_difference(west, east);
        int *pointer = Matrix_at(energy, row, column);
        (*pointer)=result;
      }
    }
  Matrix_fill_border(energy, Matrix_max(energy));
}

// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  //first row is energy matrix
  Matrix_init(cost,energy->width,energy->height);
  Matrix_fill(cost, 0);
  for(int i=0; i<energy->width; ++i){
    cost->data[i] = energy->data[i];
  }
  //now computing cost matrix 
  //cost(r, c) = energy(r, c) + min(cost(r-1, c-1),cost(r-1, c),cost(r-1, c+1))
  
  for(int row=1; row<energy->height; ++row){
    for(int column=0; column<energy->width; ++column){
      int current=0;
      if(column != 0 && column != energy->width-1){
       current = *Matrix_at(energy, row, column) + Matrix_min_value_in_row(cost, row-1, column-1, column+2);
      }
      else if(column == 0){
        current = *Matrix_at(energy, row, column) + Matrix_min_value_in_row(cost, row-1, column, column+2);
      }
      else if(column == energy->width-1){
        current = *Matrix_at(energy, row, column) + Matrix_min_value_in_row(cost, row-1, column-1, column+1);
      }
      int *data = Matrix_at(cost, row, column);
      (*data) = current;
    }
  }
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  int min_index = Matrix_column_of_min_value_in_row(cost, cost->height-1, 0, cost->width);
  seam[0] = min_index;
  int current_index = 0;

  for(int i=cost->height-2; i>=0; --i){
   if(seam[current_index] != 0 && seam[current_index] != cost->width-1){
    min_index = Matrix_column_of_min_value_in_row(cost, i, seam[current_index]-1, seam[current_index]+2);
   }
   else if(seam[current_index] == 0){
    min_index = Matrix_column_of_min_value_in_row(cost, i, seam[current_index], seam[current_index]+2);
   }
   else if(seam[current_index] == cost->width-1){
    min_index = Matrix_column_of_min_value_in_row(cost, i, seam[current_index]-1, seam[current_index]+1);
   }
   seam[current_index+1] = min_index;
   ++current_index;
  }

  int *seam_again;
  seam_again = new int [cost->height];

  int *Pseam = &(seam[Matrix_height(cost)-1]);
  int *Pseam_again = seam_again;
  for(int i = 0; i < cost->height; i++)
  {
    *Pseam_again = *Pseam;
    Pseam_again++;
    Pseam--;
  }
  for(int i = 0; i < cost->height; i++)
  {
    seam[i] = seam_again[i];
  }
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
  const int x = img->height;  
  int *seam_again;
  seam_again = new int [x];

  const int *Pseam = &(seam[x-1]);
  int *Pseam_again = seam_again;
  for(int i = 0; i < x; i++)
  {
    *Pseam_again = *Pseam;
    Pseam_again++;
    Pseam--;
  }  
  
  Image *thinner_image = new Image;
  Image_init(thinner_image, img->width-1, img->height);
  for(int current_seam=0; current_seam<img->height; ++current_seam){
    int seam_index = seam_again[current_seam];
    
    Pixel *new_row;
    new_row = new Pixel [img->width-1];
    //Pixel new_row[];
    int current_row = img->height-1 - current_seam; 
    
    for(int old_index = 0; old_index<img->width; ++old_index){
      Pixel old_pixel = Image_get_pixel(img, current_row, old_index);
      if(old_index<seam_index){
        new_row[old_index] = old_pixel; 
      }
      else if (old_index>seam_index){
        new_row[old_index-1] = old_pixel; 
      }

    }
    for(int i=0; i<thinner_image->width; ++i){
      Image_set_pixel(thinner_image, current_row, i, new_row[i]);
    }
  }
  *img = *thinner_image;
  delete thinner_image;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {
  int cut_times = img->width - newWidth;
  for(int i=0; i<cut_times; ++i){
    Matrix energy_matrix;
    compute_energy_matrix(img, &energy_matrix);
    Matrix cost_matrix;
    compute_vertical_cost_matrix(&energy_matrix, &cost_matrix);
    
    int *seam;
    seam = new int [img->height];

    find_minimal_vertical_seam(&cost_matrix, seam);
    remove_vertical_seam(img, seam);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  rotate_left(img);
  seam_carve_width(img, newHeight); 
  rotate_right(img);  
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
