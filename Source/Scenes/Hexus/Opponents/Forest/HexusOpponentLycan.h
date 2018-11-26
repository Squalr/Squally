#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentLycan : public HexusOpponentData
{
public:
	static HexusOpponentLycan* getInstance();

private:
	HexusOpponentLycan();
	~HexusOpponentLycan();

	static const std::string OpponentSaveKey;
	static HexusOpponentLycan* instance;
};
