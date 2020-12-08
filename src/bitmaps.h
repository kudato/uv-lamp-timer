#pragma once

// 64x64
const unsigned char logoImg [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x80, 0x03, 0x80, 0x00,
	0x00, 0x01, 0xe0, 0x01, 0x80, 0x07, 0x80, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x07, 0x80, 0x00,
	0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x0f, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00,
	0x07, 0x00, 0x1f, 0xe0, 0x07, 0xc0, 0x00, 0x00, 0x0f, 0xc0, 0x3f, 0x80, 0x01, 0xc0, 0x00, 0x00,
	0x07, 0xc0, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x07, 0x00, 0xe0, 0x70, 0x0e,
	0x00, 0x07, 0xc0, 0x0f, 0x00, 0xe0, 0xf0, 0x0e, 0x00, 0x07, 0x80, 0x0f, 0x01, 0xf0, 0xf0, 0x1e,
	0x00, 0x07, 0x80, 0x0f, 0x01, 0xf0, 0x70, 0x1e, 0x00, 0x0f, 0x00, 0x0f, 0x01, 0xf0, 0x78, 0x1e,
	0x00, 0x0f, 0x00, 0x0f, 0x01, 0xf0, 0x78, 0x1e, 0x00, 0x0f, 0x00, 0x0f, 0x01, 0xf0, 0x78, 0x1e,
	0x7c, 0x0f, 0x00, 0x0f, 0x01, 0xf0, 0x78, 0x1c, 0x7e, 0x0f, 0x00, 0x0f, 0x01, 0xf0, 0x78, 0x3c,
	0x7e, 0x0f, 0x00, 0x0f, 0x01, 0xf0, 0x3c, 0x3c, 0x7c, 0x0f, 0x00, 0x0f, 0x01, 0xe0, 0x3c, 0x3c,
	0x00, 0x0f, 0x00, 0x0f, 0x01, 0xe0, 0x3c, 0x3c, 0x00, 0x0f, 0x00, 0x07, 0x81, 0xe0, 0x1e, 0x78,
	0x00, 0x0f, 0x00, 0x07, 0xc3, 0xe0, 0x1e, 0x78, 0x00, 0x07, 0x80, 0x03, 0xff, 0xc0, 0x1f, 0xf8,
	0x00, 0x07, 0x80, 0x03, 0xff, 0x80, 0x0f, 0xf0, 0x00, 0x07, 0xc0, 0x00, 0xff, 0x00, 0x07, 0xe0,
	0x00, 0x03, 0xc0, 0x00, 0x7c, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0xf0, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x01, 0x80, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00,
	0x03, 0xc0, 0xfc, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x07, 0xc0, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00,
	0x0f, 0x80, 0x3f, 0x80, 0x01, 0xfc, 0x00, 0x00, 0x07, 0x00, 0x1f, 0xe0, 0x07, 0xf8, 0x00, 0x00,
	0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x80, 0x00,
	0x00, 0x00, 0xf0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x01, 0xe0, 0x01, 0x80, 0x07, 0x80, 0x00,
	0x00, 0x00, 0xe0, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 16x16 images
const unsigned char arrowImg [] PROGMEM = {
	0x00, 0x00, 0x00, 0xe0, 0x01, 0xf0, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0x7e, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x00, 0x7e, 0x00, 0xfc, 0x00, 0xf8, 0x01, 0xf0, 0x00, 0xe0, 0x00, 0x00
};

const unsigned char lightImg [] PROGMEM = {
	0x01, 0x80, 0x21, 0x84, 0x31, 0x8c, 0x39, 0x9c, 0x17, 0xe8, 0x0f, 0xf0, 0x0c, 0x30, 0xec, 0x37,
	0xec, 0x37, 0x0c, 0x30, 0x0e, 0x70, 0x1e, 0x78, 0x3f, 0xfc, 0x33, 0xcc, 0x03, 0xc0, 0x03, 0xc0
};

const unsigned char timerImg [] PROGMEM = {
	0x07, 0xe0, 0x03, 0xcc, 0x0f, 0xfe, 0x1f, 0xfe, 0x3f, 0xfc, 0x7f, 0xfe, 0x7c, 0x3e, 0x79, 0x9e,
	0xf9, 0xdf, 0x79, 0xde, 0x7c, 0x3e, 0x7c, 0x3e, 0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x0f, 0xf0
};

const unsigned char playImg [] PROGMEM = {
	0x78, 0x00, 0x7e, 0x00, 0x7f, 0x80, 0x67, 0xc0, 0x61, 0xf0, 0x60, 0xfc, 0x60, 0x3e, 0x60, 0x0e,
	0x60, 0x1e, 0x60, 0x3e, 0x60, 0xf8, 0x63, 0xe0, 0x67, 0xc0, 0x7f, 0x00, 0x7c, 0x00, 0x78, 0x00
};

const unsigned char pauseImg [] PROGMEM = {
	0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78,
	0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78
};

const unsigned char editImg [] PROGMEM = {
	0x00, 0x18, 0x00, 0x3c, 0x00, 0x7e, 0x00, 0xf7, 0x01, 0xff, 0x03, 0xfe, 0x07, 0xfc, 0x0f, 0xf8,
	0x1f, 0xf0, 0x3f, 0xe0, 0x3f, 0xc0, 0x6f, 0x80, 0x7f, 0x00, 0x7e, 0x00, 0xf8, 0x00, 0xc0, 0x00
};

const unsigned char exitImg [] PROGMEM = {
	0x00, 0x00, 0x10, 0x00, 0x70, 0x00, 0xff, 0xfc, 0xff, 0xfe, 0x70, 0x0f, 0x10, 0x07, 0x00, 0x03,
	0x00, 0x03, 0x00, 0x07, 0x00, 0x0f, 0xff, 0xfe, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char fireImg [] PROGMEM = {
	0x01, 0x80, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xe0, 0x03, 0x20, 0x06, 0x38, 0x1c, 0x78, 0x3c, 0xfc,
	0x39, 0xfc, 0x21, 0x6c, 0x23, 0x6c, 0x37, 0x3c, 0x36, 0x3c, 0x1e, 0x38, 0x0f, 0x70, 0x03, 0xe0
};
