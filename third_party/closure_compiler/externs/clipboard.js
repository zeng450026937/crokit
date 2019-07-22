// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file was generated by:
//   tools/json_schema_compiler/compiler.py.
// NOTE: The format of types has changed. 'FooType' is now
//   'chrome.clipboard.FooType'.
// Please run the closure compiler before committing changes.
// See https://chromium.googlesource.com/chromium/src/+/master/docs/closure_compilation.md

/** @fileoverview Externs generated from namespace: clipboard */

/**
 * @const
 */
chrome.clipboard = {};

/**
 * @enum {string}
 * @see https://developer.chrome.com/extensions/clipboard#type-ImageType
 */
chrome.clipboard.ImageType = {
  PNG: 'png',
  JPEG: 'jpeg',
};

/**
 * @enum {string}
 * @see https://developer.chrome.com/extensions/clipboard#type-DataItemType
 */
chrome.clipboard.DataItemType = {
  TEXT_PLAIN: 'textPlain',
  TEXT_HTML: 'textHtml',
};

/**
 * @typedef {{
 *   type: !chrome.clipboard.DataItemType,
 *   data: string
 * }}
 * @see https://developer.chrome.com/extensions/clipboard#type-AdditionalDataItem
 */
chrome.clipboard.AdditionalDataItem;

/**
 * Sets image data to clipboard.
 * @param {ArrayBuffer} imageData The encoded image data.
 * @param {!chrome.clipboard.ImageType} type The type of image being passed.
 * @param {!Array<!chrome.clipboard.AdditionalDataItem>=} additionalItems
 *     Additional data items for describing image data. The callback is called
 *     with <code>chrome.runtime.lastError</code> set to error code if there is
 *     an error. Requires clipboard and clipboardWrite permissions.
 * @param {function():void=} callback
 * @see https://developer.chrome.com/extensions/clipboard#method-setImageData
 */
chrome.clipboard.setImageData = function(imageData, type, additionalItems, callback) {};

/**
 * Fired when clipboard data changes. Requires clipboard and clipboardRead
 * permissions for adding listener to chrome.clipboard.onClipboardDataChanged
 * event. After this event fires, the clipboard data is available by calling
 * document.execCommand('paste').
 * @type {!ChromeEvent}
 * @see https://developer.chrome.com/extensions/clipboard#event-onClipboardDataChanged
 */
chrome.clipboard.onClipboardDataChanged;
