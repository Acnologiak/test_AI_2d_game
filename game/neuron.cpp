#include "neuron.h"


float get_random_number()
{
	return float(rand() % 1000) / 1000.0f;
}


neuron::neuron()
{
}

neuron::neuron(std::vector<int> &_weiges) :
	n_weiges(_weiges)
{
	for (int i=0; i<n_weiges.size()-1; i++)
	{
		weiges.emplace_back(matrix<float>(n_weiges[i], n_weiges[i+1]));
		for (int j = 0; j < n_weiges[i]; j++)
		{
			for (int k = 0; k < n_weiges[i + 1]; k++)
			{
				weiges[i](j, k) = get_random_number();
			}
		}
	}
}

neuron::~neuron()
{
}

matrix<float> neuron::resulting_func(matrix<float>& inp)
{
	matrix<float> out = inp;
	for (int i = 0; i < weiges.size(); i++)
	{
		out = prod(out, weiges[i]);

	}
	return out;
}
