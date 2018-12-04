#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
using std::ofstream;
using std::endl;

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  //printf("string name \n");
  //printf("%s", filename.c_str());
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // reference: https://en.wikipedia.org/wiki/Netpbm_format#File_format_description
  // reference 2: https://www.bgsu.edu/arts-and-sciences/computer-science/cs-documentation/writing-data-to-files-using-c-plus-plus.html
  // Replace with your code here:
  ofstream outdata;
  outdata.open(filename, std::ofstream::trunc);

  outdata << "P3" << endl; //type is ppm with ASCII
  outdata << width << " " << height << endl;   //width and height
  outdata << 255 << endl; //8 bit per color value
  int counter = 0;
  /*for(int n = 0; n < data.size(); n++){
         int value = (int)data.at(n);
         outdata << value << endl;
    }*/
  for(int q = 0; q < height; q++){ //q is the row
    for(int i = 0; i < width; i++){ //i is the column
      //loop over channels
      if(num_channels == 3){
        for(int p = 0; p < 3; p++){
          int value = (int) data.at(counter);
          counter++;
          outdata << value << " ";
          //easier to replace with counter
          //outdata << p; //data.at(p + num_channels*(i + q*width)); 
          //seems not necessary trim trailing whitespaces of rows
          /*if( (p =! num_channels - 1) || (i != width - 1) ) { //except for last in line
            outdata << " ";
          }*/
        }
      }
      else{// that means num_channels must be 1, i.e. grayscale
      // since ppm files always have three channels we need to triplicate the gray value
          int value = (int) data.at(counter);
          counter++;
          outdata << value << " " << value << " " << value << " ";   
      }
    }
    outdata << endl; //new row
  }
  outdata.close();

  return 0;
  ////////////////////////////////////////////////////////////////////////////
}
