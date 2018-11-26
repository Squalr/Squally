#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJasper : public HexusOpponentData
{
public:
	static HexusOpponentJasper* getInstance();

private:
	HexusOpponentJasper();
	~HexusOpponentJasper();

	static const std::string OpponentSaveKey;
	static HexusOpponentJasper* instance;
};
