#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentViper : public HexusOpponentData
{
public:
	static HexusOpponentViper* getInstance();

private:
	HexusOpponentViper();
	~HexusOpponentViper();

	static const std::string OpponentSaveKey;
	static HexusOpponentViper* instance;
};
