#pragma once

#include "Engine/Quests/QuestTask.h"

class Bard;
class CollisionObject;
class Chiron;
class Mara;
class Portal;
class Squally;
class QuestLine;

class TownExitBlocked : public QuestTask
{
public:
	static TownExitBlocked* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TownExitBlocked(GameObject* owner, QuestLine* questLine);
	virtual ~TownExitBlocked();
	
	void onEnter() override;
	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;
	void update(float dt) override;

private:
	typedef QuestTask super;

	void attachChironBehavior();
	void attachBardBehavior();
	void attachMaraBehavior();

	Bard* bard = nullptr;
	Mara* mara = nullptr;
	Chiron* chiron = nullptr;
	Squally* squally = nullptr;
	CollisionObject* chironCollision = nullptr;
	Portal* townExitPortal = nullptr;

	bool isEngagedInDialogue = false;
	float dialogueCooldown = 0.0f;

	static const std::string TagBlockedExit;
};
