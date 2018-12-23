#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentTigress : public HexusOpponentData
{
public:
	static HexusOpponentTigress* getInstance();

private:
	HexusOpponentTigress();
	~HexusOpponentTigress();

	static const std::string OpponentSaveKey;
	static HexusOpponentTigress* instance;
};
