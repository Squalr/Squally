#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJohann : public HexusOpponentData
{
public:
	static HexusOpponentJohann* getInstance();

private:
	HexusOpponentJohann();
	~HexusOpponentJohann();

	static const std::string OpponentSaveKey;
	static HexusOpponentJohann* instance;
};
