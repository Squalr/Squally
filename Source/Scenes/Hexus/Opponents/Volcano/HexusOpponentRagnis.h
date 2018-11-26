#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRagnis : public HexusOpponentData
{
public:
	static HexusOpponentRagnis* getInstance();

private:
	HexusOpponentRagnis();
	~HexusOpponentRagnis();

	static const std::string OpponentSaveKey;
	static HexusOpponentRagnis* instance;
};
