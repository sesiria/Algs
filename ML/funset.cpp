#include "funset.hpp"
#include <iostream>
#include <vector>
#include "linear_regression.hpp"

constexpr char ModelName[] = "D:/linear_regression.model";

// ============================ linear regression =============================
int test_linear_regression_train()
{
	std::vector<float> x{6.2f, 9.5f, 10.5f, 7.7f, 8.6f, 6.9f, 7.3f, 2.2f, 5.7f, 2.f,
		2.5f, 4.f, 5.4f, 2.2f, 7.2f, 12.2f, 5.6f, 9.f, 3.6f, 5.f,
		11.3f, 3.4f, 11.9f, 10.5f, 10.7f, 10.8f, 4.8f};
	std::vector<float> y{ 29.f, 44.f, 36.f, 37.f, 53.f, 18.f, 31.f, 14.f, 11.f, 11.f,
		22.f, 16.f, 27.f, 9.f, 29.f, 46.f, 23.f, 39.f, 15.f, 32.f,
		34.f, 17.f, 46.f, 42.f, 43.f, 34.f, 19.f };
	CHECK(x.size() == y.size());
	ANN::LinearRegression<float> lr;
	lr.set_regression_method(ANN::GRADIENT_DESCENT);
	lr.init(x.data(), y.data(), x.size());
	float learning_rate{ 0.001f };
	int iterations{ 1000 };
	std::string model{ ModelName };
	int ret = lr.train(model, learning_rate, iterations);
	if (ret != 0) {
		fprintf(stderr, "train fail\n");
		return -1;
	}
	std::cout << lr << std::endl; // y = wx + b
	return 0;
}
int test_linear_regression_predict()
{
	ANN::LinearRegression<float> lr;
	std::string model{ ModelName };
	int ret = lr.load_model(model);
	if (ret != 0) {
		fprintf(stderr, "load model fail: %s\n", model.c_str());
		return -1;
	}
	float x = 13.8f;
	float result = lr.predict(x);
	fprintf(stdout, "input value: %f, result value: %f\n", x, result);
	return 0;
}