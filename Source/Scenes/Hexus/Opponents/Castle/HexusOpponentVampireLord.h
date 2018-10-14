#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentVampireLord : public HexusOpponentData
{
public:
	static HexusOpponentVampireLord* getInstance();

private:
	HexusOpponentVampireLord();
	~HexusOpponentVampireLord();

	static const std::string OpponentSaveKey;
	static HexusOpponentVampireLord* instance;
};
