#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

// Forward declarations
class HexusOpponentData;

class HexusEvents
{
public:
	static const std::string HexusGameStartEvent;

	struct HexusGameEventArgs
	{
		HexusOpponentData* opponentData;

		HexusGameEventArgs(HexusOpponentData* opponentData) : opponentData(opponentData)
		{
		}
	};

	static void startGame(HexusGameEventArgs args);
};
