#include "AttachedBehaviorDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/AttachedBehavior/AttachedBehavior.h"
#include "Engine/Utils/LogUtils.h"

using namespace cocos2d;

AttachedBehaviorDeserializer::AttachedBehaviorDeserializer()
{
}

AttachedBehaviorDeserializer::~AttachedBehaviorDeserializer()
{
}

AttachedBehavior* AttachedBehaviorDeserializer::deserialize(AttachedBehaviorDeserializer::AttachedBehaviorDeserializationRequestArgs args)
{
	if (this->attachedBehaviorDeserializers.find(args.attachedBehavior) != this->attachedBehaviorDeserializers.end())
	{
		return this->attachedBehaviorDeserializers[args.attachedBehavior](args.owner);
	}
	else
	{
		LogUtils::logError("Unknown attached behavior encountered: " + args.attachedBehavior);
	}

    return nullptr;
}
