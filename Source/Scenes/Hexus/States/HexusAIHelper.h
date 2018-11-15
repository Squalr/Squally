#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/Sound/SoundManager.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class HexusAIHelper
{
public:
	static std::tuple<CardRow*, int> getBestRow(Card* candidateCardToPlay, GameState* gameState);
	static std::tuple<Card*, Card*, int> getBestSourceAndTarget(Card* candidateCardToPlay, GameState* gameState);
	static std::tuple<Card*, int> getBestTarget(Card* candidateCardToPlay, GameState* gameState);
};
