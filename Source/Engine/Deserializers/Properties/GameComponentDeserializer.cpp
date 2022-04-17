#include "GameComponentDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Components/GameComponent.h"
#include "Engine/Utils/LogUtils.h"

using namespace cocos2d;

GameComponentDeserializer::GameComponentDeserializer()
{
}

GameComponentDeserializer::~GameComponentDeserializer()
{
}

GameComponent* GameComponentDeserializer::deserialize(GameComponentDeserializer::ComponentDeserializationRequestArgs args)
{
	if (this->componentDeserializers.find(args.component) != this->componentDeserializers.end())
	{
		return this->componentDeserializers[args.component](args.owner);
	}
	else
	{
		LogUtils::logError("Unknown attached behavior encountered: " + args.component);
	}

    return nullptr;
}
