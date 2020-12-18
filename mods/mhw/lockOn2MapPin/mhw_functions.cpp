#include "mhw_functions.h"

namespace MHW {
	namespace Targets {
		void pinMap(uintptr_t unknown, uintptr_t target, char isMonster) {
			PinMapActual(unknown, target, isMonster, 0);
		}
	}
}