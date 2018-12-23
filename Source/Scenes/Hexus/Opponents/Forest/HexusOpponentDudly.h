#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDudly : public HexusOpponentData
{
public:
	static HexusOpponentDudly* getInstance();

private:
	HexusOpponentDudly();
	~HexusOpponentDudly();

	static const std::string OpponentSaveKey;
	static HexusOpponentDudly* instance;
};
