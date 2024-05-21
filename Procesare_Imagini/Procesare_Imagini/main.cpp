#include "Image.h"
#include <chrono>
using namespace std;

int main(int argc, char** argv)
{
    // Image test("girl.png");
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
  
  


    //auto start1 = chrono::high_resolution_clock::now();
    //Image gray_avg = test;
    //gray_avg.grayscale_avg();
    //auto end1 = chrono::high_resolution_clock::now();
    //auto duration1 = chrono::duration_cast<chrono::duration<double>>(end1 - start1);
    //gray_avg.write("gray_avg.png");
    //cout << "Time taken by gray_avg program is : " << fixed << setprecision(3) << duration1.count() << " seconds" << endl;

    //auto start = chrono::high_resolution_clock::now();
    //Image gray_avg_parallel = test;
    //gray_avg_parallel.grayscale_avg_parallel();
    //auto end = chrono::high_resolution_clock::now();
    //auto duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    //gray_avg_parallel.write("gray_avg_parallel.png");
    //cout << "Time taken by gray_avg_parallel program is : " << fixed << setprecision(3) << duration.count() << " seconds" << endl;

    //auto start2 = chrono::high_resolution_clock::now();
    //Image gray_avg_parallel_threads = test;
    //gray_avg_parallel_threads.grayscale_avg_parallel_threads(10);
    //auto end2 = chrono::high_resolution_clock::now();
    //auto duration2 = chrono::duration_cast<chrono::duration<double>>(end2 - start2);
    //gray_avg_parallel_threads.write("gray_avg_parallel_threads.png");
    //cout << "Time taken by gray_avg_parallel_threads program is : " << fixed << setprecision(3) << duration2.count() << " seconds" << endl;

    /*auto start1 = chrono::high_resolution_clock::now();
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

    auto start2 = chrono::high_resolution_clock::now();
    Image gray_lum_parallel_threads = test;
    gray_lum_parallel_threads.grayscale_lum_parallel_threads(10);
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::duration<double>>(end2 - start2);
    gray_lum_parallel_threads.write("gray_lum_parallel_threads.png");
    cout << "Time taken by gray_lum_parallel_threads program is : " << fixed << setprecision(3) << duration2.count() << " seconds" << endl;*/

    
    vector<string> image_files = { "girl.png", "girl.png", "girl.png", "girl.png", "image3.png",  "girl.png", "image2.png", "girl.png", "girl.png", "girl.png", "image.png", "girl.png", "girl.png" "girl.png", "girl.png", "girl.png" , "girl.png" };

    double total_time_color_mask = 0.0;
    double total_time_color_mask_parallel = 0.0;
    double total_time_color_mask_parallel_threads = 0.0;

    for (const auto& file : image_files) {
      
        Image test(file.c_str());

        if (test.data == nullptr) {
            cout << "Failed to read image: " << file << endl;
            continue;
        }

        auto start1 = chrono::high_resolution_clock::now();
        Image color_mask = test;
        color_mask.colorMask(0, 0, 0.5);
        auto end1 = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::duration<double>>(end1 - start1);
        string output_filepath = "color_mask_" + file;
        color_mask.write(output_filepath.c_str());
        cout << "Time taken by color_mask program for " << file << " is : " << fixed << setprecision(3) << duration1.count() << " seconds" << endl;
        total_time_color_mask += duration1.count();

        auto start = chrono::high_resolution_clock::now();
        Image color_mask_parallel = test;
        color_mask_parallel.colorMask_parallel(0, 0, 0.5);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::duration<double>>(end - start);
        output_filepath = "color_mask_parallel_" + file;
        color_mask_parallel.write(output_filepath.c_str());
        cout << "Time taken by color_mask_parallel program for " << file << " is : " << fixed << setprecision(3) << duration.count() << " seconds" << endl;
        total_time_color_mask_parallel += duration.count();

        auto start2 = chrono::high_resolution_clock::now();
        Image color_mask_parallel_threads = test;
        color_mask_parallel_threads.colorMask_parallel_threads(0, 0, 1, 10);
        auto end2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::duration<double>>(end2 - start2);
        output_filepath = "color_mask_parallel_threads_" + file;
        color_mask_parallel_threads.write(output_filepath.c_str());
        cout << "Time taken by color_mask_parallel_threads program for " << file << " is : " << fixed << setprecision(3) << duration2.count() << " seconds" << endl;
        total_time_color_mask_parallel_threads += duration2.count();
    }

    cout << "Total time taken by color_mask program: " << fixed << setprecision(3) << total_time_color_mask << " seconds" << endl;
    cout << "Total time taken by color_mask_parallel program: " << fixed << setprecision(3) << total_time_color_mask_parallel << " seconds" << endl;
    cout << "Total time taken by color_mask_parallel_threads program: " << fixed << setprecision(3) << total_time_color_mask_parallel_threads << " seconds" << endl;

    return 0;
}
