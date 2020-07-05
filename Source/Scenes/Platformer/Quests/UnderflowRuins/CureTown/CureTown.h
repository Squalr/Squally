#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Hera;
class QuestLine;
class Scrappy;
class Squally;

class CureTown : public QuestTask
{
public:
	static CureTown* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;
	static const std::string SaveKeyCuredCount;
	static const std::string SaveKeyAjaxCured;
	static const std::string SaveKeyGriffinCured;
	static const int MaxCuredCount;

protected:
	CureTown(GameObject* owner, QuestLine* questLine);
	virtual ~CureTown();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();
	void setPreText();

	Guano* guano;
	Hera* hera;
	Scrappy* scrappy;
	Squally* squally;
};
