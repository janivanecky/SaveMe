#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <istream>

class ScoreManager
{
public:
	static int GetTopScores();
	static void SetScore(const int score);
private:
	ScoreManager();
};