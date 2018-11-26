#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMildred : public HexusOpponentData
{
public:
	static HexusOpponentMildred* getInstance();

private:
	HexusOpponentMildred();
	~HexusOpponentMildred();

	static const std::string OpponentSaveKey;
	static HexusOpponentMildred* instance;
};
