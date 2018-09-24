#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentEgyptianGoddess : public HexusOpponentData
{
public:
	static HexusOpponentEgyptianGoddess* getInstance();

private:
	HexusOpponentEgyptianGoddess();
	~HexusOpponentEgyptianGoddess();

	static const std::string StringKeyOpponentName;
	static HexusOpponentEgyptianGoddess* instance;
};
