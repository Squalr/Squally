#pragma once
#include <string>

namespace cocos2d
{
	class Node;
}

class SerializableLayer;
class SerializableObject;

class SpawnEvents
{
public:
	enum class SpawnMethod
	{
		Below,
		Above
	};

	struct RequestObjectSpawnArgs
	{
		cocos2d::Node* spawner;
		cocos2d::Node* objectToSpawn;
		SpawnMethod spawnMethod;

		RequestObjectSpawnArgs() : spawner(nullptr), objectToSpawn(nullptr), spawnMethod(SpawnMethod::Above) { }
		RequestObjectSpawnArgs(cocos2d::Node* spawner, cocos2d::Node* objectToSpawn, SpawnMethod spawnMethod) : spawner(spawner), objectToSpawn(objectToSpawn), spawnMethod(spawnMethod) { }
	};

	struct RequestObjectSpawnDelegatorArgs
	{
		SerializableLayer* sourceLayer;
		cocos2d::Node* spawner;
		cocos2d::Node* objectToSpawn;
		SpawnMethod spawnMethod;

		RequestObjectSpawnDelegatorArgs() : sourceLayer(nullptr), spawner(nullptr), objectToSpawn(nullptr), spawnMethod(SpawnMethod::Above) { }
		RequestObjectSpawnDelegatorArgs(SerializableLayer* sourceLayer, cocos2d::Node* spawner, cocos2d::Node* objectToSpawn, SpawnMethod spawnMethod) : sourceLayer(sourceLayer), spawner(spawner), objectToSpawn(objectToSpawn), spawnMethod(spawnMethod) { }
	};

	static void TriggerObjectSpawn(RequestObjectSpawnArgs args);
	static void TriggerObjectSpawnDelegator(RequestObjectSpawnDelegatorArgs args);

	static const std::string SpawnObjectEvent;
	static const std::string SpawnObjectDelegatorEvent;
};
