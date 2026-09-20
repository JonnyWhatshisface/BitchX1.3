/*
 * cp437utf8.h: CP437 to UTF-8 conversion for terminals that do not
 * natively support the IBM PC character set (OEM-US / CP437).
 *
 * Modern terminals are UTF-8, so raw CP437 high bytes (0x80-0xFF) would
 * render as garbage.  When the terminal's locale says it does not speak
 * CP437, we translate the CP437 bytes to UTF-8 before they reach the
 * terminal, giving the same result as running the program under the
 * cp437(1) wrapper.
 */

#ifndef __cp437utf8_h
#define __cp437utf8_h

#define CP437_UTF8_MAX_LEN 3

/* Probe the terminal's character set and decide whether translation
 * via cp437utf8_convert() is needed.  Call once at startup. */
void cp437utf8_init(void);

/* Returns non-zero if the terminal natively supports CP437 and output
 * should be passed through unchanged. */
int cp437utf8_supported(void);

/* Translate the CP437 byte c into buf.
 *
 * Returns the number of bytes placed in buf (always >= 1).
 * Bytes below 0x80 and control characters are passed through unchanged.
 * The buffer must be able to hold CP437_UTF8_MAX_LEN + 1 bytes. */
int cp437utf8_convert(int c, unsigned char *buf);

#endif