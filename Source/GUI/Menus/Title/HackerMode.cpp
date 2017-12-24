#include "HackerMode.h"

HackerMode* HackerMode::hackerModeInstance = nullptr;

int HackerMode::hackerMode = 1;

HackerMode* HackerMode::GetInstance()
{
	if (HackerMode::hackerModeInstance == nullptr)
	{
		HackerMode::hackerModeInstance = new HackerMode();
	}

	return HackerMode::hackerModeInstance;
}

HackerMode::HackerMode()
{
	this->scheduleUpdate();
}

HackerMode::~HackerMode()
{
}

std::string HackerMode::GetHackerModeAddressHex()
{
	return Utils::HexAddressOf(&HackerMode::hackerMode);
}

void HackerMode::update(float dt)
{
	Node::update(dt);

	if (HackerMode::hackerMode != 0)
	{
		this->getEventDispatcher()->dispatchCustomEvent(this->HackerModeEnabledEvent, nullptr);
		this->unscheduleUpdate();
	}
}
