#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "stb_image.h"

char asacii(float brightness)
{
    int n = brightness / 3.65;
    if (n > 65)
        n = 69;

    const char *seventy = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    return seventy[n];
}

int main()
{

    std::string filename_str;
    std::cin >> filename_str;
    int n = filename_str.length();
    char filename[n + 1];
    strcpy(filename, filename_str.c_str());

    int x,
        y, channels;
    unsigned char *data = stbi_load(filename, &x, &y, &channels, 0);

    if (data != NULL)
    {
        std::cout << "READ! with width:" << x << " height:" << y << " total pixels:" << x * y << "\n";
    }
    else
    {
        std::cout << "load failed\n";
        return -1;
    }
    int bod;
    std::cin >> bod;
    int com = std::max(x, y) / bod;

    // std::cin >> com;
    if (com < 1)
        com = 1;
    for (int i = 0; i < y; i += com)
    {
        std::cout << "    ";
        for (int j = 0; j < x; j += com)
        {
            float R, G, B;
            R = data[i * x * 3 + j * 3 + 0];
            G = data[i * x * 3 + j * 3 + 1];
            B = data[i * x * 3 + j * 3 + 2];
            float brightness = 0.299 * R + 0.587 * G + 0.114 * B;
            char X = asacii(brightness);
            std::cout << X << " ";
        }
        std::cout << "   " << "\n";
    }
    stbi_image_free(data);
}