#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

class neuron
{
public:
	neuron();
	neuron(std::vector<int> & n_weiges);
	~neuron();

	matrix<float> resulting_func(matrix<float>& inp);
private:
	std::vector<int> n_weiges;

	std::vector<matrix<float>> weiges;
};

