#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "image.h"

struct OutputData
{
    inline static const std::string value_0 = "0";
    inline static const std::string value_1 = "1";
    inline static const std::string value_2 = "2";
    inline static const std::string value_3 = "3";
    inline static const std::string value_4 = "4";
    inline static const std::string value_5 = "5";
    inline static const std::string value_6 = "6";
    inline static const std::string value_7 = "7";
    inline static const std::string value_8 = "8";
    inline static const std::string value_9 = "9";

    static std::string getValue(int key)
    {
        if (key == 0)
            return value_0;
        else if (key == 1)
            return value_1;
        else if (key == 2)
            return value_2;
        else if (key == 3)
            return value_3;
        else if (key == 4)
            return value_4;
        else if (key == 5)
            return value_5;
        else if (key == 6)
            return value_6;
        else if (key == 7)
            return value_7;
        else if (key == 8)
            return value_8;
        else if (key == 9)
            return value_9;
        else
            return "Не смог определить!";
    }
};

std::vector<std::vector<double>> CreateWeightLayer(int count, int size)
{
    std::vector<std::vector<double>> matrix_weight_layer;
    std::srand(std::time(nullptr));

    for (int index = 0; index < count; ++index)
    {
        std::vector<double> weight_layer;
        for (int i = 0; i < size; ++i)
        {
            weight_layer.push_back((double)(std::rand() % 199 - 99) / 100);
        }
        matrix_weight_layer.push_back(weight_layer);
    }
    return matrix_weight_layer;
}

int PredictFunction(double value, float threshold = 0.8)
{
    return (value > threshold) ? 1 : 0;
}

void AdjustWeights(std::vector<std::vector<double>> &matrix_weight_layer,
                   std::vector<std::vector<int>> &input_data,
                   std::vector<int> vector_prediction,
                   int correct_layer_index,
                   float learning_rate)
{
    for (int index = 0; index < matrix_weight_layer.size(); ++index)
    {

        int error;
        if (index == correct_layer_index)
            error = 1 - vector_prediction[index];
        else
            error = 0 - vector_prediction[index];

        for (int i = 0; i < input_data.size(); ++i)
        {
            for (int j = 0; j < input_data.size(); ++j)
            {
                if (input_data[i][j])
                {
                    matrix_weight_layer[index][i * input_data.size() + j] += learning_rate * error * input_data[i][j];
                }
            }
        }
    }
}

std::vector<double> GetWeightedSum(std::vector<std::vector<double>> &matrix_weight_layer,
                                   std::vector<std::vector<int>> &input_data)
{
    std::vector<double> vector_weighted_sum;
    int a = 0;
    for (auto weight_layer : matrix_weight_layer)
    {
        double weighted_sum = 0;
        for (int i = 0; i < input_data.size(); ++i)
        {
            for (int j = 0; j < input_data.size(); ++j)
            {
                if (input_data[i][j])
                    weighted_sum += input_data[i][j] * weight_layer[i * input_data.size() + j];
            }
        }
        // std::cout << "W=> " << a << "   " << weighted_sum << "\n";
        vector_weighted_sum.push_back(weighted_sum);
        ++a;
    }

    return vector_weighted_sum;
}
int GetCorrectPosition(std::vector<int> &vector_prediction)
{
    int i = 0;
    for (int prediction : vector_prediction)
    {
        if (prediction)
            return i;
        ++i;
    }
    return -1;
}

std::string GetResult(std::vector<std::vector<double>> &matrix_weight_layer,
                      std::vector<std::vector<int>> &input_data)
{
    std::vector<double> vector_weighted_sum = GetWeightedSum(matrix_weight_layer, input_data);
    std::vector<int> vector_prediction;
    int max_index = 0;
    int correct_index = -1;
    int count_prediction = 0;
    int i = 0;
    for (double weighted_sum : vector_weighted_sum)
    {
        if (vector_weighted_sum[max_index] < vector_weighted_sum[i])
            max_index = i;
        int prediction = PredictFunction(weighted_sum);
        if (prediction)
        {
            count_prediction++;
            correct_index = i;
        }
        vector_prediction.push_back(prediction);
        ++i;
    }
    // std::cout << "\n";
    // if (count_prediction > 1)
    // {
    //     correct_index = -1;
    // }
    return OutputData::getValue(max_index);
}

void Traning(std::vector<std::vector<double>> &matrix_weight_layer,
             std::vector<std::vector<int>> &input_data,
             int answer,
             double learning_rate)
{
    std::vector<double> vector_weighted_sum = GetWeightedSum(matrix_weight_layer, input_data);
    std::vector<int> vector_prediction;

    int i = 0;
    for (double weighted_sum : vector_weighted_sum)
    {
        int prediction = PredictFunction(weighted_sum);
        vector_prediction.push_back(prediction);
        ++i;
    }
    // int correct_position = GetCorrectPosition(vector_prediction);

    AdjustWeights(matrix_weight_layer, input_data, vector_prediction, answer, learning_rate);
    // std::vector<double> vector_weighted_sum_2 = GetWeightedSum(matrix_weight_layer, input_data);
}

void TraningOnImages(std::vector<std::vector<double>> &matrix_weight_layer,
                     const int count = 50, double learning_rate = 0.01)
{
    int epochs = 1;

    // while (epochs <= 1000)
    {
        for (int number = 0; number < 10; ++number)
        {
            std::string str_number = std::to_string(number);
            for (int img_count = 0; img_count < count; ++img_count)
            {
                std::string end_image;
                if (img_count < 10)
                {
                    end_image = "00" + std::to_string(img_count);
                }
                else if (img_count < 100)
                {
                    end_image = "0" + std::to_string(img_count);
                }
                else
                {
                    end_image = std::to_string(img_count);
                }
                std::string image_path = ".\\\\mnist\\train\\" + str_number + "_000" + end_image + ".png";
                const char *cc_image_path = image_path.c_str();
                std::vector<std::vector<int>> input_data = ReadImage(cc_image_path);
                Traning(matrix_weight_layer, input_data, number, learning_rate);
                // system("pause");
            }
        }
        // if (epochs % 100 == 0)
        //     std::cout << "Эпоха " << epochs << " прошла успешно\n";
        // ++epochs;
        // system("pause");
    }
}
float TestingOnImages(std::vector<std::vector<double>> &matrix_weight_layer, const int count = 50, std::string test_dir = "test")
{
    int correct_ctesting = 0;
    for (int number = 0; number < 10; ++number)
    {
        std::string str_number = std::to_string(number);
        for (int img_count = 0; img_count < count; ++img_count)
        {
            std::string end_image;
            if (img_count < 10)
            {
                end_image = "00" + std::to_string(img_count);
            }
            else if (img_count < 100)
            {
                end_image = "0" + std::to_string(img_count);
            }
            else
            {
                end_image = std::to_string(img_count);
            }
            std::string image_path = ".\\\\mnist\\" + test_dir + "\\" + str_number + "_000" + end_image + ".png";
            const char *cc_image_path = image_path.c_str();
            std::vector<std::vector<int>> input_data = ReadImage(cc_image_path);
            std::string answer = GetResult(matrix_weight_layer, input_data);
            if (answer == std::to_string(number))
                ++correct_ctesting;
        }
    }
    // std::cout << correct_ctesting << "\n";
    // std::cout << "Процент правильных ответов при тестировании на " << count * 10
    //           << " изображений для каждой цифры: "
    //           << ((float)correct_ctesting / (count * 10)) * 100 << "%\n";
    return (((float)correct_ctesting / (count * 10)) * 100);
}