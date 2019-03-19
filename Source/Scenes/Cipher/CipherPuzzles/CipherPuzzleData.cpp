#include "CipherPuzzleData.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherPuzzleData::CipherPuzzleData(std::map<std::string, std::string> inputsOutputsPanel)
{
	this->inputsOutputsPanel = inputsOutputsPanel;
}

CipherPuzzleData::~CipherPuzzleData()
{
}

void CipherPuzzleData::initializeListeners()
{
	super::initializeListeners();
}
