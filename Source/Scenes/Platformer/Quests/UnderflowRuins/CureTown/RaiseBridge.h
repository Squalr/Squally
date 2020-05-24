#pragma once

#include "Engine/Quests/QuestTask.h"

class Ajax;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class RaiseBridge : public QuestTask
{
public:
	static RaiseBridge* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	RaiseBridge(GameObject* owner, QuestLine* questLine);
	virtual ~RaiseBridge();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Ajax* ajax;
	Guano* guano;
	Scrappy* scrappy;
	Squally* squally;

	static const std::string TagTownCinematic;
};
