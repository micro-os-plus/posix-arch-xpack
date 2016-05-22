/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2016 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * This file is part of the CMSIS++ proposal, intended as a CMSIS
 * replacement for C++ applications.
 *
 * It is included in `cmsis-plus/rtos/os.h` to customise
 * it with port specific declarations.
 */

#ifndef CMSIS_PLUS_RTOS_PORT_OS_DECLS_H_
#define CMSIS_PLUS_RTOS_PORT_OS_DECLS_H_

// ----------------------------------------------------------------------------

#include <cmsis-plus/rtos/os-app-config.h>
#include <cmsis-plus/rtos/port/os-c-decls.h>

#include <signal.h>
// Platform definitions
#include <sys/time.h>

// ----------------------------------------------------------------------------

#ifdef  __cplusplus

#include <cstdint>
#include <cstddef>

namespace os
{
  namespace rtos
  {
    namespace port
    {
      // ----------------------------------------------------------------------

      namespace stack
      {
        // Assume 64-bits core.
        using element_t = uint64_t;

        // Align stack to 8 bytes.
        using allocation_element_t = uint64_t;

        // Initial value for the minimum stack size in bytes.
        constexpr std::size_t min_size_bytes = SIGSTKSZ;

        // Initial value for the default stack size in bytes.
        constexpr std::size_t default_size_bytes = SIGSTKSZ;
      } /* namespace stack */

      namespace interrupts
      {
        // True if signal blocked
        using status_t = bool;

        constexpr status_t init_status = false;
      } /* namespace interrupts */

      namespace clock
      {
        constexpr int signal_number = SIGALRM;
      } /* namespace clock */

      using thread_context_t = struct thread_context_s
        {
          ucontext_t ucontext; //
        };

    // ------------------------------------------------------------------------

    } /* namespace port */
  } /* namespace rtos */
} /* namespace os */

// ----------------------------------------------------------------------------

#endif /* __cplusplus */

#if !defined(OS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES)
#define OS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES (SIGSTKSZ)
#endif

#if !defined(OS_INTEGER_RTOS_IDLE_STACK_SIZE_BYTES)
#define OS_INTEGER_RTOS_IDLE_STACK_SIZE_BYTES (SIGSTKSZ)
#endif

#endif /* CMSIS_PLUS_RTOS_PORT_OS_DECLS_H_ */
