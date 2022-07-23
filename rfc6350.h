/* https://datatracker.ietf.org/doc/html/rfc6350#page-9 */
#ifndef RFC6350_H
#define RFC6350_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>



static inline
size_t rfc6360_read_vcard(FILE *_fp, char _b[], size_t _bsz, const char **_opt_err) {
    size_t pos   = 0;
    int    state = 0;
    if (_opt_err) *_opt_err = NULL;
    while (fgets(_b+pos, _bsz-pos, _fp)) {
        _b[_bsz-1] = '\0';
        if (state == 0 && !strncmp(_b+pos, "BEGIN:VCARD", 11)) {
            state = 1;
        } else if (state == 1 && !strncmp(_b+pos, "END:VCARD", 9)) {
            state = 2;
            _b[pos] = '\0';
            break;
        } else {
            size_t l = strlen(_b+pos);
            if (l > 1 && _b[pos+l-1]=='\n') {
                pos += l;
            } else {
                if (_opt_err) *_opt_err = "An VCARD exceeds the size limit.";
                return -1;
            }
        }
    }
    switch(state) {
    case 0: return 0;
    case 1: if (_opt_err) { *_opt_err = "An VCARD doesn't end properly."; } return 0;
    case 2: return pos;
    default: return 0;
    }
}

static inline
char *rfc6360_read_property(char _b[], size_t _bsz, size_t *_p) {
    size_t start = *_p;
    size_t ptr   = *_p;
    size_t bpos  = *_p;
    
    while (ptr < _bsz) {
        size_t space = _bsz - ptr;
        if (space >= 3 && !strncmp(_b+ptr, "\r\n ", 3)) {
            ptr += 3;
            continue;
        } else if (space >= 2 && !strncmp(_b+ptr, "\n "  , 2)) {
            ptr += 2;
            continue;
        } else if (space >= 2 && !strncmp(_b+ptr, "\r\n", 2)) {
            _b[bpos] = '\0';
            *_p = (ptr + 2);
            return _b+start;
        } else if (space >= 1 && !strncmp(_b+ptr, "\n"  , 1)) {
            _b[bpos] = '\0';
            *_p = (ptr + 1);
            return _b+start;
        } else if (bpos < ptr) {
            _b[bpos++] = _b[ptr++];
        } else {
            bpos++;
            ptr++;
        }
    }
    *_p = ptr;
    return NULL;
}

static inline
bool rfc6360_split_property(char _b[], char **_var, char **_val) {
    char *p = strchr(_b, ':');
    if (p) {
        *p = '\0';
        *_var = _b;
        *_val = p+1;
        return true;
    } else {
        return false;
    }
}

#endif
/**l*
 * 
 * MIT License
 * 
 * Bug reports, feature requests to gemini|https://harkadev.com/oss
 * Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **l*/
