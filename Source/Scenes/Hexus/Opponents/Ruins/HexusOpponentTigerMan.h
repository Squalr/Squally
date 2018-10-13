#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTigerMan : public HexusOpponentData
{
public:
	static HexusOpponentTigerMan* getInstance();

private:
	HexusOpponentTigerMan();
	~HexusOpponentTigerMan();

	static const std::string StringKeyOpponentName;
	static HexusOpponentTigerMan* instance;
};
