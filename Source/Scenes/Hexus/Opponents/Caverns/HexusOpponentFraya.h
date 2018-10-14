#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentFraya : public HexusOpponentData
{
public:
	static HexusOpponentFraya* getInstance();

private:
	HexusOpponentFraya();
	~HexusOpponentFraya();

	static const std::string OpponentSaveKey;
	static HexusOpponentFraya* instance;
};
