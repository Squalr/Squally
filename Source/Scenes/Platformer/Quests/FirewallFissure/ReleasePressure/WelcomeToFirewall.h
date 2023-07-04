#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class Squally;
class QuestLine;
class Ash;

class WelcomeToFirewall : public QuestTask
{
public:
	static WelcomeToFirewall* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WelcomeToFirewall(GameObject* owner, QuestLine* questLine);
	virtual ~WelcomeToFirewall();
	
	void onEnter() override;
	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void attachAshBehavior();

	Portal* cryptDoor = nullptr;
	Ash* ash = nullptr;
	Squally* squally = nullptr;
};
