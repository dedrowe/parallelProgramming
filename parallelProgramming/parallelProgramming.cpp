#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <direct.h>

int** create_matrix(size_t height, size_t width) {
    int** matrix = new int*[width];
    for (size_t i = 0; i < width; ++i) {
        matrix[i] = new int[height];
        for (size_t j = 0; j < height; ++j)
            matrix[i][j] = rand() % 100;
    }
    return matrix;
}

void delete_matrix(int** matrix, size_t height, size_t width) {
    for (size_t i = 0; i < width; ++i) {
        delete matrix[i];
    }
    delete matrix;
}

int** multiply_matrices(int** a, int** b, size_t height, size_t width) {
    int** result = create_matrix(height, width);
    int cell;
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j) {
            cell = 0;
            for (size_t k = 0; k < width; ++k)
                cell += a[k][j] * b[i][k];
            result[i][j] = cell;
        }
    return result;
}

void write_results(const std::string& path, int** matrix, size_t height, size_t width, double time) {

    std::ofstream file(path);
    file << "{\"matrix\": [";
    for (size_t i = 0; i < height; ++i) {
        file << "[";
        for (size_t j = 0; j < width; ++j) {
            file << matrix[j][i];
            if (j < width - 1)
                file << ",";
        }
        if (i < height - 1)
            file << "],";
    }
    file << "]],\"size\": " << height * width << ", \"time\": " << time << "}";
    file.close();
}

void write_statistics(std::string path, size_t* matrix_size_array, double* time_array, size_t array_len) {
    std::ofstream file(path);
    file << "time: ";
    for (size_t i = 0; i < array_len; ++i) {
        file << time_array[i] << " ";
    }
    file << std::endl;
    file << "matrix size: ";
    for (size_t i = 0; i < array_len; ++i) {
        file << matrix_size_array[i] << " ";
    }
}

void validate_result(const std::string& script_path, const std::string& first_matrix_path, const std::string& second_matrix_path, const std::string& result_path) {
    system(std::string("python " + script_path + " " + first_matrix_path + " " + second_matrix_path + " " + result_path).c_str());
}

int main()
{
    srand(time(0));
    size_t arr_len = 6;
    size_t arr[] = { 10, 50, 100, 200, 500, 1000 };
    double* time_arr =  new double[arr_len];
    size_t multiplying_count = 100;
    int** result = NULL, **a = NULL, **b = NULL;
    std::chrono::steady_clock::time_point start, end;
    double time;
    std::string results_folder = "results", a_path, b_path, res_path, validator_path = "validator\\main.py";
    _mkdir(results_folder.c_str());
    for (size_t i = 0; i < arr_len; ++i) {
        _mkdir(std::string(results_folder + "\\" + std::to_string(arr[i])).c_str());
        a_path = std::string(results_folder + "\\" + std::to_string(arr[i]) + "\\first_matrix_" + std::to_string(arr[i]) + ".txt");
        b_path = std::string(results_folder + "\\" + std::to_string(arr[i]) + "\\second_matrix_" + std::to_string(arr[i]) + ".txt");
        res_path = std::string(results_folder + "\\" + std::to_string(arr[i]) + "\\result_" + std::to_string(arr[i]) + ".txt");
        std::cout << "Now multiplying matrices " << arr[i] << "*" << arr[i] << std::endl;
        time = 0;
        for (size_t j = 0; j < multiplying_count; ++j) {
            a = create_matrix(arr[i], arr[i]);
            write_results(a_path, a, arr[i], arr[i], 0);
            b = create_matrix(arr[i], arr[i]);
            write_results(b_path, b, arr[i], arr[i], 0);
            start = std::chrono::steady_clock::now();
            result = multiply_matrices(a, b, arr[i], arr[i]);
            end = std::chrono::steady_clock::now();
            write_results(res_path, result, arr[i], arr[i], time);

            delete_matrix(result, arr[i], arr[i]);
            delete_matrix(a, arr[i], arr[i]);
            delete_matrix(b, arr[i], arr[i]);

            validate_result(validator_path, a_path, b_path, res_path);
        }
        time += std::chrono::duration <double>(end - start).count();
        double average_time = time / multiplying_count;
        std::cout << "Average time: " << average_time << std::endl;
        time_arr[i] = average_time;
    }
    write_statistics("stats.txt", arr, time_arr, arr_len);
    return 0;
}
