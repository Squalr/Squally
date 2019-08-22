#pragma once

#include "Engine/Quests/QuestTask.h"

class CollisionObject;
class Chiron;
class Squally;
class QuestLine;

class TownExitBlocked : public QuestTask
{
public:
	static TownExitBlocked* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	TownExitBlocked(GameObject* owner, QuestLine* questLine, std::string questTag);
	~TownExitBlocked();
	
	void onEnter() override;
	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;
	void update(float dt) override;

private:
	typedef QuestTask super;

	CollisionObject* collisionObject;
	Chiron* chiron;
	Squally* squally;
	CollisionObject* chironCollision;

	bool isEngagedInDialogue;
	float dialogueCooldown;
};
