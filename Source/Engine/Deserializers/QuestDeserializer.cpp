#include "QuestDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Quests/QuestLine.h"

using namespace cocos2d;

QuestDeserializer::QuestDeserializer()
{
}

QuestDeserializer::~QuestDeserializer()
{
}

QuestLine* QuestDeserializer::deserialize(QuestDeserializer::QuestLineDeserializationRequestArgs args)
{
	if (this->lineDeserializers.find(args.questLine) != this->lineDeserializers.end())
	{
		return this->lineDeserializers[args.questLine]();
	}
	else
	{
		CCLOG("Unknown quest line encountered: %s", args.questLine.c_str());
	}

    return nullptr;
}

QuestTask* QuestDeserializer::deserialize(QuestDeserializer::QuestDeserializationRequestArgs args)
{
    QuestLine* questLine = this->deserialize(QuestDeserializer::QuestLineDeserializationRequestArgs(args.questLine));

	if (questLine != nullptr && args.owner != nullptr)
	{
		return questLine->deserialize(args.owner, args.questTask, args.questTag);
	}
	else
	{
		CCLOG("Unknown quest line encountered: %s", args.questLine.c_str());
	}

	return nullptr;
}