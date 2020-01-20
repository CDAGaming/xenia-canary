/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_VFS_DEVICES_NULL_DEVICE_H_
#define XENIA_VFS_DEVICES_NULL_DEVICE_H_

#include <string>

#include "xenia/vfs/device.h"

namespace xe {
namespace vfs {

class NullEntry;

class NullDevice : public Device {
 public:
  NullDevice(const std::string& mount_path,
             const std::initializer_list<std::string>& null_paths);
  ~NullDevice() override;

  bool Initialize() override;
  void Dump(StringBuffer* string_buffer) override;
  Entry* ResolvePath(const std::string& path) override;

  bool is_read_only() const override { return false; }

  uint32_t total_allocation_units() const override { return 128 * 1024; }
  uint32_t available_allocation_units() const override { return 128 * 1024; }

  // STFC/cache code seems to require the product of these two to equal 0x10000
  // or 0x8000! (depending on SectorsPerCluster value written to partition
  // header)
  uint32_t sectors_per_allocation_unit() const override {
    return sectors_per_allocation_unit_;
  }
  uint32_t bytes_per_sector() const override { return 512; }

  void sectors_per_allocation_unit(uint32_t value) {
    sectors_per_allocation_unit_ = value;
  }

 private:
  std::unique_ptr<Entry> root_entry_;
  std::vector<std::string> null_paths_;

  uint32_t sectors_per_allocation_unit_ = 0x80;
};

}  // namespace vfs
}  // namespace xe

#endif  // XENIA_VFS_DEVICES_NULL_DEVICE_H_
