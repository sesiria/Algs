#include "linear_regression.hpp"
#include <fstream>
#include <random>
#include <algorithm>
#include <numeric>

#ifndef DBL_EPSILON
#define DBL_EPSILON __DBL_EPSILON__
#endif

namespace ANN {

template<typename T>
void LinearRegression<T>::set_regression_method(regression_method method)
{
	this->method = method;
}

template<typename T>
int LinearRegression<T>::init(const T* x, const T* y, int length)
{
	if (length < 3) {
		fprintf(stderr, "number of points must be greater than 2: %d\n", length);
		return -1;
	}

	this->x.reset(new T[length]);
	this->y.reset(new T[length]);

	for (int i = 0; i < length; ++i) {
		this->x[i] = x[i];
		this->y[i] = y[i];
	}

	this->length = length;

	return 0;
}

template<typename T>
int LinearRegression<T>::train(const std::string& model, T learning_rate, int iterations)
{
	this->learning_rate = learning_rate;
	this->iterations = iterations;
	this->model = model;

	if (this->method == LEAST_SQUARES) {
		least_squares();
	} else if (this->method == GRADIENT_DESCENT) {
		gradient_descent();
	} else {
		fprintf(stderr, "invalid linear regression method\n");
		return -1;
	}

	return store_model();
}

template<typename T>
int LinearRegression<T>::store_model() const
{
	std::ofstream file;
	file.open(model.c_str(), std::ios::binary);
	if (!file.is_open()) {
		fprintf(stderr, "open file fail: %s\n", model.c_str());
		return -1;
	}

	int m = method;
	file.write((char*)&m, sizeof(m));
	file.write((char*)&weight, sizeof(weight));
	file.write((char*)&bias, sizeof(bias));

	file.close();

	return 0;
}

template<typename T>
int LinearRegression<T>::load_model(const std::string& model) const
{
	std::ifstream file;
	file.open(model.c_str(), std::ios::binary);
	if (!file.is_open()) {
		fprintf(stderr, "open file fail: %s\n", model.c_str());
		return -1;
	}

	int m{ -1 };
	file.read((char*)&m, sizeof(m)* 1);
	file.read((char*)&weight, sizeof(weight)* 1);
	file.read((char*)&bias, sizeof(bias)* 1);

	file.close();

	return 0;
}

template<typename T>
T LinearRegression<T>::predict(T x) const
{
	return weight * x + bias;
}

template<typename T>
int LinearRegression<T>::gradient_descent()
{
	std::random_device rd; std::mt19937 generator(rd());
	std::uniform_real_distribution<T> distribution(0, 0.5);
	weight = distribution(generator);;
	bias = distribution(generator);;
	int count{ 0 };

	std::unique_ptr<T[]> error(new T[length]), error_x(new T[length]);

	for (int i = 0; i < iterations; ++i) {
		for (int j = 0; j < length; ++j) {
			error[j] = weight * x[j] + bias - y[j];
			error_x[j] = error[j] * x[j];
		}

		T error_ = std::accumulate(error.get(), error.get() + length, (T)0) / length;
		T error_x_ = std::accumulate(error_x.get(), error_x.get() + length, (T)0) / length;

		// error = p(i) - y(i)
		// bias(i+1) = bias(i) - learning_rate*error
		bias = bias - learning_rate * error_;
		// weight(i+1) = weight(i) - learning_rate*error*x
		weight = weight - learning_rate * error_x_;

		++count;
		if (count % 100 == 0)
			fprintf(stdout, "iteration %d\n", count);
	}

	return 0;
}

template<typename T>
int LinearRegression<T>::least_squares()
{
	T sum_x{ 0 }, sum_y{ 0 }, sum_x_squared{ 0 }, sum_xy{ 0 };

	for (int i = 0; i < length; ++i) {
		sum_x += x[i];
		sum_y += y[i];
		sum_x_squared += x[i] * x[i];
		sum_xy += x[i] * y[i];
	}

	if (fabs(length * sum_x_squared - sum_x * sum_x) > DBL_EPSILON) {
		weight = (length * sum_xy - sum_y * sum_x) / (length * sum_x_squared - sum_x * sum_x); // slope
		bias = (sum_x_squared * sum_y - sum_x * sum_xy) / (length * sum_x_squared - sum_x * sum_x); // intercept
	} else {
		weight = 0;
		bias = 0;
	}

	return 0;
}

template<typename T>
std::ostream& operator << (std::ostream& out, const LinearRegression<T>& lr)
{
	out << "result: y = " << lr.weight << "x + " << lr.bias;
	return out;
}

template std::ostream& operator << (std::ostream& out, const LinearRegression<float>& lr);
template std::ostream& operator << (std::ostream& out, const LinearRegression<double>& lr);
template class LinearRegression<float>;
template class LinearRegression<double>;

} // namespace ANN