#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentEgyptianMummy : public HexusOpponentData
{
public:
	static HexusOpponentEgyptianMummy* getInstance();

private:
	HexusOpponentEgyptianMummy();
	~HexusOpponentEgyptianMummy();

	static const std::string StringKeyOpponentName;
	static HexusOpponentEgyptianMummy* instance;
};
