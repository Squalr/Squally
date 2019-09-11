#pragma once
#include <tuple>

#include "Engine/SmartNode.h"

class CipherPuzzleData : public SmartNode
{
public:
	static CipherPuzzleData* create(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> rewards,
		std::vector<std::string> bonusRewards);
	
	CipherPuzzleData* clone();
	std::vector<std::tuple<unsigned char, unsigned char>> getInputOutputMapEasy();
	std::vector<std::tuple<unsigned char, unsigned char>> getInputOutputMapHard();
	std::vector<std::string> getRewards();
	std::vector<std::string> getBonusRewards();

private:
	typedef SmartNode super;
	CipherPuzzleData(std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> rewards,
		std::vector<std::string> bonusRewards);
	~CipherPuzzleData();

	void initializeListeners() override;

	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy;
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard;
	std::vector<std::string> rewards;
	std::vector<std::string> bonusRewards;
};
