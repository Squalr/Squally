#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataEvilEye : public HexusOpponentData
{
public:
	static HexusOpponentDataEvilEye* getInstance();

private:
	HexusOpponentDataEvilEye();
	~HexusOpponentDataEvilEye();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataEvilEye* instance;
};
