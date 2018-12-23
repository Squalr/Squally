#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGargoyle : public HexusOpponentData
{
public:
	static HexusOpponentGargoyle* getInstance();

private:
	HexusOpponentGargoyle();
	~HexusOpponentGargoyle();

	static const std::string OpponentSaveKey;
	static HexusOpponentGargoyle* instance;
};
