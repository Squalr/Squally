#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMermaid : public HexusOpponentData
{
public:
	static HexusOpponentMermaid* getInstance();

private:
	HexusOpponentMermaid();
	~HexusOpponentMermaid();

	static const std::string OpponentSaveKey;
	static HexusOpponentMermaid* instance;
};
