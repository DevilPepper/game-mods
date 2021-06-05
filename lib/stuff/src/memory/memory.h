#pragma once

#include <Windows.h>

#include <vector>

using std::vector;

namespace stuff {
  namespace memory {
    /**
     * Returns an address found by jumping to addresses pointed by <code>address + offset</code>
     * for each offset in the list except the last. The last offset is added to the found address.
     * You probably want to use <code>readMem</code> or <code>writeMem</code> instead.
     *
     * @param  base    a base address to begin the traversal at
     * @param  offsets a list of offsets similar to how Cheat Engine represents pointers to pointers
     * @param  exeBase optional param used to add a constant to <code>base</code>.
     *                 Useful if wrapped to simplify base addresses that have a common addend.
     *                 Default = 0
     * @return         address computed at the end of the traversal
     */
    intptr_t followPointers(intptr_t base, const vector<intptr_t>& offsets, intptr_t exeBase = 0);

    /**
     * Returns an address found by reading the value at <code>exeBase+base</code>
     * and adding <code>offset</code> to it.
     * You probably want to use <code>readMem</code> or <code>writeMem</code> instead.
     *
     * @param  base    a base address to read from
     * @param  offset  an offset to add to the read pointer value
     * @param  exeBase optional param used to add a constant to <code>base</code>.
     *                 Useful if wrapped to simplify base addresses that have a common addend.
     *                 Default = 0
     * @return         address computed from <code>memory_value + offset</code>
     */
    intptr_t followPointer(intptr_t base, intptr_t offset, intptr_t exeBase = 0);

    /**
     * Reads into <code>buffer</code> the value found by traversing pointers
     * and returns the address this value was found at.
     * This works similar to how Cheat Engine handles pointers to pointers
     *
     * @param  base    a base address to begin the traversal at
     * @param  offsets a list of offsets used for traversing pointers
     * @param  buffer  output variable to copy value from memory into
     * @param  exeBase optional param used to add a constant to <code>base</code>.
     *                 Useful if wrapped to simplify base addresses that have a common addend.
     *                 Default = 0
     * @param  <T>     the type of the output variable
     *                 (probably should be primitives or structs or arrays of them)
     * @return         address computed at the end of the traversal
     */
    template <typename T>
    intptr_t readMem(intptr_t base,
                     const vector<intptr_t>& offsets,
                     T& buffer,
                     intptr_t exeBase = 0) {
      auto addy = followPointers(base, offsets, exeBase);
      buffer = *(T*)addy;
      return addy;
    }

    /**
     * Traverses pointers to write to memory the value in <code>buffer</code>
     * and returns the address that was written to.
     * This works similar to how Cheat Engine handles pointers to pointers
     *
     * @param  base    a base address to begin the traversal at
     * @param  offsets a list of offsets used for traversing pointers
     * @param  buffer  input variable that gets copied to memory
     * @param  exeBase optional param used to add a constant to <code>base</code>.
     *                 Useful if wrapped to simplify base addresses that have a common addend.
     *                 Default = 0
     * @param  <T>     the type of the input variable
     *                 (probably should be primitives or structs or arrays of them)
     * @return         address computed at the end of the traversal
     */
    template <typename T>
    intptr_t writeMem(intptr_t base,
                      const vector<intptr_t>& offsets,
                      T& buffer,
                      intptr_t exeBase = 0) {
      auto addy = followPointers(base, offsets, exeBase);
      *(T*)addy = buffer;
      return addy;
    }

    /**
     * Reads into <code>buffer</code> the value found by traversing pointers
     * and returns the address this value was found at.
     * This works similar to how Cheat Engine handles pointers to pointers.
     * This overload is for the special case where there is only 1 offset.
     * It's probably an unnecessary abstraction because this is trivial:
     * <code>*(*(exeBase + base) + offset)</code>
     *
     * @param  base    a base address to begin the traversal at
     * @param  offset  a single offset used for traversing pointers
     * @param  buffer  output variable to copy value from memory into
     * @param  exeBase optional param used to add a constant to <code>base</code>.
     *                 Useful if wrapped to simplify base addresses that have a common addend.
     *                 Default = 0
     * @param  <T>     the type of the output variable
     *                 (probably should be primitives or structs or arrays of them)
     * @return         address computed at the end of the traversal
     */
    template <typename T>
    intptr_t readMem(intptr_t base, intptr_t offset, T& buffer, intptr_t exeBase = 0) {
      auto addy = followPointer(base, offset, exeBase);
      buffer = *(T*)addy;
      return addy;
    }

    /**
     * Traverses pointers to write to memory the value in <code>buffer</code>
     * and returns the address that was written to.
     * This works similar to how Cheat Engine handles pointers to pointers.
     * This overload is for the special case where there is only 1 offset.
     * It's probably an unnecessary abstraction because this is trivial:
     * <code>*(*(exeBase + base) + offset)</code>
     *
     * @param  base    a base address to begin the traversal at
     * @param  offset  a single offset used for traversing pointers
     * @param  buffer  input variable that gets copied to memory
     * @param  exeBase optional param used to add a constant to <code>base</code>.
     *                 Useful if wrapped to simplify base addresses that have a common addend.
     *                 Default = 0
     * @param  <T>     the type of the input variable
     *                 (probably should be primitives or structs or arrays of them)
     * @return         address computed at the end of the traversal
     */
    template <typename T>
    intptr_t writeMem(intptr_t base, intptr_t offset, T& buffer, intptr_t exeBase = 0) {
      auto addy = followPointer(base, offset, exeBase);
      *(T*)addy = buffer;
      return addy;
    }
  }  // namespace memory
}  // namespace stuff
