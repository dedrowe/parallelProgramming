#include "MatrixMultiplier.h"


int** MatrixMultiplier::create_matrix() {
	int** matrix = new int* [_matrices_size];
	for (size_t i = 0; i < _matrices_size; ++i) {
		matrix[i] = new int[_matrices_size];
		for (size_t j = 0; j < _matrices_size; ++j)
			matrix[i][j] = rand() % 100;
	}
	return matrix;
}

void MatrixMultiplier::delete_matrix(int** matrix) {
	for (size_t i = 0; i < _matrices_size; ++i) {
		delete matrix[i];
	}
	delete matrix;
}

void MatrixMultiplier::write_results(const std::string& path, int** matrix, double time) {
	std::ofstream file(path);
	file << "{\"matrix\": [";
	for (size_t i = 0; i < _matrices_size; ++i) {
		file << "[";
		for (size_t j = 0; j < _matrices_size; ++j) {
			file << matrix[j][i];
			if (j < _matrices_size - 1)
				file << ",";
		}
		if (i < _matrices_size - 1)
			file << "],";
	}
	file << "]],\"size\": " << _matrices_size * _matrices_size;
	if (time > 0)
		file << ", \"time\": " << time;
	file << "}";
	file.close();
}

void MatrixMultiplier::validate_result(const std::string& script_path, const std::string& first_matrix_path, const std::string& second_matrix_path, const std::string& result_path) {
	system(std::string("python " + script_path + " " + first_matrix_path + " " + second_matrix_path + " " + result_path).c_str());
}

void MatrixMultiplier::define_matrices() {
	_a = create_matrix();
	_b = create_matrix();
	_result = create_matrix();

}

double MatrixMultiplier::make_experiment()
{
	_mkdir(std::string(_result_folder + "\\" + std::to_string(_matrices_size)).c_str());
	std::string a_path = std::string(_result_folder + "\\" + std::to_string(_matrices_size) + "\\first_matrix_" + std::to_string(_matrices_size) + ".json");
	std::string b_path = std::string(_result_folder + "\\" + std::to_string(_matrices_size) + "\\second_matrix_" + std::to_string(_matrices_size) + ".json");
	std::string res_path = std::string(_result_folder + "\\" + std::to_string(_matrices_size) + "\\result_" + std::to_string(_matrices_size) + ".json");
	define_matrices();
	write_results(a_path, _a);
	write_results(b_path, _b);
	double time = multiply_matrices();
	write_results(res_path, _result, time);

	delete_matrix(_result);
	delete_matrix(_a);
	delete_matrix(_b);
	if (_validating)
		validate_result(_validator_path, a_path, b_path, res_path);
	return time;
}

void MatrixMultiplier::set_matrices_size(int size) {
	this->_matrices_size = size;
}

std::string MatrixMultiplier::get_stats_path()
{
	return _stats_path;
}
