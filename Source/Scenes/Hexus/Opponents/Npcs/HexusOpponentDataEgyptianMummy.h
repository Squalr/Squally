#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataEgyptianMummy : public HexusOpponentData
{
public:
	static HexusOpponentDataEgyptianMummy* getInstance();

private:
	HexusOpponentDataEgyptianMummy();
	~HexusOpponentDataEgyptianMummy();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataEgyptianMummy* instance;
};
