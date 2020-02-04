#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class TutorialDBehavior : public HexusBehaviorBase
{
public:
	static TutorialDBehavior* create(GameObject* owner);

protected:
	TutorialDBehavior(GameObject* owner);
	virtual ~TutorialDBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

	static const std::string WinLossTrackIdentifier;
};
