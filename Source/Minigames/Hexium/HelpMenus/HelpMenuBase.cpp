#include "HelpMenuBase.h"

HelpMenuBase::HelpMenuBase()
{
}

HelpMenuBase::~HelpMenuBase()
{
}

void HelpMenuBase::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void HelpMenuBase::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void HelpMenuBase::initializeListeners()
{
}
