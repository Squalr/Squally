#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QueenElise;
class QuestLine;
class Scrappy;
class Squally;

class QueenEliseInterim : public QuestTask
{
public:
	static QueenEliseInterim* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	QueenEliseInterim(GameObject* owner, QuestLine* questLine);
	virtual ~QueenEliseInterim();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void setPostText();

	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	QueenElise* queenElise = nullptr;
};
