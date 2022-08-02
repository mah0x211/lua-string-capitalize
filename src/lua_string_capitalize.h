/**
 *  Copyright (C) 2022 Masatoshi Fukunaga
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

#ifndef lua_string_capitalize_h
#define lua_string_capitalize_h

#include <ctype.h>
#include <lauxlib.h>
#include <lua.h>

#define is_utf8tail(c) (((c)&0xC0) == 0x80)

static inline unsigned char *skip(unsigned char *s)
{
    size_t cur = 0;

    /* check byte width
     * UTF8-octets = *( UTF8-char )
     * UTF8-char: UTF8-1 / UTF8-2 / UTF8-3 / UTF8-4
     * UTF8-tail: %x80-BF = bit & 0xC0 == 0x80 */
    switch (s[cur]) {
    // 00-7F
    case 0x1 ... 0x7F:
        return s + 1;

    // C2-DF 1*UTF8-tail
    case 0xC2 ... 0xDF:
        if (is_utf8tail(s[cur + 1])) {
            return s + 2;
        }
        return s + 1;

    // E0 A0-BF 1*UTF8-tail
    case 0xE0:
        if (0xA0 <= s[cur + 1] && s[cur + 1] <= 0xBF &&
            is_utf8tail(s[cur + 2])) {
            return s + 3;
        }
        // invalid range: E0 80-9F
        return s + 1;

    // E1-EC 2*UTF8-tail
    case 0xE1 ... 0xEC:
        if (is_utf8tail(s[cur + 1]) && is_utf8tail(s[cur + 2])) {
            return s + 3;
        }
        return s + 1;

    // ED 80-9F 1*UTF8-tail
    case 0xED:
        if (0x80 <= s[cur + 1] && s[cur + 1] <= 0x9F &&
            is_utf8tail(s[cur + 2])) {
            return s + 3;
        }
        // inavlid range: ED A0-..
        return s + 1;

    // EE-EF 80-BF 1*UTF8-tail
    case 0xEE ... 0xEF:
        if (is_utf8tail(s[cur + 1]) && is_utf8tail(s[cur + 2])) {
            return s + 3;
        }
        return s + 1;

    // F0 90-BF 2*UTF8-tail
    case 0xF0:
        if (0x90 <= s[cur + 1] && s[cur + 1] <= 0xBF &&
            is_utf8tail(s[cur + 2]) && is_utf8tail(s[cur + 3])) {
            return s + 4;
        }
        // inavlid range: F0 80-9F
        return s + 1;

    // F1-F3 3*UTF8-tail
    case 0xF1 ... 0xF3:
        if (is_utf8tail(s[cur + 1]) && is_utf8tail(s[cur + 2]) &&
            is_utf8tail(s[cur + 3])) {
            return s + 4;
        }
        return s + 1;

    // F4 80-8F 2*UTF8-tail
    case 0xF4:
        if (0x80 <= s[cur + 1] && s[cur + 1] <= 0x8F &&
            is_utf8tail(s[cur + 2]) && is_utf8tail(s[cur + 3])) {
            return s + 4;
        }
        // inavlid range: F4 90-..
        return s + 1;

        /* continuation bytes: 0x80-BF
         * invalid: 0xC0-C1
         * invalid byte sequence to be 0xFFFD
        case 0x80 ... 0xC1:
            // invalid utf8
        break;
        */
    default:
        return s + 1;
    }
}

static inline void lua_string_capitalize(lua_State *L, const char *str)
{
    unsigned char *head = (unsigned char *)str;
    unsigned char *tail = head;
    luaL_Buffer b       = {0};

    // create copy
    luaL_buffinit(L, &b);

    // skip non-letter
    while (*tail) {
        if (*tail == '_') {
            tail++;
SKIP_LETTERS:
            while (*tail == '_' || isalnum(*tail)) {
                tail++;
            }
            // skip apostrophe
            if (*tail == '\'') {
                tail++;
                while (*tail == '_' || isalnum(*tail)) {
                    tail++;
                }
            }
            continue;
        } else if (isalnum(*tail)) {
            if (islower(*tail)) {
                luaL_addlstring(&b, (const char *)head, tail - head);
                // convert to uppercase
                luaL_addchar(&b, *tail - 0x20);
                head = tail + 1;
            }
            tail++;
            goto SKIP_LETTERS;
        }
        tail = skip(tail);
    }

    luaL_addlstring(&b, (const char *)head, tail - head);
    luaL_pushresult(&b);
}

#endif
