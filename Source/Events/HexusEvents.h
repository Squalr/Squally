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
	static const std::string HexusShowRewardsEvent;

	struct HexusGameResultEventArgs
	{
		bool playerWon;
		HexusOpponentData* opponentData;

		HexusGameResultEventArgs(bool playerWon, HexusOpponentData* opponentData) : playerWon(playerWon), opponentData(opponentData)
		{
		}
	};

	struct HexusRewardArgs
	{
		HexusOpponentData* opponentData;

		HexusRewardArgs(HexusOpponentData* opponentData) : opponentData(opponentData)
		{
		}
	};

	struct HexusGameEventArgs
	{
		HexusOpponentData* opponentData;
		std::function<void(HexusGameResultEventArgs)> onGameEndCallback;

		HexusGameEventArgs(HexusOpponentData* opponentData, std::function<void(HexusGameResultEventArgs)> onGameEndCallback) : opponentData(opponentData), onGameEndCallback(onGameEndCallback)
		{
		}
	};

	static void showRewards(HexusRewardArgs args);
	static void startGame(HexusGameEventArgs args);
};
