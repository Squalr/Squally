#include "HackablePreview.h"

using namespace cocos2d;

const float HackablePreview::PreviewRadius = 156.0f;
const Color4B HackablePreview::RegisterColor = Color4B(86, 156, 214, 255);

HackablePreview::HackablePreview()
{
	this->assemblyTextNode = Node::create();
	this->previewNode = Node::create();

	this->assemblyTextNode->setVisible(false);

	this->addChild(this->previewNode);
	this->addChild(this->assemblyTextNode);
}

void HackablePreview::setAssemblyTextVisible(bool isVisible)
{
	this->assemblyTextNode->setVisible(isVisible);
}
