#include "Quest.h"

using namespace cocos2d;

Quest::Quest(std::string quest) : super()
{
	this->quest = quest;
	this->isActive = false;
}

Quest::~Quest()
{
}

void Quest::initializeListeners()
{
	super::initializeListeners();
}

void Quest::activate()
{
	this->isActive = true;
}

void Quest::deactivate()
{
	this->isActive = false;
}

std::string Quest::getQuestName()
{
	return this->quest;
}
