#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
using namespace std;

Image::Image(const char* filename) {
	if (read(filename)) {
		printf("Read %s\n", filename);
		size = w * h * channels;
	}
	else {
		printf("Read failed %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels){
	size = w * h * channels;
	data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels){
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(const char* filename) {
	data = stbi_load(filename, &w, &h, &channels, 0);
	return data != NULL;
}

bool Image::write(const char* filename) {
	ImageType type = getFileType(filename);
	int success = 0;
	switch (type) {
	case PNG:
		success = stbi_write_png(filename, w, h, channels, data, w * channels);
		break;
	case BMP:
		success = stbi_write_bmp(filename, w, h, channels, data);
		break;
	case JPG:
		success = stbi_write_jpg(filename, w, h, channels, data, 100);
		break;
	case TGA:
		success = stbi_write_tga(filename, w, h, channels, data);
		break;
	}
	if (success != 0) {
		printf("\ Wrote %s [%d, %d, %d, %zu\n", filename, w, h, channels, size);
		return true;
	}
	else {
		printf("\ Failed to write %s [%d, %d, %d, %zu\n", filename, w, h, channels, size);
		return false;
	}
}

ImageType Image::getFileType(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if (ext != nullptr) {
		if (strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if (strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if (strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if (strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}

Image& Image::grayscale_avg()
{
	
	if (channels < 3) {
		printf("Image %p is already grayscale", this);
	}
	else {
		for (int i = 0; i < size; i += channels) {
			int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
			memset(data + i, gray, 3);
		}
	}
	return *this;
}

Image& Image::grayscale_lum()
{
	if (channels < 3) {
		printf("Image %p is already grayscale", this);
	}
	else {
		for (int i = 0; i < size; i += channels) {
			int gray = 0.2126 * data[i] +  0.7152 * data[i + 1] + 0.0722 * data[i + 2];
			memset(data + i, gray, 3);
		}
	}
	return *this;
}

Image& Image::colorMask(float r, float g, float b) {
	if (channels < 3) {
		printf("\e[Error] Color mask requires at least 3 channels\e\n");
	}
	else {
		for (int i = 0; i < size; i += channels) {
			data[i] *= r;
			data[i + 1] *= g;
			data[i + 2] *= b;
		}
	}
	return *this;
}

// OMP parallel

Image& Image::grayscale_avg_parallel() {
	if (channels < 3) {
		printf("Image %p is already grayscale", this);
		return *this;
	}

#pragma omp parallel for
	for (int i = 0; i < size; i += channels) {
		int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
		data[i] = gray;
		data[i + 1] = gray;
		data[i + 2] = gray;
	}

	return *this;
}

Image& Image::grayscale_lum_parallel() {
	if (channels < 3) {
		printf("Image %p is already grayscale", this);
		return *this;
	}

#pragma omp parallel for
	for (int i = 0; i < size; i += channels) {
		int gray = 0.2126f * data[i] + 0.7152f * data[i + 1] + 0.0722f * data[i + 2];
		data[i] = gray;
		data[i + 1] = gray;
		data[i + 2] = gray;
	}
	return *this;
}

Image& Image::colorMask_parallel(float r, float g, float b) {
	if (channels < 3) {
		printf("\e[Error] Color mask requires at least 3 channels\e\n");
	}
	else {
#pragma omp parallel for
		for (int i = 0; i < size; i += channels) {
			data[i] *= r;
			data[i + 1] *= g;
			data[i + 2] *= b;
		}
	}
	return *this;
}


//Threads parallel

Image& Image::grayscale_avg_parallel_threads(int num_threads) {
	if (channels < 3) {
		printf("Image %p is already grayscale\n", this);
		return *this;
	}

	auto grayscale_task = [this](int start, int end) {
		for (int i = start; i < end; i += channels) {
			int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
			data[i] = gray;
			data[i + 1] = gray;
			data[i + 2] = gray;
		}
		};

	std::vector<std::thread> threads;
	int chunk_size = size / num_threads;
	for (int i = 0; i < num_threads; ++i) {
		int start = i * chunk_size;
		int end = (i == num_threads - 1) ? size : start + chunk_size;
		threads.push_back(std::thread(grayscale_task, start, end));
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

	return *this;
}

Image& Image::grayscale_lum_parallel_threads(int num_threads) {
	if (channels < 3) {
		printf("Image %p is already grayscale\n", this);
		return *this;
	}

	auto grayscale_task = [this](int start, int end) {
		for (int i = start; i < end; i += channels) {
			if (i + 2 < size) { // Ensure we do not exceed the bounds
				int gray = 0.2126 * data[i] + 0.7152 * data[i + 1] + 0.0722 * data[i + 2];
				data[i] = gray;
				data[i + 1] = gray;
				data[i + 2] = gray;
			}
		}
		};

	std::vector<std::thread> threads;
	int chunk_size = size / num_threads;
	for (int i = 0; i < num_threads; ++i) {
		int start = i * chunk_size;
		int end = (i == num_threads - 1) ? size : start + chunk_size;
		threads.push_back(std::thread(grayscale_task, start, end));
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

	return *this;
}

Image& Image::colorMask_parallel_threads(float r, float g, float b, int num_threads) {
	if (channels < 3) {
		printf("[Error] Color mask requires at least 3 channels\n");
		return *this;
	}

	auto color_mask_task = [this, r, g, b](int start, int end) {
		for (int i = start; i < end; i += channels) {
			data[i] *= r;
			data[i + 1] *= g;
			data[i + 2] *= b;
		}
		};

	std::vector<std::thread> threads;
	int chunk_size = size / num_threads;
	for (int i = 0; i < num_threads; ++i) {
		int start = i * chunk_size;
		int end = (i == num_threads - 1) ? size : start + chunk_size;
		threads.push_back(std::thread(color_mask_task, start, end));
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
}
