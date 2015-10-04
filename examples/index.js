var fs = require('fs');
var ft = require('freetype2');

var face = {};
ft.New_Memory_Face(fs.readFileSync(process.argv[2]), 0, face);
face = face.face;

var ptSize = 70*64;
var device_hdpi = 72;
var device_vdpi = 72;
ft.Set_Char_Size(face, 0, ptSize, device_hdpi, device_vdpi );

var hb = require('../index.js');
var glyphs = hb(face.handle, process.argv[3]);
console.log(glyphs);
