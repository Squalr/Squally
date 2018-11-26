#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentBrock : public HexusOpponentData
{
public:
	static HexusOpponentBrock* getInstance();

private:
	HexusOpponentBrock();
	~HexusOpponentBrock();

	static const std::string OpponentSaveKey;
	static HexusOpponentBrock* instance;
};
