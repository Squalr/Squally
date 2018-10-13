#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCryogen : public HexusOpponentData
{
public:
	static HexusOpponentCryogen* getInstance();

private:
	HexusOpponentCryogen();
	~HexusOpponentCryogen();

	static const std::string StringKeyOpponentName;
	static HexusOpponentCryogen* instance;
};
