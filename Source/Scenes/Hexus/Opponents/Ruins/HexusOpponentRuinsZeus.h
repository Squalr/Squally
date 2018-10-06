#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsZeus : public HexusOpponentData
{
public:
	static HexusOpponentRuinsZeus* getInstance();

private:
	HexusOpponentRuinsZeus();
	~HexusOpponentRuinsZeus();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsZeus* instance;
};
