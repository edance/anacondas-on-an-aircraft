#pragma once
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class PowerBar
{
public:
	PowerBar();
	void render() const;
	const float getAmount() const;
	void changeAmount(const float amount_);

private:
	const float _maxAmount;
	float _currentAmount;
};

