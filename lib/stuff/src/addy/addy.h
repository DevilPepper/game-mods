#pragma once

#include <windows.h>

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

namespace stuff {
  namespace addy {
    extern string getAddressFilePath();

    typedef vector<intptr_t> Offsets;
    typedef intptr_t Pointer;

    class Addy {
     private:
      map<string, Offsets> offsets;
      map<string, intptr_t> address;
      nlohmann::json json;

      const Offsets& getOffsets(string node);
      const intptr_t& getPointer(string node);

     public:
      Addy();

      template <typename T>
      const T& get(string node) {
        return json[node].get<T>();
      }

      template <>
      const intptr_t& get<intptr_t>(string node) {
        return getPointer(node);
      }

      template <>
      const Offsets& get<Offsets>(string node) {
        return getOffsets(node);
      }
    };
  }  // namespace addy
}  // namespace stuff
