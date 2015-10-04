/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/rvagg/nan/blob/master/LICENSE.md>
 ********************************************************************/

var addon = require('./build/Release/addon');
module.exports = function(ftFaceHandle, text) {
  return addon.shape(ftFaceHandle, text);
};
