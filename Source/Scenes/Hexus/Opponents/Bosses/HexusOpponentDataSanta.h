#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataSanta : public HexusOpponentData
{
public:
	static HexusOpponentDataSanta* getInstance();

private:
	HexusOpponentDataSanta();
	~HexusOpponentDataSanta();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataSanta* instance;
};
