#pragma once

#include "Engine/Quests/QuestTask.h"

class Drak;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class CraftDemonHeart : public QuestTask
{
public:
	static CraftDemonHeart* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	CraftDemonHeart(GameObject* owner, QuestLine* questLine);
	virtual ~CraftDemonHeart();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void setDrakText();

	Drak* drak = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
