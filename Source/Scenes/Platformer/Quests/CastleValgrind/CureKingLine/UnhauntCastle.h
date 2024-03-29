#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Mabel;
class Portal;
class QuestLine;
class Scrappy;
class Squally;

class UnhauntCastle : public QuestTask
{
public:
	static UnhauntCastle* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;
	static const std::string SaveKeySoulHarvestedCount;
	static const std::string SaveKeyPrefixUnhaunted;
	static const int MaxUnhauntCount;

protected:
	UnhauntCastle(GameObject* owner, QuestLine* questLine);
	virtual ~UnhauntCastle();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void updateQuestVisuals();
	void runCinematicSequence();
	void setPreText();
	void moveBookshelf(bool animate);

	Guano* guano = nullptr;
	Mabel* mabel = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	GameObject* bookshelf = nullptr;
	Portal* secretDoorPortal = nullptr;
};
