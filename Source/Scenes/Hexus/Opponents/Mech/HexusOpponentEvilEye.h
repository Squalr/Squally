#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentEvilEye : public HexusOpponentData
{
public:
	static HexusOpponentEvilEye* getInstance();

private:
	HexusOpponentEvilEye();
	~HexusOpponentEvilEye();

	static const std::string StringKeyOpponentName;
	static HexusOpponentEvilEye* instance;
};
