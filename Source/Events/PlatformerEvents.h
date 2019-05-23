#pragma once
#include <string>

class PlatformerEntity;

class PlatformerEvents
{
public:
	static const std::string EventCinematicHijack;
	static const std::string EventCinematicRestore;
	static const std::string EventHudTrackEntity;
	static const std::string EventHudUntrackEntity;

	struct HudTrackEntityArgs
	{
		PlatformerEntity* entity;

		HudTrackEntityArgs(PlatformerEntity* entity) : entity(entity)
		{
		}
	};

	static void TriggerCinematicHijack();
	static void TriggerCinematicRestore();
	static void TriggerHudTrackEntity(HudTrackEntityArgs args);
	static void TriggerHudUntrackEntity(HudTrackEntityArgs args);
};
