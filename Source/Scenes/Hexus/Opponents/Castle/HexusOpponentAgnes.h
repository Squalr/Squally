#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAgnes : public HexusOpponentData
{
public:
	static HexusOpponentAgnes* getInstance();

private:
	HexusOpponentAgnes();
	~HexusOpponentAgnes();

	static const std::string OpponentSaveKey;
	static HexusOpponentAgnes* instance;
};
