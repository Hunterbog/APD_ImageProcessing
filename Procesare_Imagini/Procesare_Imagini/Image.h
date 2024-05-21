#pragma once
#include <cstdio>
#include <stdint.h>
#include <omp.h>
#include <vector>
#include <thread>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>

enum ImageType {
	PNG, JPG, BMP, TGA
};

struct Image {
	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;

	Image(const char* filename);
	Image(int w, int h, int channels);
	Image(const Image& img);
	~Image();
	bool read(const char* filename);
	bool write(const char* filename);

	ImageType getFileType(const char* filename);
	 
	Image& grayscale_avg();
	Image& grayscale_lum();
	Image& colorMask(float r, float g, float b);

	//omp parallel
	Image& grayscale_avg_parallel();
	Image& grayscale_lum_parallel();
	Image& colorMask_parallel(float r, float g, float b);

	//threads parallel
	Image& grayscale_avg_parallel_threads(int threads);
	Image& grayscale_lum_parallel_threads(int threads);
	Image& colorMask_parallel_threads(float r, float g, float b, int num_threads);
};