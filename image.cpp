#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "stb_image.h"

const char *shades = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

float cal_brirghtness(float R, float G, float B)
{

    float brightness = 0.299 * R + 0.587 * G + 0.114 * B;
    return brightness;
}

char asacii(float brightness, bool inverse_flag)
{
    int n = brightness / 3.65;
    const char *seventy = shades;
    if (inverse_flag)
    {
        return seventy[69 - n];
    }
    else
    {
        return seventy[n];
    }
}

void display(int x, int y, unsigned char *data)
{
    int bod;
    std::cout << "how many the boarder is :";
    std::cin >> bod;
    bool inverse_flag = true;
    std::cout << "Inversed?[Y/N]";
    std::string ans;
    std::cin >> ans;
    if (ans == "Y")
    {
        inverse_flag = true;
    }
    else
    {
        inverse_flag = false;
    }
    int com = std::max(x, y) / bod;
    if (com * bod < std::max(x, y))
        com++;

    // std::cin >> com;
    if (com < 1)
        com = 1;

    // int k = 1;
    std::cout << "# ";
    for (int j = 0; j < x; j += com)
    {
        std::cout << "# ";
    }
    std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < y; i += com)
    {

        // std::cout << "    ";
        std::cout << "# ";

        for (int j = 0; j < x; j += com)
        {
            /*R = data[i * x * 3 + j * 3 + 0];
                G = data[i * x * 3 + j * 3 + 1];
                B = data[i * x * 3 + j * 3 + 2];*/
            int pos = i * x * 3 + j * 3;
            float brightness = cal_brirghtness(data[pos], data[pos + 1], data[pos + 2]);
            char X = asacii(brightness, inverse_flag);
            std::cout << X << " ";
        }
        std::cout << "#" << "\n";
    }
    std::cout << "# ";
    for (int j = 0; j < x; j += com)
    {
        std::cout << "# ";
    }
    std::cout << "#";
    std::cout << std::endl;
    stbi_image_free(data);
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
    display(x, y, data);
}