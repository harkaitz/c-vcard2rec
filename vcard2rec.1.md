# NAME

*vcard2rec* - Convert from vCard RFC-6350 to GNU Recutils

# SYNOPSIS

    vcard2rec < VCARD-FILE > REC-FILE

# DESCRIPTION

The *vcard2rec* utility reads a vCard RFC-6350 file from the
standard input and outputs a GNU Recutils file to the output.

All properties are lowercased and all ";-" are replaced by
"_" in property names.


# COLLABORATING

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**RFC6350(3)**
