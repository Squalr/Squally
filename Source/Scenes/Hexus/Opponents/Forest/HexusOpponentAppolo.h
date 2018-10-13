#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAppolo : public HexusOpponentData
{
public:
	static HexusOpponentAppolo* getInstance();

private:
	HexusOpponentAppolo();
	~HexusOpponentAppolo();

	static const std::string StringKeyOpponentName;
	static HexusOpponentAppolo* instance;
};
