#pragma once
#include <tuple>

#include "Engine/SmartNode.h"

class 
CipherPuzzleData : public SmartNode
{
public:
	static CipherPuzzleData* create(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> easyTokens,
		std::vector<std::string> hardTokens,
		std::string bonusReward,
		std::function<void(CipherPuzzleData*, bool)> onUnlock);
	
	CipherPuzzleData* clone();
	bool hasHardMode();
	std::vector<std::tuple<unsigned char, unsigned char>> getInputOutputMapEasy();
	std::vector<std::tuple<unsigned char, unsigned char>> getInputOutputMapHard();
	std::vector<std::string> getEasyTokens();
	std::vector<std::string> getHardTokens();
	std::string getBonusReward();
	std::function<void(CipherPuzzleData*, bool)> onUnlock;

private:
	typedef SmartNode super;
	CipherPuzzleData(std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> easyTokens,
		std::vector<std::string> hardTokens,
		std::string bonusReward,
		std::function<void(CipherPuzzleData*, bool)> onUnlock);
	~CipherPuzzleData();

	void initializeListeners() override;

	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy;
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard;
	std::vector<std::string> easyTokens;
	std::vector<std::string> hardTokens;
	std::string bonusReward;
};
