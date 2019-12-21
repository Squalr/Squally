#include "HackablePreview.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Strings/Strings.h"

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
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_XEqualsY::create());

	if (isPointer)
	{
		LocalizedString* pointerString = Strings::Common_Brackets::create();

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
		case HackableCode::Register::zax:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEax::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRax::create()));
		}
		case HackableCode::Register::zbx:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEbx::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRbx::create()));
		}
		case HackableCode::Register::zcx:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEcx::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRcx::create()));
		}
		case HackableCode::Register::zdx:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEdx::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRdx::create()));
		}
		case HackableCode::Register::zdi:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEdi::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRdi::create()));
		}
		case HackableCode::Register::zsi:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEsi::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRsi::create()));
		}
		case HackableCode::Register::zbp:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEbp::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRbp::create()));
		}
		case HackableCode::Register::zsp:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEsp::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRsp::create()));
		}
		case HackableCode::Register::zip:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_RegisterEip::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRip::create()));
		}
		case HackableCode::Register::r8:
		{
			return Strings::Menus_Hacking_RegisterR8::create();
		}
		case HackableCode::Register::r9:
		{
			return Strings::Menus_Hacking_RegisterR9::create();
		}
		case HackableCode::Register::r10:
		{
			return Strings::Menus_Hacking_RegisterR10::create();
		}
		case HackableCode::Register::r11:
		{
			return Strings::Menus_Hacking_RegisterR11::create();
		}
		case HackableCode::Register::r12:
		{
			return Strings::Menus_Hacking_RegisterR12::create();
		}
		case HackableCode::Register::r13:
		{
			return Strings::Menus_Hacking_RegisterR13::create();
		}
		case HackableCode::Register::r14:
		{
			return Strings::Menus_Hacking_RegisterR14::create();
		}
		case HackableCode::Register::r15:
		{
			return Strings::Menus_Hacking_RegisterR15::create();
		}
		case HackableCode::Register::st0:
		{
			return Strings::Menus_Hacking_RegisterSt0::create();
		}
		case HackableCode::Register::st1:
		{
			return Strings::Menus_Hacking_RegisterSt1::create();
		}
		case HackableCode::Register::st2:
		{
			return Strings::Menus_Hacking_RegisterSt2::create();
		}
		case HackableCode::Register::st3:
		{
			return Strings::Menus_Hacking_RegisterSt3::create();
		}
		case HackableCode::Register::st4:
		{
			return Strings::Menus_Hacking_RegisterSt4::create();
		}
		case HackableCode::Register::st5:
		{
			return Strings::Menus_Hacking_RegisterSt5::create();
		}
		case HackableCode::Register::st6:
		{
			return Strings::Menus_Hacking_RegisterSt6::create();
		}
		case HackableCode::Register::st7:
		{
			return Strings::Menus_Hacking_RegisterSt7::create();
		}
		case HackableCode::Register::xmm0:
		{
			return Strings::Menus_Hacking_RegisterXmm0::create();
		}
		case HackableCode::Register::xmm1:
		{
			return Strings::Menus_Hacking_RegisterXmm1::create();
		}
		case HackableCode::Register::xmm2:
		{
			return Strings::Menus_Hacking_RegisterXmm2::create();
		}
		case HackableCode::Register::xmm3:
		{
			return Strings::Menus_Hacking_RegisterXmm3::create();
		}
		case HackableCode::Register::xmm4:
		{
			return Strings::Menus_Hacking_RegisterXmm4::create();
		}
		case HackableCode::Register::xmm5:
		{
			return Strings::Menus_Hacking_RegisterXmm5::create();
		}
		case HackableCode::Register::xmm6:
		{
			return Strings::Menus_Hacking_RegisterXmm6::create();
		}
		case HackableCode::Register::xmm7:
		{
			return Strings::Menus_Hacking_RegisterXmm7::create();
		}
	}
}
