#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCleopatra : public HexusOpponentData
{
public:
	static HexusOpponentCleopatra* getInstance();

private:
	HexusOpponentCleopatra();
	~HexusOpponentCleopatra();

	static const std::string StringKeyOpponentName;
	static HexusOpponentCleopatra* instance;
};
