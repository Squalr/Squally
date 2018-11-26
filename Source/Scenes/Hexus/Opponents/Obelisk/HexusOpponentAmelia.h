#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAmelia : public HexusOpponentData
{
public:
	static HexusOpponentAmelia* getInstance();

private:
	HexusOpponentAmelia();
	~HexusOpponentAmelia();

	static const std::string OpponentSaveKey;
	static HexusOpponentAmelia* instance;
};
