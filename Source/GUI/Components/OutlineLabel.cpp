#include "OutlineLabel.h"

OutlineLabel * OutlineLabel::create(std::string labelText, std::string fontResource, float fontSize)
{
	OutlineLabel* outlineLabel = new OutlineLabel(labelText, fontResource, fontSize);

	outlineLabel->autorelease();

	return outlineLabel;
}

OutlineLabel::OutlineLabel(std::string labelText, std::string fontResource, float fontSize)
{
	this->label = Label::createWithTTF(labelText, fontResource, fontSize);
	this->labelHighlighted = Label::createWithTTF(labelText, fontResource, fontSize);

	this->label->enableOutline(Color4B::BLACK, fontOutlineSize);

	this->setCascadeOpacityEnabled(true);

	this->addChild(this->labelHighlighted);
	this->addChild(this->label);

	this->setContentSize(this->label->getContentSize());
}

OutlineLabel::~OutlineLabel()
{
}

void OutlineLabel::setColor(Color3B color)
{
	this->label->setColor(color);
}

void OutlineLabel::setText(std::string text)
{
	this->label->setString(text);
	this->labelHighlighted->setString(text);

	this->setContentSize(this->label->getContentSize());
}
