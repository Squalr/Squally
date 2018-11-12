#include "SmartNode.h"

SmartNode::SmartNode()
{
}

SmartNode::~SmartNode()
{
}

void SmartNode::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void SmartNode::initializePositions()
{
}

void SmartNode::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartNode::resume()
{
	Node::resume();

	this->initializeListeners();
}
