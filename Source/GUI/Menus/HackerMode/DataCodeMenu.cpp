#include "DataCodeMenu.h"

const Size DataCodeMenu::maxPreviewSize = Size(340.0f, 340.0f);

DataCodeMenu* DataCodeMenu::create()
{
	DataCodeMenu* dataCodeMenu = new DataCodeMenu();

	dataCodeMenu->autorelease();

	return dataCodeMenu;
}

DataCodeMenu::DataCodeMenu()
{
	this->activeHackableObject = nullptr;
	this->hackableObjectPreview = nullptr;

	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 196));
	this->menuBackground = Sprite::create(Resources::Menus_HackerModeMenu_RadialMenu);
	this->dataButton = MenuSprite::create(Resources::Menus_Buttons_Ram, Resources::Menus_Buttons_RamHover, Resources::Menus_Buttons_RamClick);
	this->codeButton = MenuSprite::create(Resources::Menus_Buttons_CpuChip, Resources::Menus_Buttons_CpuChipHover, Resources::Menus_Buttons_CpuChipClick);
	this->returnButton = MenuSprite::create(Resources::Menus_Buttons_Return, Resources::Menus_Buttons_ReturnHover, Resources::Menus_Buttons_ReturnClick);

	this->gamePostProcessNightVision = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_NightVision);

	this->addChild(this->layerColor);
	this->addChild(this->menuBackground);
	this->addChild(this->dataButton);
	this->addChild(this->codeButton);
	this->addChild(this->returnButton);

	this->addChild(this->gamePostProcessNightVision);

	this->initializePositions();
	this->initializeListeners();
}

DataCodeMenu::~DataCodeMenu()
{
}

void DataCodeMenu::activate(HackableObject::HackableObjectEditArgs* hackableObjectArgs)
{
	// Remove existing preview image
	if (this->hackableObjectPreview != nullptr)
	{
		this->removeChild(this->hackableObjectPreview);
	}

	// Set target hackable object
	this->activeHackableObject = hackableObjectArgs->hackableObject;
	this->hackableObjectPreview = Sprite::create(hackableObjectArgs->previewResource);
	this->setVisible(true);

	// Position preview image and scale it
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->hackableObjectPreview->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	Size originalSize = this->hackableObjectPreview->getContentSize();
	Size overFlowSize = originalSize - DataCodeMenu::maxPreviewSize;

	if (overFlowSize.width > 0.0f && overFlowSize.width >= overFlowSize.height)
	{
		this->hackableObjectPreview->setScale(DataCodeMenu::maxPreviewSize.width / originalSize.width);
	}
	else if (overFlowSize.height > 0.0f)
	{
		this->hackableObjectPreview->setScale(DataCodeMenu::maxPreviewSize.height / originalSize.height);
	}

	this->addChild(this->hackableObjectPreview);

	// Ensure that this menu is running
	Utils::resume(this);
}

void DataCodeMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->layerColor->setContentSize(Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
	this->menuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->dataButton->setPosition(Vec2(visibleSize.width / 2.0f - 320.0f, visibleSize.height / 2.0f));
	this->codeButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 320.0f));
}

void DataCodeMenu::initializeListeners()
{
	this->dataButton->setClickCallback(CC_CALLBACK_1(DataCodeMenu::onClose, this));
	this->codeButton->setClickCallback(CC_CALLBACK_1(DataCodeMenu::onClose, this));
	this->returnButton->setClickCallback(CC_CALLBACK_1(DataCodeMenu::onClose, this));
}

void DataCodeMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::resume(Director::getInstance()->getRunningScene());
}

void DataCodeMenu::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (this->hackableObjectPreview != nullptr)
	{
		this->hackableObjectPreview->setVisible(true);
		this->gamePostProcessNightVision->draw(this->hackableObjectPreview);
		this->hackableObjectPreview->setVisible(false);
	}
}
