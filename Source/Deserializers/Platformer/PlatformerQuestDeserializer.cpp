#include "PlatformerQuestDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/Quests/PlatformerQuests.h"

using namespace cocos2d;

PlatformerQuestDeserializer* PlatformerQuestDeserializer::create()
{
	PlatformerQuestDeserializer* instance = new PlatformerQuestDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerQuestDeserializer::PlatformerQuestDeserializer() : super()
{
	this->lineDeserializers = std::map<std::string, std::function<QuestLine*()>>();

	// GLOBAL QUESTS
	this->lineDeserializers[CharterShipLine::MapKeyQuestLine] = [=]() { return (QuestLine*)CharterShipLine::create(); };
	this->lineDeserializers[RestoreWarpGatesLine::MapKeyQuestLine] = [=]() { return (QuestLine*)RestoreWarpGatesLine::create(); };
	
	// ENDIAN FOREST QUESTS
	this->lineDeserializers[BusinessHoursLine::MapKeyQuestLine] = [=]() { return (QuestLine*)BusinessHoursLine::create(); };
	this->lineDeserializers[HexusGauntletLine::MapKeyQuestLine] = [=]() { return (QuestLine*)HexusGauntletLine::create(); };
	this->lineDeserializers[IntroLine::MapKeyQuestLine] = [=]() { return (QuestLine*)IntroLine::create(); };
	this->lineDeserializers[FindElrielLine::MapKeyQuestLine] = [=]() { return (QuestLine*)FindElrielLine::create(); };
	this->lineDeserializers[PerceptronEncounterLine::MapKeyQuestLine] = [=]() { return (QuestLine*)PerceptronEncounterLine::create(); };
	this->lineDeserializers[RescueGuanoLine::MapKeyQuestLine] = [=]() { return (QuestLine*)RescueGuanoLine::create(); };
	this->lineDeserializers[SailForRuinsLine::MapKeyQuestLine] = [=]() { return (QuestLine*)SailForRuinsLine::create(); };
	this->lineDeserializers[SaveTownLine::MapKeyQuestLine] = [=]() { return (QuestLine*)SaveTownLine::create(); };
	this->lineDeserializers[SkyShipToTempleLine::MapKeyQuestLine] = [=]() { return (QuestLine*)SkyShipToTempleLine::create(); };
	this->lineDeserializers[SneakIntoLianasHouseLine::MapKeyQuestLine] = [=]() { return (QuestLine*)SneakIntoLianasHouseLine::create(); };
	this->lineDeserializers[WaterSpellbookLine::MapKeyQuestLine] = [=]() { return (QuestLine*)WaterSpellbookLine::create(); };
	this->lineDeserializers[WindSpellbookLine::MapKeyQuestLine] = [=]() { return (QuestLine*)WindSpellbookLine::create(); };

	// UNDERFLOW RUINS QUESTS
	this->lineDeserializers[ColosseumGauntletLine::MapKeyQuestLine] = [=]() { return (QuestLine*)ColosseumGauntletLine::create(); };
	this->lineDeserializers[CleansePyramidLine::MapKeyQuestLine] = [=]() { return (QuestLine*)CleansePyramidLine::create(); };
	this->lineDeserializers[CureTownLine::MapKeyQuestLine] = [=]() { return (QuestLine*)CureTownLine::create(); };

	// DATA MINES QUESTS
	this->lineDeserializers[DefeatRhinomanLine::MapKeyQuestLine] = [=]() { return (QuestLine*)DefeatRhinomanLine::create(); };
	this->lineDeserializers[RestorePowerLine::MapKeyQuestLine] = [=]() { return (QuestLine*)RestorePowerLine::create(); };
	this->lineDeserializers[MinesPerceptronEncounterLine::MapKeyQuestLine] = [=]() { return (QuestLine*)MinesPerceptronEncounterLine::create(); };

	// CASTLE VALGRIND QUESTS
	this->lineDeserializers[ArcaneBookLine::MapKeyQuestLine] = [=]() { return (QuestLine*)ArcaneBookLine::create(); };
	this->lineDeserializers[CureKingLine::MapKeyQuestLine] = [=]() { return (QuestLine*)CureKingLine::create(); };
	
	// LAMBDA CRYPTS QUESTS
	this->lineDeserializers[CraftDemonHeartLine::MapKeyQuestLine] = [=]() { return (QuestLine*)CraftDemonHeartLine::create(); };
	this->lineDeserializers[ElricsDemiseLine::MapKeyQuestLine] = [=]() { return (QuestLine*)ElricsDemiseLine::create(); };
	this->lineDeserializers[OpenCryptLine::MapKeyQuestLine] = [=]() { return (QuestLine*)OpenCryptLine::create(); };
	this->lineDeserializers[RezLazarusLine::MapKeyQuestLine] = [=]() { return (QuestLine*)RezLazarusLine::create(); };

	// DAEMONS HALLOW QUESTS
	this->lineDeserializers[DefeatAsmodeusLine::MapKeyQuestLine] = [=]() { return (QuestLine*)DefeatAsmodeusLine::create(); };
	this->lineDeserializers[ReleasePressureLine::MapKeyQuestLine] = [=]() { return (QuestLine*)ReleasePressureLine::create(); };
	
	// BALLMER PEAKS QUESTS
	
	// VOID STAR QUESTS
	this->lineDeserializers[PerceptronFightLine::MapKeyQuestLine] = [=]() { return (QuestLine*)PerceptronFightLine::create(); };
}

PlatformerQuestDeserializer::~PlatformerQuestDeserializer()
{
}

void PlatformerQuestDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	/*
		FORMATS SUPPORTED:
		1) QuestLine (single) / QuestTask (single)
		2) QuestLine (single) / QuestTask (multiple)
		3) QuestLine (multiple) / QuestTask (multiple) -- same count
	*/
	std::vector<std::string> questLines = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(properties, GameObject::MapKeyQuestLine, Value("")).asString(),
		",",
		false
	);
	std::vector<std::string> questTasks = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(properties, GameObject::MapKeyQuest, Value("")).asString(),
		",",
		false
	);

	while (!questLines.empty() && questLines.size() < questTasks.size())
	{
		questLines.push_back(questLines.front());
	}

	for (int index = 0; index < int(questTasks.size()); index++)
	{
		QuestTask* quest = this->deserialize(QuestDeserializer::QuestDeserializationRequestArgs(owner, questLines[index], questTasks[index]));

		if (quest != nullptr)
		{
			owner->addChild(quest);
		}
	}
}

std::string PlatformerQuestDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyQuestLine;
}
