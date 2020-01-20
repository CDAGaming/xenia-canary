/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/vfs/devices/null_file.h"

#include "xenia/vfs/devices/null_device.h"
#include "xenia/vfs/devices/null_entry.h"

namespace xe {
namespace vfs {

NullFile::NullFile(uint32_t file_access, NullEntry* entry)
    : File(file_access, entry) {}

NullFile::~NullFile() = default;

void NullFile::Destroy() { delete this; }

X_STATUS NullFile::ReadSync(void* buffer, size_t buffer_length,
                            size_t byte_offset, size_t* out_bytes_read) {
  if (!(file_access_ & FileAccess::kFileReadData)) {
    return X_STATUS_ACCESS_DENIED;
  }

  return X_STATUS_SUCCESS;
}

X_STATUS NullFile::WriteSync(const void* buffer, size_t buffer_length,
                             size_t byte_offset, size_t* out_bytes_written) {
  if (!(file_access_ &
        (FileAccess::kFileWriteData | FileAccess::kFileAppendData))) {
    return X_STATUS_ACCESS_DENIED;
  }

  // Check if game is writing a FATX header...
  if (byte_offset == 0 && buffer_length >= (4 * 3)) {
    auto* header = (uint32_t*)buffer;
    if (xe::load_and_swap<uint32_t>(header) == 0x58544146) {
      // This is a FATX header - read the SectorsPerCluster value from it
      // Game will try reading this back through NtQueryVolumeInformationFile
      // later on, if it doesn't match, cache partition mount won't succeed
      auto sectors_per_cluster = xe::byte_swap(header[2]);
      // Update NullDevice with the SectorsPerCluster value
      auto* null_device = (NullDevice*)entry_->device();
      null_device->sectors_per_allocation_unit(sectors_per_cluster);
    }
  }

  return X_STATUS_SUCCESS;
}

X_STATUS NullFile::SetLength(size_t length) {
  if (!(file_access_ & FileAccess::kFileWriteData)) {
    return X_STATUS_ACCESS_DENIED;
  }

  return X_STATUS_SUCCESS;
}

}  // namespace vfs
}  // namespace xe
