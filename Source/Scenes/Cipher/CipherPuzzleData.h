#pragma once
#include <tuple>

#include "Engine/SmartNode.h"

class CipherPuzzleData : public SmartNode
{
public:
	static CipherPuzzleData* create(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> easyTokens,
		std::vector<std::string> hardTokens,
		std::vector<std::string> rewards,
		std::string bonusReward);
	
	CipherPuzzleData* clone();
	bool hasHardMode();
	std::vector<std::tuple<unsigned char, unsigned char>> getInputOutputMapEasy();
	std::vector<std::tuple<unsigned char, unsigned char>> getInputOutputMapHard();
	std::vector<std::string> getEasyTokens();
	std::vector<std::string> getHardTokens();
	std::vector<std::string> getRewards();
	std::string getBonusReward();

private:
	typedef SmartNode super;
	CipherPuzzleData(std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> easyTokens,
		std::vector<std::string> hardTokens,
		std::vector<std::string> rewards,
		std::string bonusReward);
	~CipherPuzzleData();

	void initializeListeners() override;

	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy;
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard;
	std::vector<std::string> easyTokens;
	std::vector<std::string> hardTokens;
	std::vector<std::string> rewards;
	std::string bonusReward;
};
