#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentVoidDemon : public HexusOpponentData
{
public:
	static HexusOpponentVoidDemon* getInstance();

private:
	HexusOpponentVoidDemon();
	~HexusOpponentVoidDemon();

	static const std::string OpponentSaveKey;
	static HexusOpponentVoidDemon* instance;
};
