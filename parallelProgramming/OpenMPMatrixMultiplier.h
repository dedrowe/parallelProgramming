#pragma once
#include "MatrixMultiplier.h"
class OpenMPMatrixMultiplier : public MatrixMultiplier {
	double multiply_matrices() override;

public:
	OpenMPMatrixMultiplier();
	OpenMPMatrixMultiplier(int size, const std::string& res_path, const std::string& validator_path, const std::string& stats_path, bool validating);

	~OpenMPMatrixMultiplier();
};

