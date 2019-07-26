#include "HelpSquallyHeal.h"

using namespace cocos2d;

const std::string HelpSquallyHeal::MapKeyQuest = "help-squally-heal";

HelpSquallyHeal::HelpSquallyHeal() : super(HelpSquallyHeal::MapKeyQuest)
{
}

HelpSquallyHeal::~HelpSquallyHeal()
{
}

void HelpSquallyHeal::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent();
}
