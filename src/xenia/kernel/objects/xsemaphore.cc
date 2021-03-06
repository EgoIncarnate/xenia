/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/kernel/objects/xsemaphore.h"

namespace xe {
namespace kernel {

XSemaphore::XSemaphore(KernelState* kernel_state)
    : XObject(kernel_state, kTypeSemaphore), native_handle_(NULL) {}

XSemaphore::~XSemaphore() {
  if (native_handle_) {
    CloseHandle(native_handle_);
  }
}

void XSemaphore::Initialize(int32_t initial_count, int32_t maximum_count) {
  assert_null(native_handle_);

  CreateNative(sizeof(X_SEMAPHORE));

  native_handle_ = CreateSemaphore(NULL, initial_count, maximum_count, NULL);
}

void XSemaphore::InitializeNative(void* native_ptr, X_DISPATCH_HEADER& header) {
  assert_null(native_handle_);

  // NOT IMPLEMENTED
  // We expect Initialize to be called shortly.
}

int32_t XSemaphore::ReleaseSemaphore(int32_t release_count) {
  LONG previous_count = 0;
  ::ReleaseSemaphore(native_handle_, release_count, &previous_count);
  return previous_count;
}

}  // namespace kernel
}  // namespace xe
