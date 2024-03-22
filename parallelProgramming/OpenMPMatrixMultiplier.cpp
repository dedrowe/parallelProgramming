#include "OpenMPMatrixMultiplier.h"
#include <omp.h>

double OpenMPMatrixMultiplier::multiply_matrices() {
	double start, end;
	int** a = _a, **b = _b, **result = _result;
	int i, j, k;
	omp_set_dynamic(1);
	start = omp_get_wtime();
#pragma omp parallel for shared(a, b, result) private(i, j, k)
	for (i = 0; i < _matrices_size; ++i) {
		for (j = 0; j < _matrices_size; ++j) {
			_result[i][j] = 0;
			for (k = 0; k < _matrices_size; ++k)
				_result[i][j] += _a[k][j] * _b[i][k];
		}
	}
	end = omp_get_wtime();
	return end - start;
}

OpenMPMatrixMultiplier::OpenMPMatrixMultiplier() {
	this->_matrices_size = 0;
	this->_result_folder = "";
	this->_validator_path = "";
}

OpenMPMatrixMultiplier::OpenMPMatrixMultiplier(int size, const std::string& res_path, const std::string& validator_path, const std::string& stats_path, bool validating) {
	this->_matrices_size = size;
	this->_result_folder = res_path;
	_mkdir(_result_folder.c_str());
	this->_stats_path = stats_path;
	this->_validator_path = validator_path;
	this->_validating = validating;
}

OpenMPMatrixMultiplier::~OpenMPMatrixMultiplier() {
	delete_matrix(_result);
	delete_matrix(_a);
	delete_matrix(_b);
}
