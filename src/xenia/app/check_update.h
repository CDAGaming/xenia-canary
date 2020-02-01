/**
******************************************************************************
* Xenia : Xbox 360 Emulator Research Project                                 *
******************************************************************************
* Copyright 2015 Ben Vanik. All rights reserved.                             *
* Released under the BSD license - see LICENSE in the root for more details. *
******************************************************************************
*/

#ifndef XENIA_UPDATE_H_
#define XENIA_UPDATE_H_

namespace xe {
namespace update {

  class Update {
  public:
    static void CheckUpdate();
  private:
    // static int check_update();
  };
}  // namespace update
}  // namespace xe
#endif