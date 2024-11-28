/*
@file    EVE_supplemental.h
@brief   prototypes for supplemental functions
@version 5.0
@date    2024-11-01
@author  Rudolph Riedel

@section LICENSE

MIT License

Copyright (c) 2016-2024 Rudolph Riedel

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

@section History

5.0
- added EVE_polar_cartesian()
- moved EVE_calibrate_manual() over from EVE_commands
- added EVE_calibrate_write() and EVE_calibrate_read()

*/

#ifndef EVE_SUPPLEMENTAL_H
#define EVE_SUPPLEMENTAL_H

#include "EVE.h"
#include "EVE_commands.h"

#ifdef __cplusplus
extern "C"
{
#endif

void EVE_widget_circle(int16_t xc0, int16_t yc0, uint16_t radius, uint16_t border, uint32_t bgcolor);
void EVE_widget_rectangle(int16_t xc0, int16_t yc0, int16_t wid, int16_t hgt, int16_t border, uint16_t linewidth, uint32_t bgcolor);
void EVE_polar_cartesian(uint16_t length, uint16_t angle, int16_t *p_xc0, int16_t *p_yc0);

void EVE_calibrate_write(uint32_t tta, uint32_t ttb, uint32_t ttc, uint32_t ttd, uint32_t tte, uint32_t ttf);
void EVE_calibrate_read(uint32_t *p_tta, uint32_t *p_ttb, uint32_t *p_ttc, uint32_t *p_ttd, uint32_t *p_tte, uint32_t *p_ttf);
void EVE_calibrate_manual(uint16_t width, uint16_t height);

#endif /* EVE_SUPPLEMENTAL_H */
