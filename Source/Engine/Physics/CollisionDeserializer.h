#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Physics/CollisionObject.h"

using namespace cocos2d;

class CollisionDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	CollisionDeserializer();
	~CollisionDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static CollisionDeserializer* instance;
	static const std::string KeyTypeIsometricEntity;
};
