// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image.h"
#include "processing.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <string>

using namespace std;

int main(int argc, char *argv[]){    
    if(argc != 4 && argc != 5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
    }
    ifstream fin(argv[1]);
    if(!fin.is_open())
    {
      cout << "Error opening file: " << argv[1] << endl;
      return 1;
    }

    if(argc == 4)
    {
      int w = atoi(argv[3]);
    Image* img = new Image;    
    Image_init(img, fin);
    if((w > Image_width(img)) | (w <= 0))
    {
     cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
       return 1;
    }      
    seam_carve_width(img, w); 
    ofstream fout(argv[2]);
    Image_print(img, fout);
    delete img;
    }    
    
    
    if(argc == 5)
    {
      int w = atoi(argv[3]);
    int h = atoi(argv[4]);
    Image* img = new Image;    
    Image_init(img, fin);
    if((w > Image_width(img)) | (h > Image_height(img)) 
     | (w <= 0) | (h <= 0))
    {
     cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
       return 1;
    }      
    seam_carve(img, w, h); 
    ofstream fout(argv[2]);
    Image_print(img, fout);
    delete img;
    }
}