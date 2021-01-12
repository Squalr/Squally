#include "LogicPuzzleController.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Interactables/Puzzles/LogicGate.h"

using namespace cocos2d;

const std::string LogicPuzzleController::MapKey = "logic-puzzle-controller";
const std::string LogicPuzzleController::PropertyOperation = "operation";
const std::string LogicPuzzleController::MapEventTorchLogicSwitchSavePrefix = "torch-logic-switched-by-save-";
const std::string LogicPuzzleController::MapEventTorchLogicSwitch = "torch-logic-switched";
const std::string LogicPuzzleController::MapEventSolveTorches = "solve-torches";
const std::string LogicPuzzleController::MapEventCheckComplete = "check-complete";
const std::string LogicPuzzleController::SaveKeyIsSolved = "SAVE_KEY_IS_SOLVED";

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

	
	ObjectEvents::QueryObjects(QueryObjectsArgs<Brazier>([=](Brazier* brazier)
	{
		this->braziers[brazier->getTorchColor()].push_back(brazier);
	}));
	
	ObjectEvents::QueryObjects(QueryObjectsArgs<LogicGate>([=](LogicGate* logicGate)
	{
		this->logicGates[logicGate->getTorchColor()] = logicGate;
	}));

	this->computeIsOpen(true);

	this->listenForMapEvent(LogicPuzzleController::MapEventTorchLogicSwitch, [=](ValueMap)
	{
		this->computeIsOpen(false);
	});

	/*
	this->listenForMapEvent(LogicPuzzleController::MapEventSolveTorches, [=](ValueMap)
	{
		this->saveObjectState(LogicPuzzleController::SaveKeyIsSolved, Value(true));
		this->checkComplete();
		this->computeIsOpen(false);
	});

	this->listenForMapEvent(LogicPuzzleController::MapEventCheckComplete, [=](ValueMap)
	{
		this->checkComplete();
		this->computeIsOpen(false);
	});
	*/
	
	/*
	this->isOn |= this->isSolved();

	static float TorchDelay = 0.0f;

	TorchDelay = 0.0f;

	// Listen for events if unsolved
	if (!this->isSolved() && !this->saveKey.empty())
	{
		this->isOn = SaveManager::GetProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();

		this->listenForMapEvent(Brazier::MapEventTorchLogicSwitchSavePrefix + this->saveKey, [=](ValueMap)
		{
			this->isOn = SaveManager::GetProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();
			
			this->updateBrazierVisibility();
		});

		// For torches with a save key, use a different mode to save! Allows cross map syncing.
		this->listenForMapEvent(Brazier::MapEventSolveTorches, [=](ValueMap)
		{
			SaveManager::SoftSaveProfileData(this->saveKey + "_" + Brazier::SaveKeyIsSolved, Value(true));
			this->setInteractType(InteractType::None);

			TorchDelay += 0.1f;

			this->runAction(Sequence::create(
				DelayTime::create(TorchDelay),
				CallFunc::create([=]()
				{
					this->torchOn();
				}),
				nullptr
			));
		});

		SaveManager::SoftSaveProfileData(this->saveKey, Value(this->isOn));
	}
	else if (!this->isSolved() && this->saveKey.empty())
	{
		// For torches with no save key, save as object state
		this->listenForMapEvent(Brazier::MapEventSolveTorches, [=](ValueMap)
		{
			this->saveObjectState(Brazier::SaveKeyIsSolved, Value(true));
			this->setInteractType(InteractType::None);

			TorchDelay += 0.1f;

			this->runAction(Sequence::create(
				DelayTime::create(TorchDelay),
				CallFunc::create([=]()
				{
					this->torchOn();
				}),
				nullptr
			));
		});
	}

	// Set interactable if unsolved
	if (!this->isSolved() && GameUtils::getKeyOrDefault(this->properties, Brazier::PropertyIsInteractable, Value(false)).asBool())
	{
		this->setInteractType(InteractType::Input);
	}
	*/
}


	/*
	if (!this->saveKey.empty())
	{
		SaveManager::SoftSaveProfileData(this->saveKey, Value(this->isOn()));

		this->broadcastMapEvent(Brazier::MapEventTorchLogicSwitchSavePrefix + this->saveKey, ValueMap());
		this->broadcastMapEvent(Brazier::MapEventTorchLogicSwitchPrefix + this->torchColorName, ValueMap());
	}

	this->broadcastMapEvent(Brazier::MapEventCheckComplete, ValueMap());
	*/

void LogicPuzzleController::initializePositions()
{
	super::initializePositions(); 
}

void LogicPuzzleController::initializeListeners()
{
	super::initializeListeners();
}

/*


bool Brazier::isSolved()
{
	if (this->saveKey.empty())
	{
		return this->loadObjectStateOrDefault(Brazier::SaveKeyIsSolved, Value(false)).asBool();
	}
	else
	{
		return SaveManager::GetProfileDataOrDefault(this->saveKey + "_" + Brazier::SaveKeyIsSolved, Value(false)).asBool();
	}
}
*/

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

/*
bool LogicPuzzleController::isSolved()
{
	return this->isOn() == this->answer;
}

void LogicPuzzleController::checkComplete()
{
	if (this->loadObjectStateOrDefault(Brazier::SaveKeyIsSolved, Value(false)).asBool())
	{
		return;
	}

	// Note: using variable firstRun here instead of local variable "areAllSolved", because reference capture lambdas are glitchy
	this->firstRun = this->isSolved();

	ObjectEvents::QueryObjects(QueryObjectsArgs<LogicGate>([=](LogicGate* logicGate)
	{
		this->firstRun &= logicGate->isSolved();
	}));

	bool areAllSolved = this->firstRun;

	if (areAllSolved)
	{
		this->broadcastMapEvent(Brazier::MapEventSolveTorches, ValueMap());
	}
}
*/

void LogicPuzzleController::computeIsOpen(bool isInstant)
{
	if (this->loadObjectStateOrDefault(LogicPuzzleController::SaveKeyIsSolved, Value(false)).asBool())
	{
		this->runGateAnims(isInstant);
		return;
	}

	for (const auto&[torchColor, logicGate] : this->logicGates)
	{
		if (!this->braziers.contains(torchColor))
		{
			continue;
		}

		bool isOpen = false;
		bool firstRun = true;

		for (Brazier* brazier : this->braziers[torchColor])
		{
			switch (this->operation)
			{
				case LogicPuzzleController::Operation::And:
				{
					isOpen = firstRun ? brazier->isOn() : (isOpen & brazier->isOn());
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

		logicGate->toggle(isOpen);
	}
}

void LogicPuzzleController::runGateAnims(bool isInstant)
{
	
}
