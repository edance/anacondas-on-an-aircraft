#pragma once
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class HealthBar
{
public:
	HealthBar();
	void render() const;
	void setHealth(const float amount_);
	void setMaxHealth(const float amount_);

private:
	float _maxHealth;
	float _currentHealth;
};

