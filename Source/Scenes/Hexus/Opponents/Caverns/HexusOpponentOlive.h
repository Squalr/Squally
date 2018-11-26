#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentOlive : public HexusOpponentData
{
public:
	static HexusOpponentOlive* getInstance();

private:
	HexusOpponentOlive();
	~HexusOpponentOlive();

	static const std::string OpponentSaveKey;
	static HexusOpponentOlive* instance;
};
