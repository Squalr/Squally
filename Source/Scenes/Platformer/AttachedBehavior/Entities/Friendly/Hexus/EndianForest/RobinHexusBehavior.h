#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class RobinHexusBehavior : public HexusBehaviorBase
{
public:
	static RobinHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RobinHexusBehavior(GameObject* owner);
	virtual ~RobinHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
