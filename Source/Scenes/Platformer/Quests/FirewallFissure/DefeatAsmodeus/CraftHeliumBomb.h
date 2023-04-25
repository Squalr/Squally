#pragma once

#include "Engine/Quests/QuestTask.h"

class Drak;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class CraftHeliumBomb : public QuestTask
{
public:
	static CraftHeliumBomb* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	CraftHeliumBomb(GameObject* owner, QuestLine* questLine);
	virtual ~CraftHeliumBomb();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
};
