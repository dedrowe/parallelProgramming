#pragma once
#include <string>
#include <fstream>
#include <direct.h>
#include <iostream>

class MatrixMultiplier {
protected:
	int** _result = nullptr, ** _a = nullptr, ** _b = nullptr;
	std::string _result_folder, _validator_path, _stats_path;
	int _matrices_size;
	bool _validating;

	int** create_matrix();
	void delete_matrix(int** matrix);
	void write_results(const std::string& path, int** matrix, double time = -1);
	void validate_result(const std::string& script_path, const std::string& first_matrix_path, const std::string& second_matrix_path, const std::string& result_path);
	virtual double multiply_matrices() = 0;
	void define_matrices();
public:

	double make_experiment();

	void set_matrices_size(int size);
	std::string get_stats_path();
};
