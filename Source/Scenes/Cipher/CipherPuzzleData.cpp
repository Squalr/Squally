#include "CipherPuzzleData.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherPuzzleData* CipherPuzzleData::create(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> rewards,
		std::vector<std::string> bonusRewards)
{
	CipherPuzzleData* instance = new CipherPuzzleData(inputOutputMapEasy, inputOutputMapHard, rewards, bonusRewards);

	instance->autorelease();

	return instance;
}

CipherPuzzleData::CipherPuzzleData(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy,
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard,
		std::vector<std::string> rewards,
		std::vector<std::string> bonusRewards)
{
	this->inputOutputMapEasy = inputOutputMapEasy;
	this->inputOutputMapHard = inputOutputMapHard;
	this->rewards = rewards;
	this->bonusRewards = bonusRewards;
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
		this->rewards,
		this->bonusRewards
	);
}

std::vector<std::tuple<unsigned char, unsigned char>> CipherPuzzleData::getInputOutputMapEasy()
{
	return this->inputOutputMapEasy;
}

std::vector<std::tuple<unsigned char, unsigned char>> CipherPuzzleData::getInputOutputMapHard()
{
	return this->inputOutputMapHard;
}

std::vector<std::string> CipherPuzzleData::getRewards()
{
	return this->rewards;
}

std::vector<std::string> CipherPuzzleData::getBonusRewards()
{
	return this->bonusRewards;
}
