#pragma once
#include <string>

class PlatformerEntity;

class PlatformerEvents
{
public:
	static const std::string EventHudTrackEntity;

	struct HudTrackEntityArgs
	{
		PlatformerEntity* entity;

		HudTrackEntityArgs(PlatformerEntity* entity) : entity(entity)
		{
		}
	};

	static void TriggerHudTrackEntity(HudTrackEntityArgs args);
};
