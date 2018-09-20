#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataKnight : public HexusOpponentData
{
public:
	static HexusOpponentDataKnight* getInstance();

private:
	HexusOpponentDataKnight();
	~HexusOpponentDataKnight();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataKnight* instance;
};
