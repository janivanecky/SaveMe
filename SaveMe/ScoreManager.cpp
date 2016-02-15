#include "ScoreManager.h"

const std::string fileName = "score.scr";

ScoreManager::ScoreManager()
{

}

int ScoreManager::GetTopScores()
{
	std::ifstream stream(fileName);
	std::string line;

	int highscore(0);
	if (stream.is_open())
	{
		while (std::getline(stream, line))
		{
			int score = (atoi(line.c_str()));
			if (score > 0)
				highscore = score;
		}
		stream.close();
	}

	return highscore;
}

void ScoreManager::SetScore(const int score)
{
	std::ofstream stream(fileName);
	stream << score << std::endl;
}