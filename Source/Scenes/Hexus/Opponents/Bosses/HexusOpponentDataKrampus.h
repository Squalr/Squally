#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataKrampus : public HexusOpponentData
{
public:
	static HexusOpponentDataKrampus* getInstance();

private:
	HexusOpponentDataKrampus();
	~HexusOpponentDataKrampus();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataKrampus* instance;
};
