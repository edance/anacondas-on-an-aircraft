#pragma once
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Score
{
public:
	Score();
	void render() const;
	void changeScore(const int amount_);
	void resetScore();
	const int getScore() const;

private:
	int _currentScore;
};

