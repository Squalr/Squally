#include "GameObject.h"

GameObject::GameObject() : Node()
{
}

GameObject::~GameObject()
{
}

void GameObject::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void GameObject::initializePositions()
{

}

void GameObject::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}
