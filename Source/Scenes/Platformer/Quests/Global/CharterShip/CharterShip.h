#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;

class CharterShip : public QuestTask
{
public:
	static CharterShip* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	CharterShip(GameObject* owner, QuestLine* questLine);
	virtual ~CharterShip();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
	Portal* portal = nullptr;

	static const std::string QuestTagShipPortal;
};
