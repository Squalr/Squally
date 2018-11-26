#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCooper : public HexusOpponentData
{
public:
	static HexusOpponentCooper* getInstance();

private:
	HexusOpponentCooper();
	~HexusOpponentCooper();

	static const std::string OpponentSaveKey;
	static HexusOpponentCooper* instance;
};
