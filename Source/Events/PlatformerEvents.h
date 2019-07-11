#pragma once
#include <string>
#include <vector>

class PlatformerEntity;

class PlatformerEvents
{
public:
	static const std::string EventCinematicHijack;
	static const std::string EventCinematicRestore;
	static const std::string EventQueryMapArgs;
	static const std::string EventRuneConsumed;
	static const std::string EventHudTrackEntity;
	static const std::string EventHudUntrackEntity;

	struct HudTrackEntityArgs
	{
		PlatformerEntity* entity;

		HudTrackEntityArgs(PlatformerEntity* entity) : entity(entity)
		{
		}
	};

	struct QueryMapArgsArgs
	{
		std::vector<std::string>* argRef;

		QueryMapArgsArgs(std::vector<std::string>* argRef) : argRef(argRef)
		{
		}
	};

	struct RuneConsumedArgs
	{
		PlatformerEntity* entity;
		int index;

		RuneConsumedArgs(PlatformerEntity* entity, int index) : entity(entity), index(index)
		{
		}
	};

	static void TriggerCinematicHijack();
	static void TriggerCinematicRestore();
	static void TriggerQueryMapArgs(QueryMapArgsArgs args);
	static void TriggerRuneConsumed(RuneConsumedArgs args);
	static void TriggerHudTrackEntity(HudTrackEntityArgs args);
	static void TriggerHudUntrackEntity(HudTrackEntityArgs args);
};
