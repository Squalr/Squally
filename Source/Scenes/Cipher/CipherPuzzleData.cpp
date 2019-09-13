#include "CipherPuzzleData.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherPuzzleData* CipherPuzzleData::create(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> easyTokens,
		std::vector<std::string> hardTokens,
		std::vector<std::string> rewards,
		std::string bonusReward)
{
	CipherPuzzleData* instance = new CipherPuzzleData(inputOutputMapEasy, inputOutputMapHard, easyTokens, hardTokens, rewards, bonusReward);

	instance->autorelease();

	return instance;
}

CipherPuzzleData::CipherPuzzleData(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> easyTokens,
		std::vector<std::string> hardTokens,
		std::vector<std::string> rewards,
		std::string bonusReward)
{
	this->inputOutputMapEasy = inputOutputMapEasy;
	this->inputOutputMapHard = inputOutputMapHard;
	this->easyTokens = easyTokens;
	this->hardTokens = hardTokens;
	this->rewards = rewards;
	this->bonusReward = bonusReward;
}

CipherPuzzleData::~CipherPuzzleData()
{
}

void CipherPuzzleData::initializeListeners()
{
	super::initializeListeners();
}

CipherPuzzleData* CipherPuzzleData::clone()
{
	return CipherPuzzleData::create(
		this->inputOutputMapEasy,
		this->inputOutputMapHard,
		this->easyTokens,
		this->hardTokens,
		this->rewards,
		this->bonusReward
	);
}

bool CipherPuzzleData::hasHardMode()
{
	return !this->inputOutputMapHard.empty();
}

std::vector<std::tuple<unsigned char, unsigned char>> CipherPuzzleData::getInputOutputMapEasy()
{
	return this->inputOutputMapEasy;
}

std::vector<std::tuple<unsigned char, unsigned char>> CipherPuzzleData::getInputOutputMapHard()
{
	return this->inputOutputMapHard;
}

std::vector<std::string> CipherPuzzleData::getEasyTokens()
{
	return this->easyTokens;
}

std::vector<std::string> CipherPuzzleData::getHardTokens()
{
	return this->hardTokens;
}

std::vector<std::string> CipherPuzzleData::getRewards()
{
	return this->rewards;
}

std::string CipherPuzzleData::getBonusReward()
{
	return this->bonusReward;
}
