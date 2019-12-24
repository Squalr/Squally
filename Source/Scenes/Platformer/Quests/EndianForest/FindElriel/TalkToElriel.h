#pragma once

#include "Engine/Quests/QuestTask.h"

class Alder;
class Aster;
class Elriel;
class Gorgon;
class Igneus;
class Marcel;
class Merlin;
class PlatformerEntity;
class QuestLine;
class Sarude;

class TalkToElriel : public QuestTask
{
public:
	static TalkToElriel* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	TalkToElriel(GameObject* owner, QuestLine* questLine, std::string questTag);
	~TalkToElriel();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();
	void doCastAnim(PlatformerEntity* entity);

	Alder* alder;
	Aster* aster;
	Elriel* elriel;
	Gorgon* gorgon;
	Igneus* igneus;
	Marcel* marcel;
	Merlin* merlin;
	Sarude* sarude;
};
