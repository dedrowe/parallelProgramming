#include "BasicMatrixMultiplier.h"
#include "OpenMPMatrixMultiplier.h"
#include <vector>

void write_statistics(std::string path, size_t* matrix_size_array, double* time_arr, double* avg_time_array, size_t avg_array_len, size_t time_arr_len) {
    std::ofstream file(path);
    file << "times: ";
    for (size_t i = 0; i < time_arr_len; ++i) {
        file << time_arr[i] << ", ";
    }
    file << std::endl;
    file << "avg_time: ";
    for (size_t i = 0; i < avg_array_len; ++i) {
        file << avg_time_array[i] << ", ";
    }
    file << std::endl;
    file << "matrix size: ";
    for (size_t i = 0; i < avg_array_len; ++i) {
        file << matrix_size_array[i] << ", ";
    }
}

int main()
{
    srand(time(0));
    bool validating = false;
    size_t const arr_len = 6;
    size_t const multiplying_count = 100;
    size_t arr[] = { 10, 50, 100, 200, 500, 1000 };
    double time_arr[multiplying_count]{}, avg_time_arr[arr_len]{ 0 }, time;
    std::string validator_path = "validator\\main.py";
    std::vector< MatrixMultiplier* > multiplying_ways;
    multiplying_ways.push_back(new BasicMatrixMultiplier(arr[0], "results_basic", validator_path, "stats_basic.txt", validating));
    multiplying_ways.push_back(new OpenMPMatrixMultiplier(arr[0], "results_openMP", validator_path, "stats_openMP.txt", validating));
    for (auto & way : multiplying_ways) {
        for (size_t i = 0; i < arr_len; ++i) {
            avg_time_arr[i] = 0;
            std::cout << "Now multiplying matrices " << arr[i] << "*" << arr[i] << std::endl;
            way->set_matrices_size(arr[i]);
            for (size_t j = 0; j < multiplying_count; ++j) {
                time = way->make_experiment();
                avg_time_arr[i] += time;
                if (i == arr_len - 1)
                    time_arr[j] = time;
            }
            avg_time_arr[i] /= multiplying_count;
            std::cout << "Average time: " << avg_time_arr[i] << std::endl;
        }
        write_statistics(way->get_stats_path(), arr, time_arr, avg_time_arr, arr_len, multiplying_count);
    }
    for (auto& i : multiplying_ways)
        delete i;
    return 0;
}
