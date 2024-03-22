#include "BasicMatrixMultiplier.h"
#include <chrono>

double BasicMatrixMultiplier::multiply_matrices() {
	std::chrono::steady_clock::time_point start, end;
	start = std::chrono::steady_clock::now();
	for (size_t i = 0; i < _matrices_size; ++i) {
		for (size_t j = 0; j < _matrices_size; ++j) {
			_result[i][j] = 0;
			for (size_t k = 0; k < _matrices_size; ++k)
				_result[i][j] += _a[k][j] * _b[i][k];
		}
	}
	end = std::chrono::steady_clock::now();
	return std::chrono::duration <double>(end - start).count();
}

BasicMatrixMultiplier::BasicMatrixMultiplier() {
	this->_matrices_size = 0;
	this->_result_folder = "";
	this->_validator_path = "";
}

BasicMatrixMultiplier::BasicMatrixMultiplier(int size, const std::string& res_path, const std::string& validator_path, const std::string& stats_path, bool validating) {
	this->_matrices_size = size;
	this->_result_folder = res_path;
	_mkdir(_result_folder.c_str());
	this->_stats_path = stats_path;
	this->_validator_path = validator_path;
	this->_validating = validating;
}

BasicMatrixMultiplier::~BasicMatrixMultiplier() {
	delete_matrix(_result);
	delete_matrix(_a);
	delete_matrix(_b);
}
