#pragma once

#include "Engine/Quests/QuestTask.h"

class Bard;
class CollisionObject;
class Chiron;
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
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;
	void update(float dt) override;

private:
	typedef QuestTask super;

	void attachChironBehavior();
	void attachBardBehavior();

	Bard* bard;
	Chiron* chiron;
	Squally* squally;
	CollisionObject* chironCollision;
	Portal* townExitPortal;

	bool isEngagedInDialogue;
	float dialogueCooldown;

	static const std::string TagBlockedExit;
};
