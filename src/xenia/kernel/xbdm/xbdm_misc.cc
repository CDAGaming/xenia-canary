/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/base/logging.h"
#include "xenia/kernel/kernel_state.h"
#include "xenia/kernel/util/shim_utils.h"
#include "xenia/kernel/xbdm/xbdm_private.h"
#include "xenia/kernel/xthread.h"
#include "xenia/xbox.h"

#define XBDM_ERROR(err) (0x82DA0000 | (err & 0xFFFF))

namespace xe {
namespace kernel {
namespace xbdm {

void DmCloseLoadedModules(lpdword_t unk0_ptr) {}
DECLARE_XBDM_EXPORT1(DmCloseLoadedModules, kDebug, kStub);

void DmSendNotificationString(lpdword_t unk0_ptr) {}
DECLARE_XBDM_EXPORT1(DmSendNotificationString, kDebug, kStub);

dword_result_t DmWalkLoadedModules(lpdword_t unk0_ptr, lpdword_t unk1_ptr) {
  return X_STATUS_INVALID_PARAMETER;
}
DECLARE_XBDM_EXPORT1(DmWalkLoadedModules, kDebug, kStub);

dword_result_t DmCaptureStackBackTrace(lpdword_t unk0_ptr, lpdword_t unk1_ptr) {
  return X_STATUS_INVALID_PARAMETER;
}
DECLARE_XBDM_EXPORT1(DmCaptureStackBackTrace, kDebug, kStub);

void DmMapDevkitDrive() {}
DECLARE_XBDM_EXPORT1(DmMapDevkitDrive, kDebug, kStub);

dword_result_t DmFindPdbSignature(lpdword_t unk0_ptr, lpdword_t unk1_ptr) {
  return X_STATUS_INVALID_PARAMETER;
}
DECLARE_XBDM_EXPORT1(DmFindPdbSignature, kDebug, kStub);

dword_result_t DmGetXbeInfo(pointer_t<char> path, pointer_t<uint8_t> info) {
  // TODO: get full path of path parameter, and copy it into info[0:0x100]
  memset(info, 0, 0x10C);
  return X_ERROR_SUCCESS;
}
DECLARE_XBDM_EXPORT1(DmGetXbeInfo, kDebug, kStub);

dword_result_t DmGetXboxName(pointer_t<char> name, lpdword_t name_len) {
  std::string box_name = "XeniaBox";
  if (!name_len) {
    return XBDM_ERROR(0x17);  // xbdm invalid arg error code?
  }

  auto orig_len = *name_len;
  *name_len = (uint32_t)box_name.length() + 1;

  if (orig_len < *name_len) {
    return XBDM_ERROR(0x105);  // xbdm buffer size error code?
  }

  // Limit console name size to 255 chars
  auto name_size = std::min((uint32_t)box_name.length(), 255u);

  memcpy(name, box_name.c_str(), name_size);
  name[name_size] = 0;

  return X_ERROR_SUCCESS;
}
DECLARE_XBDM_EXPORT1(DmGetXboxName, kDebug, kImplemented);

dword_result_t DmIsDebuggerPresent() { return 0; }
DECLARE_XBDM_EXPORT1(DmIsDebuggerPresent, kDebug, kStub);

dword_result_t DmRegisterCommandProcessor(dword_t r3, dword_t r4) {
  return X_ERROR_SUCCESS;
}
DECLARE_XBDM_EXPORT1(DmRegisterCommandProcessor, kDebug, kStub);

dword_result_t DmRegisterCommandProcessorEx(dword_t r3, dword_t r4,
                                            dword_t r5) {
  return X_ERROR_SUCCESS;
}
DECLARE_XBDM_EXPORT1(DmRegisterCommandProcessorEx, kDebug, kStub);

dword_result_t DmSetDumpSettings(dword_t r3) { return X_ERROR_SUCCESS; }
DECLARE_XBDM_EXPORT1(DmSetDumpSettings, kDebug, kStub);

void RegisterMiscExports(xe::cpu::ExportResolver* export_resolver,
                         KernelState* kernel_state) {}

}  // namespace xbdm
}  // namespace kernel
}  // namespace xe
