#include "OptionWarp.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OptionWarp::MapKey = "option-warp";
const std::string OptionWarp::PropertyWarpFrom = "from";
const std::string OptionWarp::PropertyWarpTo = "to";
const std::string OptionWarp::PropertyZoom = "zoom";
const std::string OptionWarp::PropertyNoWarpCamera = "no-warp-camera";
const std::string OptionWarp::PropertyRelayer = "relayer";
const std::string OptionWarp::PropertyStrKey = "string";
const std::string OptionWarp::EventWarpToPrefix = "EVENT_WARP_TO_";

OptionWarp* OptionWarp::create(ValueMap& properties)
{
	OptionWarp* instance = new OptionWarp(properties);

	instance->autorelease();

	return instance;
}

OptionWarp::OptionWarp(ValueMap& properties) : super(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	std::string warpToList = GameUtils::getKeyOrDefault(this->properties, OptionWarp::PropertyWarpTo, Value("")).asString();

	this->from = GameUtils::getKeyOrDefault(this->properties, OptionWarp::PropertyWarpFrom, Value("")).asString();
	this->to = StrUtils::splitOn(warpToList, ", ", false);
	this->toStrKeys = this->to;
	this->warpCamera = !GameUtils::getKeyOrDefault(this->properties, OptionWarp::PropertyNoWarpCamera, Value(false)).asBool();
	this->relayer = GameUtils::getKeyOrDefault(this->properties, OptionWarp::PropertyRelayer, Value(false)).asBool();
	this->zoomOverride = GameUtils::getKeyOrDefault(this->properties, OptionWarp::PropertyZoom, Value(0.0f)).asFloat();
	this->canChooseOption = false;
	this->strKey = GameUtils::getKeyOrDefault(this->properties, OptionWarp::PropertyStrKey, Value("")).asString();

	this->addTag(this->from);

	this->setName("Warp from " + this->from + " to " + warpToList);
	this->setInteractType(InteractType::Input);
}

OptionWarp::~OptionWarp()
{
}

void OptionWarp::onEnter()
{
	super::onEnter();

	this->resolveToStrKeys();
}

void OptionWarp::initializePositions()
{
	super::initializePositions();
}

void OptionWarp::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(OptionWarp::EventWarpToPrefix + this->from, [=](ValueMap args)
	{
		ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
		{
			this->doRelayer();
			this->applyZoomOverride();

			PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(squally, GameUtils::getWorldCoords3D(this), this->warpCamera));
		}), Squally::MapKey);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_1 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(1))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_2 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(2))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_3 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(3))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_4 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(4))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_5 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(5))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_6 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(6))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_7 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(7))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_8 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(8))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_9 }, [=](InputEvents::InputArgs* args)
	{
		if (this->chooseOption(9))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_BACK, EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (this->cancelOptionChoice())
		{
			args->handle();
		}
	});
}

void OptionWarp::loadMap()
{
	this->openDialogue();
}
	
std::string OptionWarp::getStrKey()
{
	return this->strKey;
}

void OptionWarp::resolveToStrKeys()
{
	for (int index = 0; index < int(this->to.size()); index++)
	{
		ObjectEvents::WatchForObject<OptionWarp>(this, [=](OptionWarp* optionWarp)
		{
			this->toStrKeys[index] = optionWarp->getStrKey();
		}, this->to[index]);
	}
}

void OptionWarp::openDialogue()
{
	if (this->to.empty() || this->canChooseOption || this->squally == nullptr || this->squally->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, false))
	{
		return;
	}

	this->canChooseOption = true;
	PlatformerEvents::TriggerDisallowPause();
	
	LocalizedString* options = Strings::Common_Triconcat::create();
	LocalizedString* prelude = Strings::Common_Triconcat::create()
		->setStringReplacementVariables({Strings::Platformer_Objects_Warps_WhereTo::create(), Strings::Common_Newline::create(), options });
	LocalizedString* currentOption = options;
	int index = 1;

	for (auto it = toStrKeys.begin(); it != toStrKeys.end(); it++, index++)
	{
		std::string next = *it;
		bool lastIter = it == (--toStrKeys.end());
		LocalizedString* option = this->getOptionString(index, next);
		LocalizedString* nextOption = lastIter ? (LocalizedString*)Strings::Common_Empty::create() : (LocalizedString*)Strings::Common_Triconcat::create();

		currentOption->setStringReplacementVariables({option , Strings::Common_Newline::create(), nextOption });
		currentOption = nextOption;
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		prelude,
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(nullptr, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		"",
		true,
		false
	));
}

LocalizedString* OptionWarp::getOptionString(int index, std::string strKey)
{
	LocalizedString* optionText = nullptr;

	if (strKey == "back")
	{
		optionText = Strings::Platformer_Objects_Warps_Back::create();
	}
	else if (strKey == "mid" || strKey == "middle")
	{
		optionText = Strings::Platformer_Objects_Warps_Middle::create();
	}
	else if (strKey == "front")
	{
		optionText = Strings::Platformer_Objects_Warps_Front::create();
	}

	LocalizedString* dash = Strings::Common_Dash::create();
	LocalizedString* brackets = Strings::Common_Brackets::create();

	brackets->setStringReplacementVariables(ConstantString::create(std::to_string(index)));

	dash->setStringReplacementVariables({ brackets, optionText });

	return dash;
}

bool OptionWarp::cancelOptionChoice()
{
	if (!this->canChooseOption)
	{
		return false;
	}

	DialogueEvents::TriggerTryDialogueClose(DialogueEvents::DialogueCloseArgs([=]()
	{
		this->canChooseOption = false;
		PlatformerEvents::TriggerAllowPause();
	}));

	return true;
}
	
bool OptionWarp::chooseOption(int option)
{
	if (!this->canChooseOption || --option < 0 || option >= int(this->to.size()))
	{
		return false;
	}

	DialogueEvents::TriggerTryDialogueClose(DialogueEvents::DialogueCloseArgs([=]()
	{
		this->canChooseOption = false;
		PlatformerEvents::TriggerAllowPause();
		this->broadcastMapEvent(OptionWarp::EventWarpToPrefix + this->to[option], ValueMap());
	}));

	return true;
}

void OptionWarp::doRelayer()
{
	if (!this->relayer)
	{
		return;
	}

	MapLayer* layer = GameUtils::getFirstParentOfType<MapLayer>(this);

	if (layer != nullptr)
	{
		GameUtils::changeParent(squally, layer, true);
	}
}

void OptionWarp::applyZoomOverride()
{
	if (this->zoomOverride == 0.0f)
	{
		return;
	}

	CameraTrackingData* data = GameCamera::getInstance()->getCurrentTrackingData();

	if (data != nullptr)
	{
		data->zoom = this->zoomOverride;
	}
}
