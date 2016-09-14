/* Copyright (c) 2016 Matthew Else. All rights reserved.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 Matthew Else
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "jerryscript-mbed-util/logging.h"
#include "jerryscript-mbed-library-registry/wrap_tools.h"

#include "ChainableLED.h"
#include "mbed.h"

DECLARE_CLASS_FUNCTION(ChainableLED, setColorRGB)
{
    CHECK_ARGUMENT_COUNT(ChainableLED, setColorRGB, (args_count == 4));
    CHECK_ARGUMENT_TYPE_ALWAYS(ChainableLED, __constructor, 0, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(ChainableLED, __constructor, 1, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(ChainableLED, __constructor, 2, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(ChainableLED, __constructor, 3, number);

    uint32_t led_num = (uint32_t)jsmbed_wrap_unbox_number(args[0]);
    uint8_t r = (uint8_t)jsmbed_wrap_unbox_number(args[1]);
    uint8_t g = (uint8_t)jsmbed_wrap_unbox_number(args[2]);
    uint8_t b = (uint8_t)jsmbed_wrap_unbox_number(args[3]);

    uintptr_t native_ptr = jsmbed_wrap_get_native_handle(this_obj);

    ((ChainableLED*)native_ptr)->setColorRGB(led_num, r, g, b);

    return jerry_create_undefined();
}

void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(ChainableLED) (uintptr_t handle) {
    delete (ChainableLED*) handle;
}

DECLARE_CLASS_CONSTRUCTOR(ChainableLED) {
    CHECK_ARGUMENT_COUNT(ChainableLED, __constructor, (args_count == 3));
    CHECK_ARGUMENT_TYPE_ALWAYS(ChainableLED, __constructor, 0, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(ChainableLED, __constructor, 1, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(ChainableLED, __constructor, 2, number);

    int clk_pin = jsmbed_wrap_unbox_number(args[0]);
    int sda_pin = jsmbed_wrap_unbox_number(args[1]);
    int num_leds = jsmbed_wrap_unbox_number(args[2]);

    uintptr_t native_ptr = (uintptr_t)new ChainableLED((PinName)clk_pin, (PinName)sda_pin, (PinName)num_leds);

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_handle(js_object, native_handle, NAME_FOR_CLASS_NATIVE_DESTRUCTOR(ChainableLED));

    return js_object;
}
