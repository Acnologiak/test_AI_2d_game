#pragma once

#include "game_data.h"
#include "input.h"
#include "settings.h"
#include "utilities.h"


class players
{
public:
	static players& instance();

	void spawn_bots();
	void move_bots(float);
	void move_bot(creature& b, glm::vec2 v, float alpha);
	void shooting_bots();
	void shooting_bot(creature& b, glm::vec2 v);

	void check_crossing_pl();
	void update_last_position();
	//рух пуль
	void move_bullets(float alpha);
private:
	players() = default;
	game_data& g_data = game_data::instance();
	input& inp = input::instance();
	settings& set = settings::instance();
};


struct nnlay {
	int in;
	int out;
	float matrix;
	float hidden;
	float err;
	float lr = 0.1;
	void updmatrix(float enteredval)
	{
		for (int i = 0; i < out; i++) {
			for (int h = 0; h < out; h++) {
				matrix[h][i] += (lr * err[i] * enteredval[h]);

			}
			matrix[in][out] += (lr * err[i]);
		}

	};

};


void setio(int inp, int out)
{
	h = (float*)malloc((out) * sizeof(float));

	/*matrix = (float**)malloc((inp + 1) * sizeof(float));*/
	for (int i = 0; i < inp+ 1; i++)
	{
		matrix[i] = (float*)malloc(out * sizeof(float));
	}
	for (int i = 0; i < inp + 1; i++)
	{
		for (int o = 0; o < out; o++)
		{
			matrix[i][o] = (((float)qrand() / (float)RAND_MAX) - 0.5) * pow(out, -0.5);
		}
	}

}

void makehidden(float* inputs)
{
	for (int h = 0; h < out; h++)
	{
		float tmpS = 0.0;
		for (int i = 0; i < in; i++)
		{
			tmpS += inputs[inp] * matrix[i][h];
		}
		tmpS += matrix[i][h];
		hidden[h] = sigmoida(tmpS);
	}
};

float gethidden()
{
	return hidden;
};

void calcouterr(float targets)
{
	errors = (float*)malloc((out) * sizeof(float));
	for (int o = 0; o < out; o++)
	{
		errors[o] = (targets[o] - hidden[o]) * sigmoidasderivate(hidden[o]);
	}
};

void calcHidError(float targets, float outweights, int inS, int outS)
{
	errors = (float*)malloc((inS) * sizeof(float));
	for (int hid = 0; hid < inS; hid++)
	{
		errors[hid] = 0.0;
		for (int i = 0; i < outS; i++)
		{
			errors[hid] += targets[i] * outweights[hid][i];
		}
		errors[hid] *= sigmoidasDerivate(hidden[hid]);
	}
};

floatgetErrors()
{
	return errors;
};

float sigmoida(float val)
{
	return (1.0 / (1.0 + exp(-val)));
}

float sigmoidasDerivate(float val)
{
	return (val * (1.0 - val));
};
