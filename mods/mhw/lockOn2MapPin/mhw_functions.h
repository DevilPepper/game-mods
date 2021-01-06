#pragma once
#include "pch.h"

namespace MHW {
	typedef void(__fastcall* PointerConsumer)(uintptr_t);

	namespace Targets {
		typedef void(__fastcall* PinMap)(uintptr_t, uintptr_t, char, char);

		static PointerConsumer lockOnInc = (PointerConsumer)0x1412a54a0;
		static PinMap PinMapActual = (PinMap)0x141dd3060;

		void pinMap(uintptr_t, uintptr_t, char);
	}
}
