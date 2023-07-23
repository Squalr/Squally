#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class Squally;
class QuestLine;
class Zana;

class CryptGuard : public QuestTask
{
public:
	static CryptGuard* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	CryptGuard(GameObject* owner, QuestLine* questLine);
	virtual ~CryptGuard();
	
	void onEnter() override;
	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void attachZanaBehavior();

	Portal* cryptDoor = nullptr;
	Zana* zana = nullptr;
	Squally* squally = nullptr;
};
