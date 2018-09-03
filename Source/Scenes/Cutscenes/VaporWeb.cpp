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
	this->grid = Grid::create();
	this->darkLord = Sprite::create(Resources::Cutscenes_VaporWeb_DarkLord);
	this->dialoguePlate = LayerColor::create(Color4B(64, 0, 64, 255), visibleSize.width, VaporWeb::dialogueHeight);
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
	this->forestBackground->setVisible(false);
	this->darkLord->setVisible(false);

	this->addChild(InputManager::claimInstance());
	this->addChild(this->forestBackground);
	this->addChild(this->grid);
	this->addChild(this->darkLord);
	this->addChild(this->dialoguePlate);
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

	this->forestBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->forestBackground->setPosition(Vec2(visibleSize.width / 2.0f, this->grid->getHorizon() + VaporWeb::dialogueHeight));
	this->grid->setPosition(Vec2(0.0f, VaporWeb::dialogueHeight));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void VaporWeb::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void VaporWeb::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void VaporWeb::endCutscene()
{
	NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneIntroSpace);
}

void VaporWeb::runCutscene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CallFunc* dialogueBegin = CallFunc::create([=]()
	{

	});

	this->runAction(Sequence::create(
		dialogueBegin,
		this->createCutsceneGridSetup(),
		this->createCutsceneForest(),
		this->createCutsceneCaverns(),
		this->createCutsceneIceCaps(),
		this->createCutsceneObelisk(),
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
		this->forestBackground->setOpacity(0);
		this->forestBackground->setVisible(true);
		this->forestBackground->runAction(FadeIn::create(fadeSpeed));
	});

	return Sequence::create(
		fadeInBackground,
		DelayTime::create(4.0f),
		nullptr
	);
}

FiniteTimeAction* VaporWeb::createCutsceneCaverns()
{
	return Sequence::create(
		nullptr
	);
}

FiniteTimeAction* VaporWeb::createCutsceneIceCaps()
{
	return Sequence::create(
		nullptr
	);
}

FiniteTimeAction* VaporWeb::createCutsceneObelisk()
{
	return Sequence::create(
		nullptr
	);
}

int VaporWeb::getCellIndex(int row, int column)
{
	return VaporWeb::cellRows * column + row;
}
