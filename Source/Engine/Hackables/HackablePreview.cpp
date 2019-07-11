#include "HackablePreview.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Common/XEqualsY.h"
#include "Strings/Hacking/RegisterEax.h"
#include "Strings/Hacking/RegisterEbx.h"
#include "Strings/Hacking/RegisterEcx.h"
#include "Strings/Hacking/RegisterEdx.h"
#include "Strings/Hacking/RegisterEdi.h"
#include "Strings/Hacking/RegisterEsi.h"
#include "Strings/Hacking/RegisterEbp.h"
#include "Strings/Hacking/RegisterEsp.h"
#include "Strings/Hacking/RegisterEip.h"
#include "Strings/Hacking/RegisterRax.h"
#include "Strings/Hacking/RegisterRbx.h"
#include "Strings/Hacking/RegisterRcx.h"
#include "Strings/Hacking/RegisterRdx.h"
#include "Strings/Hacking/RegisterRdi.h"
#include "Strings/Hacking/RegisterRsi.h"
#include "Strings/Hacking/RegisterRbp.h"
#include "Strings/Hacking/RegisterRsp.h"
#include "Strings/Hacking/RegisterRip.h"
#include "Strings/Hacking/RegisterR8.h"
#include "Strings/Hacking/RegisterR9.h"
#include "Strings/Hacking/RegisterR10.h"
#include "Strings/Hacking/RegisterR11.h"
#include "Strings/Hacking/RegisterR12.h"
#include "Strings/Hacking/RegisterR13.h"
#include "Strings/Hacking/RegisterR14.h"
#include "Strings/Hacking/RegisterR15.h"
#include "Strings/Hacking/RegisterSt0.h"
#include "Strings/Hacking/RegisterSt1.h"
#include "Strings/Hacking/RegisterSt2.h"
#include "Strings/Hacking/RegisterSt3.h"
#include "Strings/Hacking/RegisterSt4.h"
#include "Strings/Hacking/RegisterSt5.h"
#include "Strings/Hacking/RegisterSt6.h"
#include "Strings/Hacking/RegisterSt7.h"
#include "Strings/Hacking/RegisterXmm0.h"
#include "Strings/Hacking/RegisterXmm1.h"
#include "Strings/Hacking/RegisterXmm2.h"
#include "Strings/Hacking/RegisterXmm3.h"
#include "Strings/Hacking/RegisterXmm4.h"
#include "Strings/Hacking/RegisterXmm5.h"
#include "Strings/Hacking/RegisterXmm6.h"
#include "Strings/Hacking/RegisterXmm7.h"

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
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEax::create(): (LocalizedString*)Strings::Hacking_RegisterRax::create()));
		}
		case HackableCode::Register::zbx:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEbx::create(): (LocalizedString*)Strings::Hacking_RegisterRbx::create()));
		}
		case HackableCode::Register::zcx:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEcx::create(): (LocalizedString*)Strings::Hacking_RegisterRcx::create()));
		}
		case HackableCode::Register::zdx:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEdx::create(): (LocalizedString*)Strings::Hacking_RegisterRdx::create()));
		}
		case HackableCode::Register::zdi:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEdi::create(): (LocalizedString*)Strings::Hacking_RegisterRdi::create()));
		}
		case HackableCode::Register::zsi:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEsi::create(): (LocalizedString*)Strings::Hacking_RegisterRsi::create()));
		}
		case HackableCode::Register::zbp:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEbp::create(): (LocalizedString*)Strings::Hacking_RegisterRbp::create()));
		}
		case HackableCode::Register::zsp:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEsp::create(): (LocalizedString*)Strings::Hacking_RegisterRsp::create()));
		}
		case HackableCode::Register::zip:
		{
			return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_RegisterEip::create(): (LocalizedString*)Strings::Hacking_RegisterRip::create()));
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
		case HackableCode::Register::st0:
		{
			return Strings::Hacking_RegisterSt0::create();
		}
		case HackableCode::Register::st1:
		{
			return Strings::Hacking_RegisterSt1::create();
		}
		case HackableCode::Register::st2:
		{
			return Strings::Hacking_RegisterSt2::create();
		}
		case HackableCode::Register::st3:
		{
			return Strings::Hacking_RegisterSt3::create();
		}
		case HackableCode::Register::st4:
		{
			return Strings::Hacking_RegisterSt4::create();
		}
		case HackableCode::Register::st5:
		{
			return Strings::Hacking_RegisterSt5::create();
		}
		case HackableCode::Register::st6:
		{
			return Strings::Hacking_RegisterSt6::create();
		}
		case HackableCode::Register::st7:
		{
			return Strings::Hacking_RegisterSt7::create();
		}
		case HackableCode::Register::xmm0:
		{
			return Strings::Hacking_RegisterXmm0::create();
		}
		case HackableCode::Register::xmm1:
		{
			return Strings::Hacking_RegisterXmm1::create();
		}
		case HackableCode::Register::xmm2:
		{
			return Strings::Hacking_RegisterXmm2::create();
		}
		case HackableCode::Register::xmm3:
		{
			return Strings::Hacking_RegisterXmm3::create();
		}
		case HackableCode::Register::xmm4:
		{
			return Strings::Hacking_RegisterXmm4::create();
		}
		case HackableCode::Register::xmm5:
		{
			return Strings::Hacking_RegisterXmm5::create();
		}
		case HackableCode::Register::xmm6:
		{
			return Strings::Hacking_RegisterXmm6::create();
		}
		case HackableCode::Register::xmm7:
		{
			return Strings::Hacking_RegisterXmm7::create();
		}
	}
}
