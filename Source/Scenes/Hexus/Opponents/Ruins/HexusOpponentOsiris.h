#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentOsiris : public HexusOpponentData
{
public:
	static HexusOpponentOsiris* getInstance();

private:
	HexusOpponentOsiris();
	~HexusOpponentOsiris();

	static const std::string OpponentSaveKey;
	static HexusOpponentOsiris* instance;
};
