/**
 * @File  : Image_Class.h
 * @brief : This file contains the declaration of the Image class (Fixed Version).
 */

#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H

#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <exception>
#include <cstring>
#include <algorithm>

class Image {
private:
    std::string filename;

    bool isValidFilename(const std::string& name) {
        const char* extension = strrchr(name.c_str(), '.');
        if (extension == nullptr) {
            return false;
        }
        return true;
    }

    short getExtensionType(const char* extension) {
        if (strcmp(extension, ".png") == 0) return PNG_TYPE;
        if (strcmp(extension, ".bmp") == 0) return BMP_TYPE;
        if (strcmp(extension, ".tga") == 0) return TGA_TYPE;
        if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) return JPG_TYPE;
        return UNSUPPORTED_TYPE;
    }

public:
    int width = 0;
    int height = 0;
    int channels = 3; // <--- تم نقله هنا ليكون Public
    unsigned char* imageData = nullptr;

    // Default Constructor
    Image() = default;

    // Load from file Constructor
    Image(std::string filename) : filename(filename) {
        loadNewImage(this->filename);
    }

    // Blank Image Constructor
    Image(int mWidth, int mHeight) {
        width = mWidth;
        height = mHeight;
        imageData = (unsigned char*)malloc(width * height * channels);
        if (imageData == nullptr) {
            throw std::bad_alloc();
        }
    }

    // Copy Constructor (Deep Copy)
    Image(const Image& other) {
        width = other.width;
        height = other.height;
        channels = other.channels;
        filename = other.filename;
        if (other.imageData != nullptr) {
            imageData = (unsigned char*)malloc(width * height * channels);
            if (imageData != nullptr) {
                memcpy(imageData, other.imageData, width * height * channels);
            }
        }
    }

    // Copy Assignment Operator
    Image& operator=(const Image& other) {
        if (this == &other) return *this;

        if (imageData != nullptr) {
            stbi_image_free(imageData);
            imageData = nullptr;
        }

        width = other.width;
        height = other.height;
        channels = other.channels;
        filename = other.filename;

        if (other.imageData != nullptr) {
            imageData = (unsigned char*)malloc(width * height * channels);
            if (imageData != nullptr) {
                memcpy(imageData, other.imageData, width * height * channels);
            }
        }
        return *this;
    }

    // Destructor
    ~Image() {
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }
    }

    bool loadNewImage(const std::string& fname) {
        if (!isValidFilename(fname)) {
            throw std::invalid_argument("The file extension does not exist");
        }

        const char* extension = strrchr(fname.c_str(), '.');
        if (getExtensionType(extension) == UNSUPPORTED_TYPE) {
            throw std::invalid_argument("File Extension is not supported");
        }

        if (imageData != nullptr) {
            stbi_image_free(imageData);
            imageData = nullptr;
        }

        imageData = stbi_load(fname.c_str(), &width, &height, &channels, STBI_rgb);
        if (imageData == nullptr) {
            throw std::invalid_argument("Invalid filename or file does not exist");
        }

        return true;
    }

    bool saveImage(const std::string& outputFilename) {
        if (!isValidFilename(outputFilename)) {
            throw std::invalid_argument("The file extension does not exist");
        }

        const char* extension = strrchr(outputFilename.c_str(), '.');
        short extensionType = getExtensionType(extension);

        if (extensionType == UNSUPPORTED_TYPE) {
            throw std::invalid_argument("Unsupported output file format");
        }

        if (extensionType == PNG_TYPE) {
            stbi_write_png(outputFilename.c_str(), width, height, STBI_rgb, imageData, width * 3);
        } else if (extensionType == BMP_TYPE) {
            stbi_write_bmp(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        } else if (extensionType == TGA_TYPE) {
            stbi_write_tga(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        } else if (extensionType == JPG_TYPE) {
            stbi_write_jpg(outputFilename.c_str(), width, height, STBI_rgb, imageData, 90);
        }

        return true;
    }

    unsigned char& getPixel(int x, int y, int c) {
        // Fixed bounds check (using >= instead of >)
        if (x >= width || x < 0) {
            throw std::out_of_range("X coordinate is out of bounds");
        }
        if (y >= height || y < 0) {
            throw std::out_of_range("Y coordinate is out of bounds");
        }
        if (c < 0 || c >= channels) {
            throw std::out_of_range("Channel index is out of bounds");
        }

        return imageData[(y * width + x) * channels + c];
    }

    void setPixel(int x, int y, int c, unsigned char value) {
        getPixel(x, y, c) = value; // Reuse getPixel bounds checking
    }

    unsigned char& operator()(int row, int col, int channel) {
        return getPixel(row, col, channel);
    }
};

#endif // _IMAGE_CLASS_H
