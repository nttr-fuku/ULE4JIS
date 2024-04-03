
#include "stdafx.h"
#include "USonJISRemoteStrategy.h"
#include "NormalKeyEmulation.h"
#include "PressAndReleaseDecorator.h"
#include "ShiftPressDecorator.h"
#include "ShiftReleaseDecorator.h"
#include "NopEmulation.h"

void USonJISRemoteStrategy::getEmulationMap(EmulationMapType* dest) {

	dest->clear();

	// @
	dest->insert(
		KeyCondition('2', true),
		new ShiftReleaseDecorator(
			std::auto_ptr<Emulation>(new NormalKeyEmulation(VK_OEM_3))
		)
	);
	// ^
	dest->insert(
		KeyCondition('6', true),
		new ShiftReleaseDecorator(
			std::auto_ptr<Emulation>(new NormalKeyEmulation(VK_OEM_7))
		)
	);
	// &
	dest->insert(KeyCondition('7', true), new NormalKeyEmulation('6'));
	// *
	dest->insert(KeyCondition('8', true), new NormalKeyEmulation(VK_OEM_1));
	// (
	dest->insert(KeyCondition('9', true), new NormalKeyEmulation('8'));
	// )
	dest->insert(KeyCondition('0', true), new NormalKeyEmulation('9'));
	// _
	dest->insert(KeyCondition(VK_OEM_MINUS, true), new NormalKeyEmulation(VK_OEM_102));
	// =
	dest->insert(KeyCondition(VK_OEM_PLUS),
		new ShiftPressDecorator(std::auto_ptr<Emulation>(new NormalKeyEmulation(VK_OEM_MINUS))));
	// `
	dest->insert(KeyCondition(VK_OEM_3),
		new ShiftPressDecorator(std::auto_ptr<Emulation>(new NormalKeyEmulation(VK_OEM_3))));
	// ~
	dest->insert(KeyCondition(VK_OEM_3, true), new NormalKeyEmulation(VK_OEM_7));
	// ;
	dest->insert(KeyCondition(VK_OEM_1), new NormalKeyEmulation(VK_OEM_PLUS));
	// :
	dest->insert(
		KeyCondition(VK_OEM_1, true),
		new ShiftReleaseDecorator(
			std::auto_ptr<Emulation>(new NormalKeyEmulation(VK_OEM_1))
		)
	);
	// '
	dest->insert(
		KeyCondition(VK_OEM_7),
		new ShiftPressDecorator(
			std::auto_ptr<Emulation>(new NormalKeyEmulation('7'))
		)
	);
	// "
	dest->insert(KeyCondition(VK_OEM_7, true), new NormalKeyEmulation('2'));

	// ”¼Šp
	dest->insert(KeyCondition(VK_OEM_AUTO), new NopEmulation());
	dest->insert(KeyCondition(VK_OEM_AUTO, true), new NopEmulation());
	// ‘SŠp
	dest->insert(KeyCondition(VK_OEM_ENLW), new NopEmulation());
	dest->insert(KeyCondition(VK_OEM_ENLW, true), new NopEmulation());

}
