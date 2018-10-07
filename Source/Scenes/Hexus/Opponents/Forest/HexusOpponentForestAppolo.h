#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestAppolo : public HexusOpponentData
{
public:
	static HexusOpponentForestAppolo* getInstance();

private:
	HexusOpponentForestAppolo();
	~HexusOpponentForestAppolo();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestAppolo* instance;
};
