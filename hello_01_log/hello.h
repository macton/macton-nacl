// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include <stdint.h>

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/ppb.h"

const int kInvalidInstance = 0;
const int kInvalidResource = 0;

struct InstanceInfo 
{
  PPB_GetInterface browser_interface;
  PP_Instance      instance_id;
};
