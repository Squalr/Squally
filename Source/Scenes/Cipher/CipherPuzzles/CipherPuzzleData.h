#pragma once
#include <tuple>

#include "Engine/SmartNode.h"

class CipherPuzzleData : public SmartNode
{
public:
	static CipherPuzzleData* create(
		std::vector<std::tuple<std::string, std::string>> inputOutputMapEasy,
		std::vector<std::tuple<std::string, std::string>> inputOutputMapHard,
		std::vector<std::string> rewards,
		std::vector<std::string> bonusRewards,
		bool isHardMode);
	
	std::vector<std::tuple<std::string, std::string>> getInputOutputMapEasy();
	std::vector<std::tuple<std::string, std::string>> getInputOutputMapHard();
	std::vector<std::string> getRewards();
	std::vector<std::string> getBonusRewards();
	bool isHardModeEnabled();

private:
	typedef SmartNode super;
	CipherPuzzleData(std::vector<std::tuple<std::string, std::string>> inputOutputMapEasy,
		std::vector<std::tuple<std::string, std::string>> inputOutputMapHard,
		std::vector<std::string> rewards,
		std::vector<std::string> bonusRewards,
		bool isHardMode);
	~CipherPuzzleData();

	void initializeListeners() override;

	std::vector<std::tuple<std::string, std::string>> inputOutputMapEasy;
	std::vector<std::tuple<std::string, std::string>> inputOutputMapHard;
	std::vector<std::string> rewards;
	std::vector<std::string> bonusRewards;
	bool isHardMode;
};
