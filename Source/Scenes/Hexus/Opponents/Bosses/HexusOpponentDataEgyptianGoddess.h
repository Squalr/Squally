#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataEgyptianGoddess : public HexusOpponentData
{
public:
	static HexusOpponentDataEgyptianGoddess* getInstance();

private:
	HexusOpponentDataEgyptianGoddess();
	~HexusOpponentDataEgyptianGoddess();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataEgyptianGoddess* instance;
};
