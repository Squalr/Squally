#include "LogicPuzzleController.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Interactables/Puzzles/LogicGate.h"

using namespace cocos2d;

const std::string LogicPuzzleController::MapKey = "logic-puzzle-controller";
const std::string LogicPuzzleController::PropertyOperation = "operation";
const std::string LogicPuzzleController::SaveKeyIsSolved = "IS_SOLVED";

LogicPuzzleController* LogicPuzzleController::create(ValueMap& properties)
{
	LogicPuzzleController* instance = new LogicPuzzleController(properties);

	instance->autorelease();

	return instance;
}

LogicPuzzleController::LogicPuzzleController(ValueMap& properties) : super(properties)
{
	this->puzzleTag = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyTag, Value("")).asString();
	this->operationName = GameUtils::getKeyOrDefault(this->properties, LogicPuzzleController::PropertyOperation, Value("")).asString();
	this->operation = LogicPuzzleController::StrToOperation(this->operationName);
	this->braziers = std::map<Brazier::TorchColor, std::vector<Brazier*>>();
	this->logicGates = std::map<Brazier::TorchColor, LogicGate*>();
}

LogicPuzzleController::~LogicPuzzleController()
{
}

void LogicPuzzleController::onEnter()
{
	super::onEnter();

	this->isSolved = this->loadObjectStateOrDefault(LogicPuzzleController::SaveKeyIsSolved, Value(false)).asBool();

	ObjectEvents::QueryObjects<Brazier>([=](Brazier* brazier)
	{
		if (!brazier->isInteractable())
		{
			this->braziers[brazier->getTorchColor()].push_back(brazier);
		}
		
		this->listenForMapEvent(ToggleableObject::MapEventToggledBySave + brazier->getSaveKey(), [=](ValueMap)
		{
			this->defer([=]()
			{
				this->computeIsOpen(false);
			});
		});
	});
	
	ObjectEvents::QueryObjects<LogicGate>([=](LogicGate* logicGate)
	{
		this->logicGates[logicGate->getTorchColor()] = logicGate;
	});

	this->computeIsOpen(true);
}

void LogicPuzzleController::initializePositions()
{
	super::initializePositions(); 
}

void LogicPuzzleController::initializeListeners()
{
	super::initializeListeners();
}

LogicPuzzleController::Operation LogicPuzzleController::StrToOperation(std::string operationName)
{
	if (operationName == "and")
	{
		return Operation::And;
	}
	else if (operationName == "or")
	{
		return Operation::Or;
	}
	else if (operationName == "xor")
	{
		return Operation::Xor;
	}

	return Operation::None;
}

void LogicPuzzleController::computeIsOpen(bool isInstant)
{
	bool isCurrentlySolved = true;

	for (const auto&[torchColor, logicGate] : this->logicGates)
	{
		if (!this->braziers.contains(torchColor))
		{
			continue;
		}

		bool isOpen = this->braziers[torchColor].size() >= 2 && (this->operation == LogicPuzzleController::Operation::And ? true : false);

		for (Brazier* brazier : this->braziers[torchColor])
		{
			switch (this->operation)
			{
				case LogicPuzzleController::Operation::And:
				{
					isOpen &= brazier->isOn();
					break;
				}
				case LogicPuzzleController::Operation::Xor:
				{
					isOpen ^= brazier->isOn();
					break;
				}
				default:
				case LogicPuzzleController::Operation::Or:
				{
					isOpen |= brazier->isOn();
					break;
				}
			}
		}

		logicGate->toggle(isOpen, isInstant);
		isCurrentlySolved &= (isOpen == logicGate->getAnswer());
	}

	if (!this->isSolved && isCurrentlySolved)
	{
		this->isSolved = true;
		this->saveObjectState(LogicPuzzleController::SaveKeyIsSolved, Value(true));
		this->broadcastMapEvent(this->sendEvent, { });
	}
}
