#ifndef NN_LINEAR_REGRESSION_HPP_
#define NN_LINEAR_REGRESSION_HPP_

#include <memory>
#include <string>
#include <ostream>

namespace ANN {

typedef enum {
	LEAST_SQUARES = 0,
	GRADIENT_DESCENT
} regression_method;

template<typename T>
class LinearRegression {
	template<typename U>
	friend std::ostream& operator << (std::ostream& out, const LinearRegression<U>& lr);

public:
	LinearRegression() = default;
	void set_regression_method(regression_method method);
	int init(const T* x, const T* y, int length);
	int train(const std::string& model, T learning_rate = 0, int iterations = 0);
	int load_model(const std::string& model) const;
	T predict(T x) const; // y = wx+b

private:
	int gradient_descent();
	int least_squares();
	int store_model() const;

	regression_method method;
	std::unique_ptr<T[]> x, y;
	std::string model = "";
	int iterations = 1000;
	int length = 0;
	T learning_rate = 0.001f;
	T weight = 0;
	T bias = 0;
};

} // namespace ANN

#endif // NN_LINEAR_REGRESSION_HPP_