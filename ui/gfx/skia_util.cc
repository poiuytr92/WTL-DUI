// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gfx/skia_util.h"

#include "base/i18n/char_iterator.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkColorPriv.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/core/SkUnPreMultiply.h"
#include "third_party/skia/include/effects/SkGradientShader.h"
#include "ui/gfx/rect.h"

namespace gfx {

SkRect RectToSkRect(const gfx::Rect& rect) {
  SkRect r;
  r.iset(rect.x(), rect.y(), rect.right(), rect.bottom());
  return r;
}

SkIRect RectToSkIRect(const gfx::Rect& rect) {
  SkIRect r = { rect.x(), rect.y(), rect.right(), rect.bottom() };
  return r;
}

gfx::Rect SkRectToRect(const SkRect& rect) {
  return gfx::Rect(static_cast<int>(rect.left()),
                   static_cast<int>(rect.top()),
                   static_cast<int>(rect.width()),
                   static_cast<int>(rect.height()));
}

SkShader* CreateGradientShader(int start_point,
                               int end_point,
                               SkColor start_color,
                               SkColor end_color) {
  SkColor grad_colors[2] = { start_color, end_color};
  SkPoint grad_points[2];
  grad_points[0].iset(0, start_point);
  grad_points[1].iset(0, end_point);

  return SkGradientShader::CreateLinear(
      grad_points, grad_colors, NULL, 2, SkShader::kRepeat_TileMode);
}

bool BitmapsAreEqual(const SkBitmap& bitmap1, const SkBitmap& bitmap2) {
  void* addr1 = NULL;
  void* addr2 = NULL;
  size_t size1 = 0;
  size_t size2 = 0;

  bitmap1.lockPixels();
  addr1 = bitmap1.getAddr32(0, 0);
  size1 = bitmap1.getSize();
  bitmap1.unlockPixels();

  bitmap2.lockPixels();
  addr2 = bitmap2.getAddr32(0, 0);
  size2 = bitmap2.getSize();
  bitmap2.unlockPixels();

  return (size1 == size2) && (0 == memcmp(addr1, addr2, bitmap1.getSize()));
}

string16 RemoveAcceleratorChar(const string16& s,
                               char16 accelerator_char,
                               int *accelerated_char_pos,
                               int *accelerated_char_span) {
   bool escaped = false;
   int last_char_pos = -1;
   int last_char_span = 0;
   base::i18n::UTF16CharIterator chars(&s); 
   string16 accelerator_removed;

   accelerator_removed.reserve(s.size());
   while (!chars.end()) {
	   int32 c = chars.get();
	   int array_pos = chars.array_pos();
	   chars.Advance();

	   if (c != accelerator_char || escaped) {
		   int span = chars.array_pos() - array_pos;
		   if (escaped && c != accelerator_char) {
			   last_char_pos = accelerator_removed.size();
			   last_char_span = span;
		   }
		   for (int i = 0; i < span; i++)
			   accelerator_removed.push_back(s[array_pos + i]);
		   escaped = false;
	   } else {
		   escaped = true;
	   }
   }

   if (accelerated_char_pos)
	   *accelerated_char_pos = last_char_pos;
   if (accelerated_char_span)
	   *accelerated_char_span = last_char_span;
 return accelerator_removed;
}

void ConvertSkiaToRGBA(const unsigned char* skia,
                       int pixel_width,
                       unsigned char* rgba) {
  int total_length = pixel_width * 4;
  for (int i = 0; i < total_length; i += 4) {
    const uint32_t pixel_in = *reinterpret_cast<const uint32_t*>(&skia[i]);

    // Pack the components here.
    int alpha = SkGetPackedA32(pixel_in);
    if (alpha != 0 && alpha != 255) {
      SkColor unmultiplied = SkUnPreMultiply::PMColorToColor(pixel_in);
      rgba[i + 0] = SkColorGetR(unmultiplied);
      rgba[i + 1] = SkColorGetG(unmultiplied);
      rgba[i + 2] = SkColorGetB(unmultiplied);
      rgba[i + 3] = alpha;
    } else {
      rgba[i + 0] = SkGetPackedR32(pixel_in);
      rgba[i + 1] = SkGetPackedG32(pixel_in);
      rgba[i + 2] = SkGetPackedB32(pixel_in);
      rgba[i + 3] = alpha;
    }
  }
}

}  // namespace gfx
