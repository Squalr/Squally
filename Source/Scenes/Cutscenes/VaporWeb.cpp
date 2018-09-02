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
	this->cells = new std::map<int, Sprite*>();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->forestBackground = Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Background);
	this->grid = Grid::create();
	this->darkLord = Sprite::create(Resources::Cutscenes_VaporWeb_DarkLord);
	this->dialoguePlate = LayerColor::create(Color4B(64, 0, 64, 255), visibleSize.width, VaporWeb::dialogueHeight);
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	for (int column = 0; column < VaporWeb::cellColumns; column++)
	{
		for (int row = 0; row < VaporWeb::cellRows; row++)
		{
			(*this->cells)[this->getCellIndex(row, column)] = Sprite::create(Resources::Cutscenes_VaporWeb_Cell);
			(*this->cells)[this->getCellIndex(row, column)]->setAnchorPoint(Vec2(0.5f, 0.0f));
		}
	}

	this->forestBackground->setVisible(false);
	this->darkLord->setVisible(false);

	this->addChild(InputManager::claimInstance());
	this->addChild(this->forestBackground);
	this->addChild(this->grid);

	// Add cells symmetrically to preserve proper Z order
	for (int column = 0; column <= VaporWeb::cellColumns / 2; column++)
	{
		for (int row = VaporWeb::cellRows - 1; row >= 0; row--)
		{
			(*this->cells)[this->getCellIndex(row, column)]->setVisible(false);
			this->grid->addChild((*this->cells)[this->getCellIndex(row, column)]);

			if (column != VaporWeb::cellColumns / 2)
			{
				(*this->cells)[this->getCellIndex(row, VaporWeb::cellColumns - column - 1)]->setVisible(false);
				this->grid->addChild((*this->cells)[this->getCellIndex(row, VaporWeb::cellColumns - column - 1)]);
			}
		}
	}

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

	this->cutsceneIntro();
}

void VaporWeb::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->forestBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->forestBackground->setPosition(Vec2(visibleSize.width / 2.0f, this->grid->getHorizon() + VaporWeb::dialogueHeight));

	this->grid->setPosition(Vec2(0.0f, VaporWeb::dialogueHeight));

	for (int row = 0; row < VaporWeb::cellRows; row++)
	{
		for (int column = 0; column < VaporWeb::cellColumns; column++)
		{
			const float spacingRow = 2.0f;
			const float spacingColumn = 1.0f;
			const float offset = 3.0f;

			float gridRow = row * spacingRow + offset;
			float gridColumn = Grid::lineColumns / 2 - (VaporWeb::cellColumns / 2) * spacingColumn + column * spacingColumn;

			(*this->cells)[this->getCellIndex(row, column)]->setScale(1.0f - row * 0.1f);
			(*this->cells)[this->getCellIndex(row, column)]->setPosition(this->grid->coordsToLocation(Vec2(gridRow, gridColumn)));
		}
	}

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

void VaporWeb::cutsceneIntro()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CallFunc* dialogBegin = CallFunc::create([=]()
	{

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

	const float rowDelay = 0.5f;

	CallFunc* fadeInCells = CallFunc::create([=]()
	{
		const float fadeSpeed = 1.0f;

		for (int rowIndex = 0; rowIndex < VaporWeb::cellRows; rowIndex++)
		{
			for (int columnIndex = 0; columnIndex < VaporWeb::cellColumns; columnIndex++)
			{
				(*this->cells)[this->getCellIndex(rowIndex, columnIndex)]->setOpacity(0);
				(*this->cells)[this->getCellIndex(rowIndex, columnIndex)]->setVisible(true);
				(*this->cells)[this->getCellIndex(rowIndex, columnIndex)]->runAction(Sequence::create(
					DelayTime::create(rowIndex * rowDelay),
					FadeIn::create(fadeSpeed),
					nullptr
				));
			}
		}
	});

	CallFunc* triggerNextEvent = CallFunc::create([=]()
	{
		this->cutsceneForest();
	});

	this->runAction(Sequence::create(
		darkLordMoveIn,
		dialogBegin,
		DelayTime::create(1.0f),
		fadeInCells,
		DelayTime::create(rowDelay * VaporWeb::cellRows),
		triggerNextEvent,
		nullptr
	));
}

void VaporWeb::cutsceneForest()
{
	const float fadeSpeed = 1.0f;

	CallFunc* dialogBegin = CallFunc::create([=]()
	{

	});

	CallFunc* fadeInBackground = CallFunc::create([=]()
	{
		this->forestBackground->setOpacity(0);
		this->forestBackground->setVisible(true);
		this->forestBackground->runAction(FadeIn::create(fadeSpeed));
	});

	CallFunc* triggerNextEvent = CallFunc::create([=]()
	{
		this->cutsceneCaverns();
	});

	this->runAction(Sequence::create(
		dialogBegin,
		fadeInBackground,
		DelayTime::create(4.0f),
		triggerNextEvent,
		nullptr
	));
}

void VaporWeb::cutsceneCaverns()
{

}

void VaporWeb::cutsceneIceCaps()
{

}

void VaporWeb::cutsceneObelisk()
{

}

int VaporWeb::getCellIndex(int row, int column)
{
	return VaporWeb::cellRows * column + row;
}
