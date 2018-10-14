#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentElriel : public HexusOpponentData
{
public:
	static HexusOpponentElriel* getInstance();

private:
	HexusOpponentElriel();
	~HexusOpponentElriel();

	static const std::string OpponentSaveKey;
	static HexusOpponentElriel* instance;
};
