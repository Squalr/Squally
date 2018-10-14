#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentExterminator : public HexusOpponentData
{
public:
	static HexusOpponentExterminator* getInstance();

private:
	HexusOpponentExterminator();
	~HexusOpponentExterminator();

	static const std::string OpponentSaveKey;
	static HexusOpponentExterminator* instance;
};
