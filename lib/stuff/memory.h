#pragma once

#include <Windows.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace stuff {
	namespace memory {
		intptr_t readMem(HANDLE proc, intptr_t base, vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size);
		intptr_t writeMem(HANDLE proc, intptr_t base, vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size);

		class Helper {
		private:
			HANDLE proc;
			intptr_t base;
			void setProc(string exe);
		public:
			Helper() = delete;
			Helper(string exe);
			Helper(string exe, intptr_t base);
			intptr_t readMem(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size);
			intptr_t writeMem(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size);
			void readMem(intptr_t address, LPVOID buffer, SIZE_T size);
			void writeMem(intptr_t address, LPVOID buffer, SIZE_T size);
			intptr_t readMemNoBase(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size);
			intptr_t writeMemNoBase(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size);
		};
	}
}
