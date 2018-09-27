#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJunglePurpleDinosaur : public HexusOpponentData
{
public:
	static HexusOpponentJunglePurpleDinosaur* getInstance();

private:
	HexusOpponentJunglePurpleDinosaur();
	~HexusOpponentJunglePurpleDinosaur();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJunglePurpleDinosaur* instance;
};
