#include <vector>
#include <iostream>
#include <fstream>

void NoiseRemoval(std::vector<std::vector<int>> &matrix, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (matrix[i][j] == 1)
            {
                if (j + 1 <= width and i + 1 <= height)
                    if ((matrix[i][j + 1] == 1) or (matrix[i - 1][j] == 1) or (matrix[i + 1][j + 1] == 1))
                    {
                        j += 1;
                        i += 1;
                        continue;
                    }
                    else
                    {
                        matrix[i][j] = 0;
                    }
            }
        }
    }
}

void ClearMatrix(std::vector<std::vector<int>> &matrix, int width, int height)
{
    for (int i = 0; i < height; i++)

    {
        for (int j = 0; j < width; j++)

        {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(std::vector<std::vector<int>> read_matrix)
{

    std::vector<float> new_vector;
    for (auto vector : read_matrix)
    {
        for (auto number : vector)
        {
            std::cout << number << " ";
        }
        std::cout << "\n";
    }
}

void SaveWeights(const std::vector<std::vector<double>> &matrix_weight_layer, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (auto weight_layer : matrix_weight_layer)
        {
            for (double weight : weight_layer)
            {
                file << weight << "\n";
            }
            file << -999 << "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Ошибка при сохранении в файл\n";
    }
}

std::vector<std::vector<double>> LoadWeights(const std::string &filename)
{
    std::vector<std::vector<double>> matrix_weight_layer;
    std::ifstream file(filename);
    if (file.is_open())
    {
        double weight;
        std::vector<double> weight_layer;
        while (file >> weight)
        {
            if (weight == -999)
            {
                matrix_weight_layer.push_back(weight_layer);
                weight_layer.clear();
            }
            else
            {
                weight_layer.push_back(weight);
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Ошибка при загрузке из файла\n";
    }
    return matrix_weight_layer;
}