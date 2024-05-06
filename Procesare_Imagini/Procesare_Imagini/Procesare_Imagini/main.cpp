#include "Image.h"
using namespace std;

int main(int argc, char** argv)
{
    Image test("girl.jpg");
    /*
    test.write("new.png");
    Image copy = test;
    for (int i = 0; i < copy.w * copy.channels; ++i) {
        copy.data[i] = 255;
    }
    copy.write("copy.png");
    Image blank(100, 100, 3);
    blank.write("blank.jpg");
    */
 
    //Image gray_avg = test;
    //gray_avg.grayscale_avg();
    //gray_avg.write("gray_avg.png");
  
  
   /* auto start1 = chrono::high_resolution_clock::now();
    Image color_mask = test;
    color_mask.colorMask(0, 1, 0);
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::duration<double>>(end1 - start1);
   
    color_mask.write("green.png");
    cout << "Time taken by color_mask program is : " << fixed << setprecision(3) << duration1.count() << " seconds" << endl;

    auto start = chrono::high_resolution_clock::now();
    Image colorMask_parallel = test;
    colorMask_parallel.colorMask_parallel(0, 1, 0);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start);

    colorMask_parallel.write("green_parallel.png");
    cout << "Time taken by color_mask_parallel program is : " << fixed << setprecision(3) << duration.count() << " seconds" << endl;*/


    auto start1 = chrono::high_resolution_clock::now();
    Image gray_lum = test;
    gray_lum.grayscale_lum();
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::duration<double>>(end1 - start1);
    gray_lum.write("gray_lum.png");
    cout << "Time taken by gray_lum program is : " << fixed << setprecision(3) << duration1.count() << " seconds" << endl;

    auto start = chrono::high_resolution_clock::now();
    Image gray_lum_parallel = test;
    gray_lum_parallel.grayscale_lum_parallel();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start);

    gray_lum_parallel.write("gray_lum_parallel.png");
    cout << "Time taken by gray_lum_parallel program is : " << fixed << setprecision(3) << duration.count() << " seconds" << endl;


    return 0;
}
