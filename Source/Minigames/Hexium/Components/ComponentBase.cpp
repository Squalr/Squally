#include "ComponentBase.h"

ComponentBase* ComponentBase::create()
{
	ComponentBase* componentBase = new ComponentBase();

	componentBase->autorelease();

	return componentBase;
}

ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ComponentBase::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ComponentBase::initializeListeners()
{
}

void ComponentBase::onStateChange(EventCustom* eventCustom)
{
	this->onStateChange((GameState*)(eventCustom->getUserData()));
}
