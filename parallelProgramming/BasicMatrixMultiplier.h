#pragma once
#include "MatrixMultiplier.h"
class BasicMatrixMultiplier : public MatrixMultiplier {
	double multiply_matrices() override;
public:
	BasicMatrixMultiplier();
	BasicMatrixMultiplier(int size, const std::string& res_path, const std::string& validator_path, const std::string& stats_path, bool validating);

	~BasicMatrixMultiplier();
};

