#include "VaporWeb.h"

const float VaporWeb::dialogueHeight = 256.0f;

const int VaporWeb::cellColumns = 5;
const int VaporWeb::cellRows = 8;

VaporWeb* VaporWeb::create()
{
	VaporWeb* instance = new VaporWeb();

	instance->autorelease();

	return instance;
}

VaporWeb::VaporWeb()
{
	this->cells = new std::map<int, GridObject*>();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->forestBackground = Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Background);
	this->cavernsBackground = Sprite::create(Resources::Cutscenes_VaporWeb_Caverns_Background);
	this->obeliskBackground = Sprite::create(Resources::Cutscenes_VaporWeb_Obelisk_Background);
	this->grid = Grid::create();
	this->darkLord = Sprite::create(Resources::Cutscenes_VaporWeb_DarkLord);
	this->dialoguePlate = LayerColor::create(Color4B(64, 0, 64, 255), visibleSize.width, VaporWeb::dialogueHeight);
	this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneVaporWeb, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	for (int column = 0; column < VaporWeb::cellColumns; column++)
	{
		for (int row = 0; row < VaporWeb::cellRows; row++)
		{
			const float spacingRow = 2.0f;
			const float spacingColumn = 1.0f;
			const float offset = 3.0f;

			float gridRow = row * spacingRow + offset;
			float gridColumn = Grid::lineColumns / 2 - (VaporWeb::cellColumns / 2) * spacingColumn + column * spacingColumn;

			GridObject* cell = GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Cell), Vec2(gridRow, gridColumn), true);
			cell->setOpacity(0);

			this->cells->insert_or_assign(this->getCellIndex(row, column), cell);

			this->grid->addGridObject(cell);
		}
	}

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->forestBackground->setOpacity(0);
	this->cavernsBackground->setOpacity(0);
	this->obeliskBackground->setOpacity(0);

	this->forestBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->cavernsBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->obeliskBackground->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->darkLord->setVisible(false);

	this->addChild(InputManager::claimInstance());
	this->addChild(this->forestBackground);
	this->addChild(this->cavernsBackground);
	this->addChild(this->obeliskBackground);
	this->addChild(this->grid);
	this->addChild(this->darkLord);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

VaporWeb::~VaporWeb()
{
	delete(this->cells);
}

void VaporWeb::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->runCutscene();
}

void VaporWeb::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->forestBackground->setPosition(Vec2(visibleSize.width / 2.0f, this->grid->getHorizon() + VaporWeb::dialogueHeight));
	this->cavernsBackground->setPosition(Vec2(visibleSize.width / 2.0f, this->grid->getHorizon() + VaporWeb::dialogueHeight));
	this->obeliskBackground->setPosition(Vec2(visibleSize.width / 2.0f, this->grid->getHorizon() + VaporWeb::dialogueHeight));

	this->grid->setPosition(Vec2(0.0f, VaporWeb::dialogueHeight));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void VaporWeb::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(VaporWeb::onDialogueShown, this));
}

void VaporWeb::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void VaporWeb::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(6.0f),
		CallFunc::create([=]() {
		if (!this->dialogue->showNextDialogue())
		{
		}
	}),
	nullptr
	));
}

void VaporWeb::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Platformer_Volcano_Volcano);
}

void VaporWeb::runCutscene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CallFunc* nextCutscene = CallFunc::create([=]()
	{
		NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneIntroSpace);
	});

	this->runAction(Sequence::create(
		this->createCutsceneGridSetup(),
		this->createCutsceneForest(),
		this->createCutsceneCaverns(),
		this->createCutsceneObelisk(),
		nextCutscene,
		nullptr
	));
}

FiniteTimeAction* VaporWeb::createCutsceneGridSetup()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CallFunc* fadeInCells = CallFunc::create([=]()
	{
		const float fadeSpeed = 1.0f;
		const float rowDelay = 0.5f;

		for (int column = 0; column < VaporWeb::cellColumns; column++)
		{
			for (int row = 0; row < VaporWeb::cellRows; row++)
			{
				GridObject* cell = this->cells->at(this->getCellIndex(row, column));

				cell->runAction(Sequence::create(
					DelayTime::create(row * rowDelay),
					FadeIn::create(fadeSpeed),
					nullptr
				));
			}
		}
	});

	CallFunc* beginDialogue = CallFunc::create([=]()
	{
		this->dialogue->showNextDialogue();
	});

	CallFunc* darkLordMoveIn = CallFunc::create([=]()
	{
		const float fadeSpeed = 1.0f;
		const float destinationX = visibleSize.width / 2.0f - 96.0f;
		const float destinationY = 128.0f + VaporWeb::dialogueHeight;
		const float flyInTime = 3.0f;
		const float floatDelta = 64.0f;
		const float floatSpeed = 2.0f;

		this->darkLord->setPosition(Vec2(visibleSize.width / 3.0f, visibleSize.height + this->darkLord->getContentSize().height));
		this->darkLord->setVisible(true);
		this->darkLord->runAction(Sequence::create(
			EaseSineOut::create(MoveTo::create(flyInTime, Vec2(destinationX, destinationY + floatDelta))),
			CallFunc::create([=]()
			{
				this->darkLord->runAction(RepeatForever::create(Sequence::create(
					EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(destinationX, destinationY))),
					EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(destinationX, destinationY + floatDelta))),
					nullptr
				)));
			}),
			nullptr
			));
	});

	return Sequence::create(
		darkLordMoveIn,
		DelayTime::create(3.0f),
		beginDialogue,
		fadeInCells,
		DelayTime::create(4.0f),
		nullptr
	);
}

FiniteTimeAction* VaporWeb::createCutsceneForest()
{
	const float fadeSpeed = 1.0f;

	CallFunc* fadeInBackground = CallFunc::create([=]()
	{
		this->forestBackground->runAction(FadeIn::create(fadeSpeed));
	});

	CallFunc* fadeOutBackground = CallFunc::create([=]()
	{
		this->forestBackground->runAction(FadeOut::create(fadeSpeed));
	});

	CallFunc* addObjects = CallFunc::create([=]()
	{
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Tree1), Vec2(-2.0f, Grid::lineColumns / 2.0f - 3.5f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Tree2), Vec2(-3.0f, Grid::lineColumns / 2.0f + 3.0f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Shrine), Vec2(-10.0f, Grid::lineColumns / 2.0f + 0.0f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Ruins1), Vec2(-12.0f, Grid::lineColumns / 2.0f - 4.0f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Thorns1), Vec2(-15.0f, Grid::lineColumns / 2.0f - 2.0f), false));
	});

	return Sequence::create(
		fadeInBackground,
		addObjects,
		DelayTime::create(10.0f),
		fadeOutBackground,
		nullptr
	);
}

FiniteTimeAction* VaporWeb::createCutsceneCaverns()
{
	const float fadeSpeed = 1.0f;

	CallFunc* fadeInBackground = CallFunc::create([=]()
	{
		this->cavernsBackground->runAction(FadeIn::create(fadeSpeed));
	});

	CallFunc* fadeOutBackground = CallFunc::create([=]()
	{
		this->cavernsBackground->runAction(FadeOut::create(fadeSpeed));
	});

	CallFunc* addObjects = CallFunc::create([=]()
	{
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Caverns_DryTree1), Vec2(-2.0f, Grid::lineColumns / 2.0f - 3.5f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Caverns_DryTree2), Vec2(-3.0f, Grid::lineColumns / 2.0f + 3.0f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Caverns_Skulls), Vec2(-10.0f, Grid::lineColumns / 2.0f + 0.0f), false));
	});

	return Sequence::create(
		fadeInBackground,
		addObjects,
		DelayTime::create(8.0f),
		fadeOutBackground,
		nullptr
	);
}

FiniteTimeAction* VaporWeb::createCutsceneObelisk()
{
	const float fadeSpeed = 1.0f;

	CallFunc* fadeInBackground = CallFunc::create([=]()
	{
		this->obeliskBackground->runAction(FadeIn::create(fadeSpeed));
	});

	CallFunc* fadeOutBackground = CallFunc::create([=]()
	{
		this->obeliskBackground->runAction(FadeOut::create(fadeSpeed));
	});

	CallFunc* addObjects = CallFunc::create([=]()
	{
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Obelisk_Tree1), Vec2(-2.0f, Grid::lineColumns / 2.0f - 3.5f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Obelisk_Door), Vec2(-3.0f, Grid::lineColumns / 2.0f + 3.0f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Obelisk_Obelisk), Vec2(-9.0f, Grid::lineColumns / 2.0f - 2.0f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Obelisk_Tree2), Vec2(-12.0f, Grid::lineColumns / 2.0f + 3.0f), false));
		this->grid->addGridObject(GridObject::create(Sprite::create(Resources::Cutscenes_VaporWeb_Obelisk_Wall), Vec2(-13.0f, Grid::lineColumns / 2.0f - 4.0f), false));
	});

	return Sequence::create(
		fadeInBackground,
		addObjects,
		DelayTime::create(12.0f),
		nullptr
	);
}

int VaporWeb::getCellIndex(int row, int column)
{
	return VaporWeb::cellRows * column + row;
}
