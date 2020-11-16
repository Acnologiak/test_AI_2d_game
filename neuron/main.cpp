#include <iostream>

#include "neuron.h"


void print_matrix(matrix<float> &m)
{
	for (int i = 0; i < m.size1(); i++)
	{
		for (int j = 0; j < m.size2(); j++)
		{
			std::cout << m(i, j) << " ";
		}
		std::cout << std::endl;
	}
}


int main()
{
	matrix<float> m_1(1, 2);
	m_1(0, 0) = 1;
	m_1(0, 1) = 1;

	std::vector<int> v{ 2, 3, 2 };

	neuron n(v);

	matrix<float> m_2 = n.resulting_func(m_1);

	print_matrix(m_2);

	return 0;
}