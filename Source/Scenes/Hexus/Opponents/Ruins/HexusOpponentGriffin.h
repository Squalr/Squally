#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGriffin : public HexusOpponentData
{
public:
	static HexusOpponentGriffin* getInstance();

private:
	HexusOpponentGriffin();
	~HexusOpponentGriffin();

	static const std::string StringKeyOpponentName;
	static HexusOpponentGriffin* instance;
};
