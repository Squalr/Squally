#include "AttachedBehaviorDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/AttachedBehavior/AttachedBehavior.h"

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
		return this->attachedBehaviorDeserializers[args.attachedBehavior](args.owner, args.attachedBehaviorArgs);
	}
	else
	{
		CCLOG("Unknown attached behavior encountered: %s", args.attachedBehavior.c_str());
	}

    return nullptr;
}
