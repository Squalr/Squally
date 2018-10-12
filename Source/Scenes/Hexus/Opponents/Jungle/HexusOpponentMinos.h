#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMinos : public HexusOpponentData
{
public:
	static HexusOpponentMinos* getInstance();

private:
	HexusOpponentMinos();
	~HexusOpponentMinos();

	static const std::string StringKeyOpponentName;
	static HexusOpponentMinos* instance;
};
