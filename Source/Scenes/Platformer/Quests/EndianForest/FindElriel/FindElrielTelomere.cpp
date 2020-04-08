#include "FindElrielTelomere.h"


#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FindElrielTelomere::MapKeyQuest = "find-elriel-telomere";

FindElrielTelomere* FindElrielTelomere::create(GameObject* owner, QuestLine* questLine)
{
	FindElrielTelomere* instance = new FindElrielTelomere(owner, questLine);

	instance->autorelease();

	return instance;
}

FindElrielTelomere::FindElrielTelomere(GameObject* owner, QuestLine* questLine) : super(owner, questLine, FindElrielTelomere::MapKeyQuest, false)
{
}

FindElrielTelomere::~FindElrielTelomere()
{
}

void FindElrielTelomere::onLoad(QuestState questState)
{
}

void FindElrielTelomere::onActivate(bool isActiveThroughSkippable)
{
}

void FindElrielTelomere::onComplete()
{
}

void FindElrielTelomere::onSkipped()
{
	this->removeAllListeners();
}
