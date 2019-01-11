#include "HackablePreview.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Strings/Generics/Brackets.h"
#include "Strings/Generics/XEqualsY.h"
#include "Strings/Hacking/RegisterEax.h"
#include "Strings/Hacking/RegisterEbx.h"
#include "Strings/Hacking/RegisterEcx.h"
#include "Strings/Hacking/RegisterEdx.h"
#include "Strings/Hacking/RegisterEdi.h"
#include "Strings/Hacking/RegisterEsi.h"
#include "Strings/Hacking/RegisterEbp.h"
#include "Strings/Hacking/RegisterEsp.h"
#include "Strings/Hacking/RegisterRax.h"
#include "Strings/Hacking/RegisterRbx.h"
#include "Strings/Hacking/RegisterRcx.h"
#include "Strings/Hacking/RegisterRdx.h"
#include "Strings/Hacking/RegisterRdi.h"
#include "Strings/Hacking/RegisterRsi.h"
#include "Strings/Hacking/RegisterRbp.h"
#include "Strings/Hacking/RegisterRsp.h"
#include "Strings/Hacking/RegisterR8.h"
#include "Strings/Hacking/RegisterR9.h"
#include "Strings/Hacking/RegisterR10.h"
#include "Strings/Hacking/RegisterR11.h"
#include "Strings/Hacking/RegisterR12.h"
#include "Strings/Hacking/RegisterR13.h"
#include "Strings/Hacking/RegisterR14.h"
#include "Strings/Hacking/RegisterR15.h"

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

LocalizedLabel* HackablePreview::createRegisterEqualsValueLabel(HackableCode::Register reg, bool isPointer, ConstantString* value)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Generics_XEqualsY::create());

	if (isPointer)
	{
		LocalizedString* pointerString = Strings::Generics_Brackets::create();

		pointerString->setStringReplacementVariables(this->getRegisterString(reg));

		label->setStringReplacementVariables({ pointerString, value });
	}
	else
	{
		label->setStringReplacementVariables({ this->getRegisterString(reg), value });
	}

	label->setTextColor(HackablePreview::RegisterColor);
	label->enableOutline(Color4B::BLACK, 2);

	return label;
}

LocalizedString* HackablePreview::getRegisterString(HackableCode::Register reg)
{
	switch (reg)
	{
		default:
		case HackableCode::Register::eax:
		{
			return Strings::Hacking_RegisterEax::create();
		}
		case HackableCode::Register::ebx:
		{
			return Strings::Hacking_RegisterEbx::create();
		}
		case HackableCode::Register::ecx:
		{
			return Strings::Hacking_RegisterEcx::create();
		}
		case HackableCode::Register::edx:
		{
			return Strings::Hacking_RegisterEdx::create();
		}
		case HackableCode::Register::edi:
		{
			return Strings::Hacking_RegisterEdi::create();
		}
		case HackableCode::Register::esi:
		{
			return Strings::Hacking_RegisterEsi::create();
		}
		case HackableCode::Register::ebp:
		{
			return Strings::Hacking_RegisterEbp::create();
		}
		case HackableCode::Register::esp:
		{
			return Strings::Hacking_RegisterEsp::create();
		}
		case HackableCode::Register::rax:
		{
			return Strings::Hacking_RegisterRax::create();
		}
		case HackableCode::Register::rbx:
		{
			return Strings::Hacking_RegisterRbx::create();
		}
		case HackableCode::Register::rcx:
		{
			return Strings::Hacking_RegisterRcx::create();
		}
		case HackableCode::Register::rdx:
		{
			return Strings::Hacking_RegisterRdx::create();
		}
		case HackableCode::Register::rdi:
		{
			return Strings::Hacking_RegisterRdi::create();
		}
		case HackableCode::Register::rsi:
		{
			return Strings::Hacking_RegisterRsi::create();
		}
		case HackableCode::Register::rbp:
		{
			return Strings::Hacking_RegisterRbp::create();
		}
		case HackableCode::Register::rsp:
		{
			return Strings::Hacking_RegisterRsp::create();
		}
		case HackableCode::Register::r8:
		{
			return Strings::Hacking_RegisterR8::create();
		}
		case HackableCode::Register::r9:
		{
			return Strings::Hacking_RegisterR9::create();
		}
		case HackableCode::Register::r10:
		{
			return Strings::Hacking_RegisterR10::create();
		}
		case HackableCode::Register::r11:
		{
			return Strings::Hacking_RegisterR11::create();
		}
		case HackableCode::Register::r12:
		{
			return Strings::Hacking_RegisterR12::create();
		}
		case HackableCode::Register::r13:
		{
			return Strings::Hacking_RegisterR13::create();
		}
		case HackableCode::Register::r14:
		{
			return Strings::Hacking_RegisterR14::create();
		}
		case HackableCode::Register::r15:
		{
			return Strings::Hacking_RegisterR15::create();
		}
	}
}
