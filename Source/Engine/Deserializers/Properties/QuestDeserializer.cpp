#include "QuestDeserializer.h"

#include "Engine/Quests/QuestLine.h"
#include "Engine/Utils/LogUtils.h"

using namespace cocos2d;

QuestDeserializer::QuestDeserializer()
{
}

QuestDeserializer::~QuestDeserializer()
{
}

QuestLine* QuestDeserializer::deserialize(QuestDeserializer::QuestLineDeserializationRequestArgs args)
{
	if (this->lineDeserializers.contains(args.questLine))
	{
		return this->lineDeserializers[args.questLine]();
	}
	else
	{
		LogUtils::logError("Unknown quest line encountered: " + args.questLine);
	}

    return nullptr;
}

QuestTask* QuestDeserializer::deserialize(QuestDeserializer::QuestDeserializationRequestArgs args)
{
    QuestLine* questLine = this->deserialize(QuestDeserializer::QuestLineDeserializationRequestArgs(args.questLine));

	if (questLine != nullptr && args.owner != nullptr)
	{
		return questLine->deserialize(args.owner, args.questTask);
	}
	else
	{
		LogUtils::logError("Unknown quest line encountered: " + args.questLine);
	}

	return nullptr;
}