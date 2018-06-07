#include "HackerMode.h"

HackerMode* HackerMode::hackerModeInstance = nullptr;
const std::string HackerMode::HackerModeEnabledEvent = "hacker_mode_enabled_event";

int HackerMode::hackerMode = 1;

HackerMode* HackerMode::getInstance()
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

std::string HackerMode::getHackerModeAddressHex()
{
	return HackUtils::hexAddressOf(&HackerMode::hackerMode, false, false);
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
