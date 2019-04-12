#include "CipherPuzzleData.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherPuzzleData::CipherPuzzleData(std::vector<std::tuple<std::string, std::string>> inputOutputMap)
{
	this->inputOutputMap = inputOutputMap;
}

CipherPuzzleData::~CipherPuzzleData()
{
}

void CipherPuzzleData::initializeListeners()
{
	super::initializeListeners();
}

std::vector<std::tuple<std::string, std::string>> CipherPuzzleData::getInputOutputMap()
{
	return this->inputOutputMap;
}
