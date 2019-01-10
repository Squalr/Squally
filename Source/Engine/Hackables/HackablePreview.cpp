#include "HackablePreview.h"

using namespace cocos2d;

HackablePreview::HackablePreview()
{
	this->assemblyTextNode = Node::create();
	this->previewNode = Node::create();

	this->addChild(this->previewNode);
	this->addChild(this->assemblyTextNode);
}

void HackablePreview::setAssemblyTextVisible(bool isVisible)
{
	this->assemblyTextNode->setVisible(isVisible);
}
