# LK - My Ultimate C++ Support Library

## License

Licensed under GPL-3.0. Open to conversation; contact me
at [development@kortlepel.com](mailto:development@kortlepel.com) if you have commercial / proprietary / other needs that
are not GPL-3.0 compatible.

## What is LK?

It's a support library for C++, depending only on libc. While it does use libc everywhere, it does so in a sane way.
This means that all inputs are checked for `nullptr`, ensured to be in range, etc. This results in most simple behavior
being a simple but safe wrapper around libc.