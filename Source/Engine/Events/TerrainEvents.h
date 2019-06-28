#pragma once
#include <functional>
#include <string>

class TerrainObject;

class TerrainEvents
{
public:
	static const std::string EventResolveOverlapConflicts;

	struct TerrainOverlapArgs
	{
		TerrainObject* newTerrain;

		TerrainOverlapArgs(TerrainObject* newTerrain) : newTerrain(newTerrain) { }
	};

	static void TriggerResolveOverlapConflicts(TerrainOverlapArgs args);
};
