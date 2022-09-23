#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;
class Ship;

class BoardCharterShip : public QuestTask
{
public:
	static BoardCharterShip* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	BoardCharterShip(GameObject* owner, QuestLine* questLine);
	virtual ~BoardCharterShip();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
	Portal* portal = nullptr;
	Ship* ship = nullptr;

	void setReturnMap();
	
	static const std::string TagDespawnableShip;
};
