

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <vector>

std::vector<std::vector<int>> ReadImage(const char *file_name)
{
    int width, height, channels;
    std::vector<std::vector<int>> binaryMatrix;

    unsigned char *data = stbi_load(file_name, &width, &height, &channels, 1); // 1 канал = grayscale
    if (!data)
    {
        std::cerr << "Ошибка загрузки!" << std::endl;
        return binaryMatrix;
    }

    for (int i = 0; i < height; ++i)
    {
        std::vector<int> demo_vector;
        for (int j = 0; j < width; ++j)
        {
            int pixel = data[i * width + j];
            demo_vector.push_back((pixel > 128) ? 1 : 0);
        }
        binaryMatrix.push_back(demo_vector);
    }

    stbi_image_free(data);

    return binaryMatrix;
}
