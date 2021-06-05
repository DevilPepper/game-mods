#pragma once

#include <Windows.h>

#include <vector>

#include "memory/memory.h"
#pragma comment(lib, "stuff.lib")

using std::vector;

namespace MHW {
  intptr_t mhwBase = 0x140000000;

  /**
   * Reads into <code>buffer</code> the value found by traversing pointers
   * and returns the address this value was found at.
   * This works similar to how Cheat Engine handles pointers to pointers
   * <p>
   * This is an wrapper on <code>stuff::memory::readMem</code>
   * that passes <code>mhwBase</code> as <code>exeBase</code>
   *
   * @param  base    a base address to begin the traversal at
   * @param  offsets a list of offsets used for traversing pointers
   * @param  buffer  output variable to copy value from memory into
   * @param  <T>     the type of the output variable
   *                 (probably should be primitives or structs or arrays of them)
   * @return         address computed at the end of the traversal
   */
  template <typename T>
  intptr_t readMem(intptr_t base, const vector<intptr_t>& offsets, T& buffer) {
    return stuff::memory::readMem(base, offsets, buffer, mhwBase);
  }

  /**
   * Traverses pointers to write to memory the value in <code>buffer</code>
   * and returns the address that was written to.
   * This works similar to how Cheat Engine handles pointers to pointers
   * <p>
   * This is an wrapper on <code>stuff::memory::writeMem</code>
   * that passes <code>mhwBase</code> as <code>exeBase</code>
   *
   * @param  base    a base address to begin the traversal at
   * @param  offsets a list of offsets used for traversing pointers
   * @param  buffer  input variable that gets copied to memory
   * @param  <T>     the type of the input variable
   *                 (probably should be primitives or structs or arrays of them)
   * @return         address computed at the end of the traversal
   */
  template <typename T>
  intptr_t writeMem(intptr_t base, const vector<intptr_t>& offsets, T& buffer) {
    return stuff::memory::writeMem(base, offsets, buffer, mhwBase);
  }

  /**
   * Reads into <code>buffer</code> the value found by traversing pointers
   * and returns the address this value was found at.
   * This works similar to how Cheat Engine handles pointers to pointers.
   * This overload is for the special case where there is only 1 offset.
   * It's probably an unnecessary abstraction because this is trivial:
   * <code>*(*(exeBase + base) + offset)</code>
   * <p>
   * This is an wrapper on <code>stuff::memory::readMem</code>
   * that passes <code>mhwBase</code> as <code>exeBase</code>
   *
   * @param  base    a base address to begin the traversal at
   * @param  offset  a single offset used for traversing pointers
   * @param  buffer  output variable to copy value from memory into
   * @param  <T>     the type of the output variable
   *                 (probably should be primitives or structs or arrays of them)
   * @return         address computed at the end of the traversal
   */
  template <typename T>
  intptr_t readMem(intptr_t base, intptr_t offset, T& buffer) {
    return stuff::memory::readMem(base, offset, buffer, mhwBase);
  }

  /**
   * Traverses pointers to write to memory the value in <code>buffer</code>
   * and returns the address that was written to.
   * This works similar to how Cheat Engine handles pointers to pointers.
   * This overload is for the special case where there is only 1 offset.
   * It's probably an unnecessary abstraction because this is trivial:
   * <code>*(*(exeBase + base) + offset)</code>
   * <p>
   * This is an wrapper on <code>stuff::memory::writeMem</code>
   * that passes <code>mhwBase</code> as <code>exeBase</code>
   *
   * @param  base    a base address to begin the traversal at
   * @param  offset  a single offset used for traversing pointers
   * @param  buffer  input variable that gets copied to memory
   * @param  <T>     the type of the input variable
   *                 (probably should be primitives or structs or arrays of them)
   * @return         address computed at the end of the traversal
   */
  template <typename T>
  intptr_t writeMem(intptr_t base, intptr_t offset, T& buffer) {
    return stuff::memory::writeMem(base, offset, buffer, mhwBase);
  }
}  // namespace MHW
