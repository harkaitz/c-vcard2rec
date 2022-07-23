#include "rfc6350.h"
#include <ctype.h>

#define COPYRIGHT_LINE \
    "Bug reports, feature requests to gemini|https://harkadev.com/oss" "\n" \
    "Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com" "\n" \
    ""

static
char *vcard2rec_var(char *_s) {
    for (size_t i=0; _s[i]; i++) {
        if (strchr(";=-", _s[i])) {
            _s[i] = '_';
        } else {
            _s[i] = tolower(_s[i]);
        }
    }
    return _s;
}

int main (int _argc, char *_argv[]) {
    
    char        vcard[1024*10]; /* Maximun of 10kB per vcard. */
    size_t      vcardsz;
    char       *property;
    const char *error;
    size_t      property_pos;
    char       *var,*val;

    if (_argc > 1 && (!strcmp(_argv[1], "-h") || !strcmp(_argv[1], "--help"))) {
        printf("Usage: vcard2rec < VCARD > REC"                             "\n"
               ""                                                           "\n"
               "Convert from RFC-6350 vCard format to GNU Recutils format." "\n"
               ""                                                           "\n"
               COPYRIGHT_LINE);
        return 0;
    }
    
    while (( vcardsz = rfc6360_read_vcard(stdin, vcard, sizeof(vcard), &error))) {
        property_pos = 0;
        while (( property = rfc6360_read_property(vcard, vcardsz, &property_pos))) {
            if (!rfc6360_split_property(property, &var, &val)) continue;
            if (!strcmp(var, "VERSION")) continue;
            
            fprintf(stdout, "%s: %s\n", vcard2rec_var(var), val);
        }
        fprintf(stdout, "\n");
    }
    
    if (error) {
        fprintf(stderr, "vcard2rec: error: %s\n", error);
        return 1;
    } else {
        return 0;
    }
}
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
