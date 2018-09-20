#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataIceGolem : public HexusOpponentData
{
public:
	static HexusOpponentDataIceGolem* getInstance();

private:
	HexusOpponentDataIceGolem();
	~HexusOpponentDataIceGolem();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataIceGolem* instance;
};
