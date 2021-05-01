#include "ComponentDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Components/Component.h"
#include "Engine/Utils/LogUtils.h"

using namespace cocos2d;

ComponentDeserializer::ComponentDeserializer()
{
}

ComponentDeserializer::~ComponentDeserializer()
{
}

Component* ComponentDeserializer::deserialize(ComponentDeserializer::ComponentDeserializationRequestArgs args)
{
	if (this->componentDeserializers.contains(args.component))
	{
		return this->componentDeserializers[args.component](args.owner);
	}
	else
	{
		LogUtils::logError("Unknown attached behavior encountered: " + args.component);
	}

    return nullptr;
}
