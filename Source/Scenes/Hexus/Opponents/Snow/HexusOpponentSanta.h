#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSanta : public HexusOpponentData
{
public:
	static HexusOpponentSanta* getInstance();

private:
	HexusOpponentSanta();
	~HexusOpponentSanta();

	static const std::string StringKeyOpponentName;
	static HexusOpponentSanta* instance;
};
