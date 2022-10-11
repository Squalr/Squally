#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;

class DiscoverCharterShip : public QuestTask
{
public:
	static DiscoverCharterShip* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DiscoverCharterShip(GameObject* owner, QuestLine* questLine);
	virtual ~DiscoverCharterShip();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
};
