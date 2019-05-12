# `timzon`

This tool lets you view IBM i `*TIMZON` objects from PASE. Eventually, the
intent is to let you convert these into [IANA zoneinfo][zoneinfo] files, either
by outputting source files suitable for `zic(8)` or binary `tzfile(5)` files.

This is also a demonstration of how to use the `_PGMCALL` system call available
to programs running in PASE, to call OPM APIs. The API for calling is much
simpler than the `_ILECALL` API, and one only needs to pass in an array of
pointers and resolve an object name. The only pitfall is conversion of EBCDIC
values to ASCII/UTF-8 suitable for use in PASE.

## Building

The source is plain C99. It will need GCC and the system libiconv. To build,
simply run `make`.

[zoneinfo]: https://www.iana.org/time-zones "IANA Time Zone Database"
