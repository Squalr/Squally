#include "WarpGate.h"

WarpGate* WarpGate::create()
{
	WarpGate* warpGate = new WarpGate();

	warpGate->autorelease();

	return warpGate;
}

WarpGate::WarpGate()
{
	this->isOpen = false;

	this->gateOpen = Sprite::create(Resources::Ingame_Objects_WarpGateOpen);
	this->gateClosed = Sprite::create(Resources::Ingame_Objects_WarpGateClosed);

	this->gateOpen->setVisible(false);

	this->addChild(this->gateOpen);
	this->addChild(this->gateClosed);
}

WarpGate::~WarpGate()
{
}

void WarpGate::open()
{
	this->gateOpen->setVisible(true);
	this->gateClosed->setVisible(false);
}

void WarpGate::close()
{
	this->gateOpen->setVisible(false);
	this->gateClosed->setVisible(true);
}
