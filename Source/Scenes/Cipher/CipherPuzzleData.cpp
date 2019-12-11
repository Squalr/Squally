#include "CipherPuzzleData.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherPuzzleData* CipherPuzzleData::create(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap,
		std::vector<std::string> tokens,
		std::string tutorial,
		std::function<void(CipherPuzzleData*)> onUnlock)
{
	CipherPuzzleData* instance = new CipherPuzzleData(inputOutputMap, tokens, tutorial, onUnlock);

	instance->autorelease();

	return instance;
}

CipherPuzzleData::CipherPuzzleData(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap,
		std::vector<std::string> tokens,
		std::string tutorial,
		std::function<void(CipherPuzzleData*)> onUnlock)
{
	this->inputOutputMap = inputOutputMap;
	this->tokens = tokens;
	this->tutorial = tutorial;
	this->onUnlock = onUnlock;
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
		this->inputOutputMap,
		this->tokens,
		this->tutorial,
		this->onUnlock
	);
}

std::vector<std::tuple<unsigned char, unsigned char>> CipherPuzzleData::getInputOutputMap()
{
	return this->inputOutputMap;
}

std::vector<std::string> CipherPuzzleData::getTokens()
{
	return this->tokens;
}

std::string CipherPuzzleData::getTutorial()
{
	return this->tutorial;
}
