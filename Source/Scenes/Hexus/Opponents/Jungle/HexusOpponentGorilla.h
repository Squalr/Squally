#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGorilla : public HexusOpponentData
{
public:
	static HexusOpponentGorilla* getInstance();

private:
	HexusOpponentGorilla();
	~HexusOpponentGorilla();

	static const std::string StringKeyOpponentName;
	static HexusOpponentGorilla* instance;
};
