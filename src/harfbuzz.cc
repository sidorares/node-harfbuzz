#include "hb.h"
#include "hb-ft.h"

#include <sstream>
#include <string>
#include <nan.h>

#include <iostream>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Array;

NAN_METHOD(Shape) {

  String::Utf8Value ftHandle(info[0]->ToString());
  String::Utf8Value input(info[1]->ToString());

  std::stringstream ss;
  ss << std::hex << *ftHandle;
  unsigned long ptr;
  ss >> ptr;
  FT_Face ft_face = reinterpret_cast<FT_Face>(ptr);

  hb_buffer_t *buf = hb_buffer_create();
  hb_font_t *hb_ft_font = hb_ft_font_create(ft_face, NULL);
  //hb_buffer_set_direction(buf, HB_DIRECTION_LTR);
  hb_buffer_set_direction(buf, HB_DIRECTION_RTL);
  //hb_buffer_set_script(buf, "en");

  int len = strlen(*input);
  hb_buffer_add_utf8(buf, *input, len, 0, len);
  hb_shape(hb_ft_font, buf, NULL, 0);

  unsigned int         glyph_count;
  hb_glyph_info_t     *glyph_info   = hb_buffer_get_glyph_infos(buf, &glyph_count);
  hb_glyph_position_t *glyph_pos    = hb_buffer_get_glyph_positions(buf, &glyph_count);

  Local<Array> glyphs = Nan::New<Array>(glyph_count);
  for (size_t i = 0; i < glyph_count; i++) {
    Local<Object> g = Nan::New<Object>();
    g->Set(Nan::New("xOffset").ToLocalChecked(), Nan::New<Number>(glyph_pos[i].x_offset));
    g->Set(Nan::New("yOffset").ToLocalChecked(), Nan::New<Number>(glyph_pos[i].y_offset));
    g->Set(Nan::New("xAdvance").ToLocalChecked(), Nan::New<Number>(glyph_pos[i].x_advance));
    g->Set(Nan::New("yAdvance").ToLocalChecked(), Nan::New<Number>(glyph_pos[i].y_advance));
    g->Set(Nan::New("codepoint").ToLocalChecked(), Nan::New<Number>(glyph_info[i].codepoint));
    g->Set(Nan::New("cluster").ToLocalChecked(), Nan::New<Number>(glyph_info[i].cluster));
    g->Set(Nan::New("mask").ToLocalChecked(), Nan::New<Number>(glyph_info[i].mask));

    glyphs->Set(i, g);
  }
  info.GetReturnValue().Set(glyphs);
}

void InitAll(Handle<Object> exports) {
  exports->Set(Nan::New<String>("shape").ToLocalChecked(), Nan::New<FunctionTemplate>(Shape)->GetFunction());
}

NODE_MODULE(addon, InitAll)
