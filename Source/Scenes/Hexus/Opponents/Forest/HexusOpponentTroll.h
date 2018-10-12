#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTroll : public HexusOpponentData
{
public:
	static HexusOpponentTroll* getInstance();

private:
	HexusOpponentTroll();
	~HexusOpponentTroll();

	static const std::string StringKeyOpponentName;
	static HexusOpponentTroll* instance;
};
