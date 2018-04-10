#ifndef FBC_TEST_NN_FUNSET_HPP_
#define FBC_TEST_NN_FUNSET_HPP_
#define CHECK(x) { \
	if (x) {} \
	else { fprintf(stderr, "Check Failed: %s, file: %s, line: %d\n", #x, __FILE__, __LINE__); return -1; } \
}

int test_linear_regression_train();
int test_linear_regression_predict();


#endif