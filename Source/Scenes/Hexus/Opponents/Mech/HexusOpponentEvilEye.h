#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentEvilEye : public HexusOpponentData
{
public:
	static HexusOpponentEvilEye* getInstance();

private:
	HexusOpponentEvilEye();
	~HexusOpponentEvilEye();

	static const std::string OpponentSaveKey;
	static HexusOpponentEvilEye* instance;
};
