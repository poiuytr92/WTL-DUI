// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/views/button_drag_utils.h"

#include "base/utf_string_conversions.h"
//#include "googleurl/src/gurl.h"
#include "grit/ui_resources.h"
#include "ui/base/dragdrop/drag_utils.h"
#include "ui/base/dragdrop/os_exchange_data.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/image/image.h"
#include "ui/views/controls/button/text_button.h"

namespace button_drag_utils {

// Maximum width of the link drag image in pixels.
static const int kLinkDragImageMaxWidth = 200;
//
//void SetURLAndDragImage(const GURL& url,
//                        const string16& title,
//                        const SkBitmap& icon,
//                        ui::OSExchangeData* data) {
//  DCHECK(url.is_valid() && data);
//
//  data->SetURL(url, title);
//
//  // Create a button to render the drag image for us.
//  views::TextButton button(NULL,
//                           title.empty() ? UTF8ToUTF16(url.spec()) : title);
//  button.set_max_width(kLinkDragImageMaxWidth);
//  if (icon.isNull()) {
//    button.SetIcon(*ui::ResourceBundle::GetSharedInstance().GetImageNamed(
//                   IDR_DEFAULT_FAVICON).ToSkBitmap());
//  } else {
//    button.SetIcon(icon);
//  }
//  gfx::Size prefsize = button.GetPreferredSize();
//  button.SetBounds(0, 0, prefsize.width(), prefsize.height());
//
//  // Render the image.
//  gfx::Canvas canvas(prefsize, false);
//  button.PaintButton(&canvas, views::TextButton::PB_FOR_DRAG);
//  drag_utils::SetDragImageOnDataObject(canvas, prefsize,
//      gfx::Point(prefsize.width() / 2, prefsize.height() / 2), data);
//}

}  // namespace button_drag_utils
