#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

// Forward declarations
class HexusOpponentData;

class HexusEvents
{
public:
	static const std::string HexusGameStartEvent;
	static const std::string HexusShowRewardsEvent;

	enum HexusGameResult
	{
		PlayerWon,
		EnemyWon,
		Draw
	};

	struct HexusGameResultEventArgs
	{
		HexusGameResult gameResult;
		HexusOpponentData* opponentData;
		int gameDurationInSeconds;

		HexusGameResultEventArgs(HexusGameResult gameResult, HexusOpponentData* opponentData, int gameDurationInSeconds) : gameResult(gameResult), opponentData(opponentData), gameDurationInSeconds(gameDurationInSeconds)
		{
		}
	};

	struct HexusRewardArgs
	{
		HexusGameResult gameResult;
		HexusOpponentData* opponentData;
		bool backToChapterSelect;

		HexusRewardArgs(HexusGameResult gameResult, HexusOpponentData* opponentData, bool backToChapterSelect) : gameResult(gameResult), opponentData(opponentData), backToChapterSelect(backToChapterSelect)
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
