#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


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
