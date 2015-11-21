/*
 *  ofAppSDLWindow.cpp
 *  ofxSDL
 *
 *  Created by Lee Byron on 1/29/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "ofxSDLAppWindow.h"
#include "ofMain.h"
#include "ofxSDLEvents.h"
#include "ofxSDLApp.h"
#include <map>

#ifdef _MSC_VER
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#endif

void ofGLReadyCallback();

static std::map<SDL_Keycode, uint32_t> sdl_ofx_keymap;
void init_keymap()
{
//    sdl_ofx_keymap[] = OF_KEY_CONTROL;
//    sdl_ofx_keymap[] = OF_KEY_SHIFT;
//    sdl_ofx_keymap[] = OF_KEY_COMMAND;
    sdl_ofx_keymap[SDL_SCANCODE_ESCAPE] = OF_KEY_ESC;
    sdl_ofx_keymap[SDL_SCANCODE_LEFT] = OF_KEY_LEFT;
    sdl_ofx_keymap[SDL_SCANCODE_RIGHT] = OF_KEY_RIGHT;
    sdl_ofx_keymap[SDL_SCANCODE_UP] = OF_KEY_UP;
    sdl_ofx_keymap[SDL_SCANCODE_DOWN] = OF_KEY_DOWN;
    sdl_ofx_keymap[SDL_SCANCODE_PAGEUP] = OF_KEY_PAGE_UP;
    sdl_ofx_keymap[SDL_SCANCODE_PAGEDOWN] = OF_KEY_PAGE_DOWN;
    sdl_ofx_keymap[SDL_SCANCODE_HOME] = OF_KEY_HOME;
    sdl_ofx_keymap[SDL_SCANCODE_END] = OF_KEY_END;
    sdl_ofx_keymap[SDL_SCANCODE_INSERT] = OF_KEY_INSERT;
    sdl_ofx_keymap[SDL_SCANCODE_LSHIFT] = OF_KEY_LEFT_SHIFT;
    sdl_ofx_keymap[SDL_SCANCODE_LCTRL] = OF_KEY_LEFT_CONTROL;
    sdl_ofx_keymap[SDL_SCANCODE_LALT] = OF_KEY_LEFT_ALT;
    sdl_ofx_keymap[SDL_SCANCODE_LGUI] = OF_KEY_LEFT_SUPER;
    sdl_ofx_keymap[SDL_SCANCODE_RSHIFT] = OF_KEY_RIGHT_SHIFT;
    sdl_ofx_keymap[SDL_SCANCODE_RCTRL] = OF_KEY_RIGHT_CONTROL;
    sdl_ofx_keymap[SDL_SCANCODE_RALT] = OF_KEY_RIGHT_ALT;
    sdl_ofx_keymap[SDL_SCANCODE_RGUI] = OF_KEY_RIGHT_SUPER;
    sdl_ofx_keymap[SDL_SCANCODE_BACKSPACE] = OF_KEY_BACKSPACE;
    sdl_ofx_keymap[SDL_SCANCODE_DELETE] = OF_KEY_DEL;
    sdl_ofx_keymap[SDL_SCANCODE_RETURN] = OF_KEY_RETURN;
    sdl_ofx_keymap[SDL_SCANCODE_TAB] = OF_KEY_TAB;
    sdl_ofx_keymap[SDL_SCANCODE_F1] = OF_KEY_F1;
    sdl_ofx_keymap[SDL_SCANCODE_F2] = OF_KEY_F2;
    sdl_ofx_keymap[SDL_SCANCODE_F3] = OF_KEY_F3;
    sdl_ofx_keymap[SDL_SCANCODE_F4] = OF_KEY_F4;
    sdl_ofx_keymap[SDL_SCANCODE_F5] = OF_KEY_F5;
    sdl_ofx_keymap[SDL_SCANCODE_F6] = OF_KEY_F6;
    sdl_ofx_keymap[SDL_SCANCODE_F7] = OF_KEY_F7;
    sdl_ofx_keymap[SDL_SCANCODE_F8] = OF_KEY_F8;
    sdl_ofx_keymap[SDL_SCANCODE_F9] = OF_KEY_F9;
    sdl_ofx_keymap[SDL_SCANCODE_F10] = OF_KEY_F10;
    sdl_ofx_keymap[SDL_SCANCODE_F11] = OF_KEY_F11;
    sdl_ofx_keymap[SDL_SCANCODE_F12] = OF_KEY_F12;
    
    sdl_ofx_keymap[SDL_SCANCODE_A] = 'A';
    sdl_ofx_keymap[SDL_SCANCODE_B] = 'B';
    sdl_ofx_keymap[SDL_SCANCODE_C] = 'C';
    sdl_ofx_keymap[SDL_SCANCODE_D] = 'D';
    sdl_ofx_keymap[SDL_SCANCODE_E] = 'E';
    sdl_ofx_keymap[SDL_SCANCODE_F] = 'F';
    sdl_ofx_keymap[SDL_SCANCODE_G] = 'G';
    sdl_ofx_keymap[SDL_SCANCODE_H] = 'H';
    sdl_ofx_keymap[SDL_SCANCODE_I] = 'I';
    sdl_ofx_keymap[SDL_SCANCODE_J] = 'J';
    sdl_ofx_keymap[SDL_SCANCODE_K] = 'K';
    sdl_ofx_keymap[SDL_SCANCODE_L] = 'L';
    sdl_ofx_keymap[SDL_SCANCODE_M] = 'M';
    sdl_ofx_keymap[SDL_SCANCODE_N] = 'N';
    sdl_ofx_keymap[SDL_SCANCODE_O] = 'O';
    sdl_ofx_keymap[SDL_SCANCODE_P] = 'P';
    sdl_ofx_keymap[SDL_SCANCODE_Q] = 'Q';
    sdl_ofx_keymap[SDL_SCANCODE_R] = 'R';
    sdl_ofx_keymap[SDL_SCANCODE_S] = 'S';
    sdl_ofx_keymap[SDL_SCANCODE_T] = 'T';
    sdl_ofx_keymap[SDL_SCANCODE_U] = 'U';
    sdl_ofx_keymap[SDL_SCANCODE_V] = 'V';
    sdl_ofx_keymap[SDL_SCANCODE_W] = 'W';
    sdl_ofx_keymap[SDL_SCANCODE_X] = 'X';
    sdl_ofx_keymap[SDL_SCANCODE_Y] = 'Y';
    sdl_ofx_keymap[SDL_SCANCODE_Z] = 'Z';

    sdl_ofx_keymap[SDL_SCANCODE_0] = '0';
    sdl_ofx_keymap[SDL_SCANCODE_1] = '1';
    sdl_ofx_keymap[SDL_SCANCODE_2] = '2';
    sdl_ofx_keymap[SDL_SCANCODE_3] = '3';
    sdl_ofx_keymap[SDL_SCANCODE_4] = '4';
    sdl_ofx_keymap[SDL_SCANCODE_5] = '5';
    sdl_ofx_keymap[SDL_SCANCODE_6] = '6';
    sdl_ofx_keymap[SDL_SCANCODE_7] = '7';
    sdl_ofx_keymap[SDL_SCANCODE_8] = '8';
    sdl_ofx_keymap[SDL_SCANCODE_9] = '9';

    sdl_ofx_keymap[SDL_SCANCODE_SPACE] = ' ';
    sdl_ofx_keymap[SDL_SCANCODE_MINUS] = '-';
    sdl_ofx_keymap[SDL_SCANCODE_EQUALS] = '=';
    sdl_ofx_keymap[SDL_SCANCODE_LEFTBRACKET] = '[';
    sdl_ofx_keymap[SDL_SCANCODE_RIGHTBRACKET] = ']';
    sdl_ofx_keymap[SDL_SCANCODE_BACKSLASH] = '\\';
    
    sdl_ofx_keymap[SDL_SCANCODE_NONUSHASH] = '\\';
    sdl_ofx_keymap[SDL_SCANCODE_SEMICOLON] = ';';
    sdl_ofx_keymap[SDL_SCANCODE_APOSTROPHE] = '\'';
    sdl_ofx_keymap[SDL_SCANCODE_GRAVE] = '`';
    
    sdl_ofx_keymap[SDL_SCANCODE_COMMA] = ',';
    sdl_ofx_keymap[SDL_SCANCODE_PERIOD] = '.';
    sdl_ofx_keymap[SDL_SCANCODE_SLASH] = '/';

//    sdl_ofx_keymap[SDL_SCANCODE_CAPSLOCK] = ;
//    sdl_ofx_keymap[SDL_SCANCODE_PRINTSCREEN] = ;
//    sdl_ofx_keymap[SDL_SCANCODE_SCROLLLOCK] = ;
//    sdl_ofx_keymap[SDL_SCANCODE_PAUSE] = ;
//    sdl_ofx_keymap[SDL_SCANCODE_NUMLOCKCLEAR] = ;
//    sdl_ofx_keymap[SDL_SCANCODE_LANG3] = ;  /**< Katakana */
//    sdl_ofx_keymap[SDL_SCANCODE_LANG4] = ;  /**< Hiragana */
//    sdl_ofx_keymap[SDL_SCANCODE_LANG5] = ;  /**< Zenkaku/Hankaku */

//    sdl_ofx_keymap[] = ;
    
#if 0
#define OF_KEY_MODIFIER 	0x0100
#define OF_KEY_RETURN		13
#define OF_KEY_ESC			27
#define OF_KEY_TAB          9
#define OF_KEY_COMMAND      OF_KEY_SUPER
    
    // http://www.openframeworks.cc/forum/viewtopic.php?t=494
    // some issues with keys across platforms:
    
#ifdef TARGET_OSX
#define OF_KEY_BACKSPACE	127
#define OF_KEY_DEL			8
#else
#define OF_KEY_BACKSPACE	8
#define OF_KEY_DEL			127
#endif
    
    // zach - there are more of these keys, we can add them here...
    // these are keys that are not coming through "special keys"
    // via glut, but just other keys on your keyboard like
    
#define OF_KEY_F1			(1 | OF_KEY_MODIFIER)
#define OF_KEY_F2			(2 | OF_KEY_MODIFIER)
#define OF_KEY_F3			(3 | OF_KEY_MODIFIER)
#define OF_KEY_F4			(4 | OF_KEY_MODIFIER)
#define OF_KEY_F5			(5 | OF_KEY_MODIFIER)
#define OF_KEY_F6			(6 | OF_KEY_MODIFIER)
#define OF_KEY_F7			(7 | OF_KEY_MODIFIER)
#define OF_KEY_F8			(8 | OF_KEY_MODIFIER)
#define OF_KEY_F9			(9 | OF_KEY_MODIFIER)
#define OF_KEY_F10			(10 | OF_KEY_MODIFIER)
#define OF_KEY_F11			(11 | OF_KEY_MODIFIER)
#define OF_KEY_F12			(12 | OF_KEY_MODIFIER)
#define OF_KEY_LEFT			(100 | OF_KEY_MODIFIER)
#define OF_KEY_UP			(101 | OF_KEY_MODIFIER)
#define OF_KEY_RIGHT		(102 | OF_KEY_MODIFIER)
#define OF_KEY_DOWN			(103 | OF_KEY_MODIFIER)
#define OF_KEY_PAGE_UP		(104 | OF_KEY_MODIFIER)
#define OF_KEY_PAGE_DOWN	(105 | OF_KEY_MODIFIER)
#define OF_KEY_HOME			(106 | OF_KEY_MODIFIER)
#define OF_KEY_END			(107 | OF_KEY_MODIFIER)
#define OF_KEY_INSERT		(108 | OF_KEY_MODIFIER)
#define OF_KEY_CONTROL		(0x200 | OF_KEY_MODIFIER)
#define OF_KEY_ALT			(0x400 | OF_KEY_MODIFIER)
#define OF_KEY_SHIFT		(0x800 | OF_KEY_MODIFIER)
#define OF_KEY_SUPER		(0x1000 | OF_KEY_MODIFIER)
#define OF_KEY_LEFT_SHIFT	(0x1 | OF_KEY_SHIFT)
#define OF_KEY_RIGHT_SHIFT	(0x2 | OF_KEY_SHIFT)
#define OF_KEY_LEFT_CONTROL	(0x1 | OF_KEY_CONTROL)
#define OF_KEY_RIGHT_CONTROL (0x2 | OF_KEY_CONTROL)
#define OF_KEY_LEFT_ALT		(0x1 | OF_KEY_ALT)
#define OF_KEY_RIGHT_ALT	(0x2 | OF_KEY_ALT)
#define OF_KEY_LEFT_SUPER	(0x1 | OF_KEY_SUPER)
#define OF_KEY_RIGHT_SUPER	(0x2 | OF_KEY_SUPER)
#define OF_KEY_LEFT_COMMAND OF_KEY_LEFT_SUPER
#define OF_KEY_RIGHT_COMMAND OF_KEY_RIGHT_SUPER
#endif
    
#if 0
    SDL_SCANCODE_UNKNOWN = 0,
    
    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */
    
    SDL_SCANCODE_A = 4,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_E = 8,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_I = 12,
    SDL_SCANCODE_J = 13,
    SDL_SCANCODE_K = 14,
    SDL_SCANCODE_L = 15,
    SDL_SCANCODE_M = 16,
    SDL_SCANCODE_N = 17,
    SDL_SCANCODE_O = 18,
    SDL_SCANCODE_P = 19,
    SDL_SCANCODE_Q = 20,
    SDL_SCANCODE_R = 21,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_T = 23,
    SDL_SCANCODE_U = 24,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_X = 27,
    SDL_SCANCODE_Y = 28,
    SDL_SCANCODE_Z = 29,
    
    SDL_SCANCODE_1 = 30,
    SDL_SCANCODE_2 = 31,
    SDL_SCANCODE_3 = 32,
    SDL_SCANCODE_4 = 33,
    SDL_SCANCODE_5 = 34,
    SDL_SCANCODE_6 = 35,
    SDL_SCANCODE_7 = 36,
    SDL_SCANCODE_8 = 37,
    SDL_SCANCODE_9 = 38,
    SDL_SCANCODE_0 = 39,
    
    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,
    
    SDL_SCANCODE_MINUS = 45,
    SDL_SCANCODE_EQUALS = 46,
    SDL_SCANCODE_LEFTBRACKET = 47,
    SDL_SCANCODE_RIGHTBRACKET = 48,
    SDL_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    SDL_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate SDL_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    SDL_SCANCODE_SEMICOLON = 51,
    SDL_SCANCODE_APOSTROPHE = 52,
    SDL_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    SDL_SCANCODE_COMMA = 54,
    SDL_SCANCODE_PERIOD = 55,
    SDL_SCANCODE_SLASH = 56,
    
    SDL_SCANCODE_CAPSLOCK = 57,
    
    SDL_SCANCODE_F1 = 58,
    SDL_SCANCODE_F2 = 59,
    SDL_SCANCODE_F3 = 60,
    SDL_SCANCODE_F4 = 61,
    SDL_SCANCODE_F5 = 62,
    SDL_SCANCODE_F6 = 63,
    SDL_SCANCODE_F7 = 64,
    SDL_SCANCODE_F8 = 65,
    SDL_SCANCODE_F9 = 66,
    SDL_SCANCODE_F10 = 67,
    SDL_SCANCODE_F11 = 68,
    SDL_SCANCODE_F12 = 69,
    
    SDL_SCANCODE_PRINTSCREEN = 70,
    SDL_SCANCODE_SCROLLLOCK = 71,
    SDL_SCANCODE_PAUSE = 72,
    SDL_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                               does send code 73, not 117) */
    SDL_SCANCODE_HOME = 74,
    SDL_SCANCODE_PAGEUP = 75,
    SDL_SCANCODE_DELETE = 76,
    SDL_SCANCODE_END = 77,
    SDL_SCANCODE_PAGEDOWN = 78,
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_UP = 82,
    
    SDL_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    SDL_SCANCODE_KP_DIVIDE = 84,
    SDL_SCANCODE_KP_MULTIPLY = 85,
    SDL_SCANCODE_KP_MINUS = 86,
    SDL_SCANCODE_KP_PLUS = 87,
    SDL_SCANCODE_KP_ENTER = 88,
    SDL_SCANCODE_KP_1 = 89,
    SDL_SCANCODE_KP_2 = 90,
    SDL_SCANCODE_KP_3 = 91,
    SDL_SCANCODE_KP_4 = 92,
    SDL_SCANCODE_KP_5 = 93,
    SDL_SCANCODE_KP_6 = 94,
    SDL_SCANCODE_KP_7 = 95,
    SDL_SCANCODE_KP_8 = 96,
    SDL_SCANCODE_KP_9 = 97,
    SDL_SCANCODE_KP_0 = 98,
    SDL_SCANCODE_KP_PERIOD = 99,
    
    SDL_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    SDL_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    SDL_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    SDL_SCANCODE_KP_EQUALS = 103,
    SDL_SCANCODE_F13 = 104,
    SDL_SCANCODE_F14 = 105,
    SDL_SCANCODE_F15 = 106,
    SDL_SCANCODE_F16 = 107,
    SDL_SCANCODE_F17 = 108,
    SDL_SCANCODE_F18 = 109,
    SDL_SCANCODE_F19 = 110,
    SDL_SCANCODE_F20 = 111,
    SDL_SCANCODE_F21 = 112,
    SDL_SCANCODE_F22 = 113,
    SDL_SCANCODE_F23 = 114,
    SDL_SCANCODE_F24 = 115,
    SDL_SCANCODE_EXECUTE = 116,
    SDL_SCANCODE_HELP = 117,
    SDL_SCANCODE_MENU = 118,
    SDL_SCANCODE_SELECT = 119,
    SDL_SCANCODE_STOP = 120,
    SDL_SCANCODE_AGAIN = 121,   /**< redo */
    SDL_SCANCODE_UNDO = 122,
    SDL_SCANCODE_CUT = 123,
    SDL_SCANCODE_COPY = 124,
    SDL_SCANCODE_PASTE = 125,
    SDL_SCANCODE_FIND = 126,
    SDL_SCANCODE_MUTE = 127,
    SDL_SCANCODE_VOLUMEUP = 128,
    SDL_SCANCODE_VOLUMEDOWN = 129,
    /* not sure whether there's a reason to enable these */
    /*     SDL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
    /*     SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
    /*     SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    SDL_SCANCODE_KP_COMMA = 133,
    SDL_SCANCODE_KP_EQUALSAS400 = 134,
    
    SDL_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                        footnotes in USB doc */
    SDL_SCANCODE_INTERNATIONAL2 = 136,
    SDL_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    SDL_SCANCODE_INTERNATIONAL4 = 138,
    SDL_SCANCODE_INTERNATIONAL5 = 139,
    SDL_SCANCODE_INTERNATIONAL6 = 140,
    SDL_SCANCODE_INTERNATIONAL7 = 141,
    SDL_SCANCODE_INTERNATIONAL8 = 142,
    SDL_SCANCODE_INTERNATIONAL9 = 143,
    SDL_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    SDL_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    SDL_SCANCODE_LANG3 = 146, /**< Katakana */
    SDL_SCANCODE_LANG4 = 147, /**< Hiragana */
    SDL_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    SDL_SCANCODE_LANG6 = 149, /**< reserved */
    SDL_SCANCODE_LANG7 = 150, /**< reserved */
    SDL_SCANCODE_LANG8 = 151, /**< reserved */
    SDL_SCANCODE_LANG9 = 152, /**< reserved */
    
    SDL_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
    SDL_SCANCODE_SYSREQ = 154,
    SDL_SCANCODE_CANCEL = 155,
    SDL_SCANCODE_CLEAR = 156,
    SDL_SCANCODE_PRIOR = 157,
    SDL_SCANCODE_RETURN2 = 158,
    SDL_SCANCODE_SEPARATOR = 159,
    SDL_SCANCODE_OUT = 160,
    SDL_SCANCODE_OPER = 161,
    SDL_SCANCODE_CLEARAGAIN = 162,
    SDL_SCANCODE_CRSEL = 163,
    SDL_SCANCODE_EXSEL = 164,
    
    SDL_SCANCODE_KP_00 = 176,
    SDL_SCANCODE_KP_000 = 177,
    SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
    SDL_SCANCODE_DECIMALSEPARATOR = 179,
    SDL_SCANCODE_CURRENCYUNIT = 180,
    SDL_SCANCODE_CURRENCYSUBUNIT = 181,
    SDL_SCANCODE_KP_LEFTPAREN = 182,
    SDL_SCANCODE_KP_RIGHTPAREN = 183,
    SDL_SCANCODE_KP_LEFTBRACE = 184,
    SDL_SCANCODE_KP_RIGHTBRACE = 185,
    SDL_SCANCODE_KP_TAB = 186,
    SDL_SCANCODE_KP_BACKSPACE = 187,
    SDL_SCANCODE_KP_A = 188,
    SDL_SCANCODE_KP_B = 189,
    SDL_SCANCODE_KP_C = 190,
    SDL_SCANCODE_KP_D = 191,
    SDL_SCANCODE_KP_E = 192,
    SDL_SCANCODE_KP_F = 193,
    SDL_SCANCODE_KP_XOR = 194,
    SDL_SCANCODE_KP_POWER = 195,
    SDL_SCANCODE_KP_PERCENT = 196,
    SDL_SCANCODE_KP_LESS = 197,
    SDL_SCANCODE_KP_GREATER = 198,
    SDL_SCANCODE_KP_AMPERSAND = 199,
    SDL_SCANCODE_KP_DBLAMPERSAND = 200,
    SDL_SCANCODE_KP_VERTICALBAR = 201,
    SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
    SDL_SCANCODE_KP_COLON = 203,
    SDL_SCANCODE_KP_HASH = 204,
    SDL_SCANCODE_KP_SPACE = 205,
    SDL_SCANCODE_KP_AT = 206,
    SDL_SCANCODE_KP_EXCLAM = 207,
    SDL_SCANCODE_KP_MEMSTORE = 208,
    SDL_SCANCODE_KP_MEMRECALL = 209,
    SDL_SCANCODE_KP_MEMCLEAR = 210,
    SDL_SCANCODE_KP_MEMADD = 211,
    SDL_SCANCODE_KP_MEMSUBTRACT = 212,
    SDL_SCANCODE_KP_MEMMULTIPLY = 213,
    SDL_SCANCODE_KP_MEMDIVIDE = 214,
    SDL_SCANCODE_KP_PLUSMINUS = 215,
    SDL_SCANCODE_KP_CLEAR = 216,
    SDL_SCANCODE_KP_CLEARENTRY = 217,
    SDL_SCANCODE_KP_BINARY = 218,
    SDL_SCANCODE_KP_OCTAL = 219,
    SDL_SCANCODE_KP_DECIMAL = 220,
    SDL_SCANCODE_KP_HEXADECIMAL = 221,
    
    SDL_SCANCODE_LCTRL = 224,
    SDL_SCANCODE_LSHIFT = 225,
    SDL_SCANCODE_LALT = 226, /**< alt, option */
    SDL_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    SDL_SCANCODE_RCTRL = 228,
    SDL_SCANCODE_RSHIFT = 229,
    SDL_SCANCODE_RALT = 230, /**< alt gr, option */
    SDL_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */
    
    SDL_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */
    
    /* @} *//* Usage page 0x07 */
    
    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */
    
    SDL_SCANCODE_AUDIONEXT = 258,
    SDL_SCANCODE_AUDIOPREV = 259,
    SDL_SCANCODE_AUDIOSTOP = 260,
    SDL_SCANCODE_AUDIOPLAY = 261,
    SDL_SCANCODE_AUDIOMUTE = 262,
    SDL_SCANCODE_MEDIASELECT = 263,
    SDL_SCANCODE_WWW = 264,
    SDL_SCANCODE_MAIL = 265,
    SDL_SCANCODE_CALCULATOR = 266,
    SDL_SCANCODE_COMPUTER = 267,
    SDL_SCANCODE_AC_SEARCH = 268,
    SDL_SCANCODE_AC_HOME = 269,
    SDL_SCANCODE_AC_BACK = 270,
    SDL_SCANCODE_AC_FORWARD = 271,
    SDL_SCANCODE_AC_STOP = 272,
    SDL_SCANCODE_AC_REFRESH = 273,
    SDL_SCANCODE_AC_BOOKMARKS = 274,
    
    /* @} *//* Usage page 0x0C */
    
    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */
    
    SDL_SCANCODE_BRIGHTNESSDOWN = 275,
    SDL_SCANCODE_BRIGHTNESSUP = 276,
    SDL_SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                       switch, video mode switch */
    SDL_SCANCODE_KBDILLUMTOGGLE = 278,
    SDL_SCANCODE_KBDILLUMDOWN = 279,
    SDL_SCANCODE_KBDILLUMUP = 280,
    SDL_SCANCODE_EJECT = 281,
    SDL_SCANCODE_SLEEP = 282,
    
    SDL_SCANCODE_APP1 = 283,
    SDL_SCANCODE_APP2 = 284,
    
    /* @} *//* Walther keys */
    
    /* Add any other keys here. */
    
    SDL_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                             for array bounds */

#endif
    
}

/* Print all information about a key event */
void PrintKeyInfo( SDL_KeyboardEvent *key ){
#if 0
	/* Is it a release or a press? */
	if( key->type == SDL_KEYUP )
		printf( "Release:- " );
	else
		printf( "Press:- " );
	
	/* Print the hardware scancode first */
	printf( "Scancode: 0x%02X", key->keysym.scancode );
	/* Print the name of the key */
	printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
	/* We want to print the unicode info, but we need to make */
	/* sure its a press event first (remember, release events */
	/* don't have unicode info                                */
	if( key->type == SDL_KEYDOWN ){
		/* If the Unicode value is less than 0x80 then the    */
		/* unicode value can be used to get a printable       */
		/* representation of the key, using (char)unicode.    */
		printf(", Unicode: " );
		if( key->keysym.unicode < 0x80 && key->keysym.unicode > 0 ){
			printf( "%c (0x%04X)", (char)key->keysym.unicode,
				   key->keysym.unicode );
		}
		else{
			printf( "? (0x%04X)", key->keysym.unicode );
		}
	}
	printf( "\n" );
	/* Print modifier info */
	PrintModifiers( key->keysym.mod );
#endif
}

/* Print modifier info */
void PrintModifiers( Uint32 mod ){
	printf( "Modifers: " );
	
	/* If there are none then say so and return */
	if( mod == KMOD_NONE ){
		printf( "None\n" );
		return;
	}
	
	/* Check for the presence of each SDLMod value */
	/* This looks messy, but there really isn't    */
	/* a clearer way.                              */
	if( mod & KMOD_NUM ) printf( "NUMLOCK " );
	if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
	if( mod & KMOD_LCTRL ) printf( "LCTRL " );
	if( mod & KMOD_RCTRL ) printf( "RCTRL " );
	if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
	if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
	if( mod & KMOD_RALT ) printf( "RALT " );
	if( mod & KMOD_LALT ) printf( "LALT " );
	if( mod & KMOD_CTRL ) printf( "CTRL " );
	if( mod & KMOD_SHIFT ) printf( "SHIFT " );
	if( mod & KMOD_ALT ) printf( "ALT " );
	printf( "\n" );
}





// maintain static reference to the screen
///static SDL_Surface* gScreen;
static SDL_Window* gScreen;
static SDL_GLContext context;
static SDL_Event    event;
static ofxSDLApp*   ofAppPtr;
static int          nFrameCount;
static int          nFramesSinceWindowResized;
static int          windowW;
static int          windowH;
static int          millisForFrame;
static bool         bFrameRateSet;

static int          diffMillis;
static int          waitMillis;
static int          prevMillis;

static float        timeNow;
static float        timeThen;
static float        frameRate;
static double       fps;
static double       lastFrameTime;

static int          buttonInUse;

static SDL_Joystick* joys[8]; // got more than 8 controllers? you mad man.
static int          numJoys;

static bool         bEnableSetupScreen;


//============================================================
// VARIABLE INITIALIZATION

//----------------------------------------------------------
ofxSDLAppWindow::ofxSDLAppWindow() {
	bEnableSetupScreen = true;
	
	windowW         = 0;
	windowH         = 0;
	
	timeNow         = 0;
	timeThen        = 0;
	fps             = 60.0; // give a realistic starting value - win32 issues
	frameRate       = 60.0;
	
	/*
	 windowMode			= OF_WINDOW;
	 bNewScreenMode	= true;
	 nFramesForFPS		= 0;
	 */
	nFramesSinceWindowResized = 0;
	nFrameCount			= 0;
	
	buttonInUse			= 0;
	
	bFrameRateSet		= false;
	millisForFrame	= 0;
	
	prevMillis			= 0;
	diffMillis			= 0;
	waitMillis      = 0;
	
	/*
	 requestedWidth	= 0;
	 requestedHeight	= 0;
	 nonFullScreenX	= -1;
	 nonFullScreenY	= -1;
	 */
	lastFrameTime		= 0.0;
	
	numJoys         = 0;
	
	// for text input
	cursor = 0;
}


//============================================================
// INITIALIZATION AND RUNTIME

//------------------------------------------------------------
void ofxSDLAppWindow::setupOpenGL(int w, int h, int screenMode) {
	// init keymap
    init_keymap();
    
	// Init SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	// Setup attributes we want for the OpenGL context
	int value;
	
	// Don't set color bit sizes (SDL_GL_RED_SIZE, etc)
	//    Mac OS X will always use 8-8-8-8 ARGB for 32-bit screens and
	//    5-5-5 RGB for 16-bit screens
/*
	// Request a 16-bit depth buffer (without this, there is no depth buffer)
	value = 16;
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, value);
	
	// Request double-buffered OpenGL
	//     The fact that windows are double-buffered on Mac OS X has no effect
	//     on OpenGL double buffering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	
	//GL_MULTISAMPLE_ARB
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
*/
	Uint32 flags = 0;

    flags = SDL_WINDOW_OPENGL;
//	flags |= SDL_INIT_JOYSTICK;
//	flags |= SDL_INIT_TIMER;
	if (screenMode != OF_WINDOW) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	
	// Create window
///	gScreen = SDL_SetVideoMode(w, h, 0, flags);
    gScreen = SDL_CreateWindow("MMM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
	if (gScreen == NULL) {
		fprintf(stderr, "Couldn't set %ix%i OpenGL video mode: %s\n", w, h, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
    
    // create OpenGL context
    context = SDL_GL_CreateContext(gScreen);
    if (!context) return;
    
	windowW = w;
	windowH = h;
    
    ofGLReadyCallback();
}

//------------------------------------------------------------
void ofxSDLAppWindow::initializeWindow() {
	// we don't have to do anything here, since some crazy ass SDL magic
	// is happening in the SDLMain.mm file, which actually does the window
	// initialization and OSX setup details.
}

//------------------------------------------------------------
void ofxSDLAppWindow::runAppViaInfiniteLoop(ofBaseApp* appPtr) {
	static ofEventArgs voidEventArgs;
	
	// ------------------------------------------------------------
	// enable keyboarding
	
///	SDL_EnableUNICODE(1);
	
	// ------------------------------------------------------------
	// connect controllers
/*
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	
	numJoys = SDL_NumJoysticks();
	for (int j = 0; j < numJoys; j++) {
		joys[j] = SDL_JoystickOpen(j);
	}
*/
	
	// ------------------------------------------------------------
	// setup application
	
	ofAppPtr = (ofxSDLApp*) appPtr;
	
#ifdef OF_USING_POCO
	ofNotifyEvent(ofEvents().setup, voidEventArgs);
	ofNotifyEvent(ofEvents().update, voidEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->setup();
        ofAppPtr->update();
    }
#endif
	
	
	// ------------------------------------------------------------
	// loop forever and ever and ever and ever (and ever)
	
	while (true) {
		
		// ------------------------------------------------------------
		// check for events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_JOYAXISMOTION:
					this->joyMovedHandler(&event);
					break;
				case SDL_JOYBUTTONDOWN:
					this->joyDownHandler(&event);
					break;
				case SDL_JOYBUTTONUP:
					this->joyUpHandler(&event);
					break;
				case SDL_MOUSEMOTION:
                    this->mouseMoveHandler(&event);
					break;
				case SDL_MOUSEBUTTONDOWN:
					this->mouseDownHandler(&event);
					break;
				case SDL_MOUSEBUTTONUP:
					this->mouseUpHandler(&event);
					break;
				case SDL_KEYDOWN:
					this->keyDownHandler(&event);
					break;
				case SDL_KEYUP:
					this->keyUpHandler(&event);
					break;
				case SDL_TEXTINPUT:
					this->textInputHandler(&event);
					break;
				case SDL_TEXTEDITING:
					this->textEditHandler(&event);					
					break;					
				case SDL_QUIT:
					this->exitApp();
					break;
				default:
					break;
			}
		}
		
		
		// ------------------------------------------------------------
		// set viewport, clear the screen
/*
		int width, height;
		width  = ofGetWidth();
		height = ofGetHeight();
		height = height > 0 ? height : 1;
		glViewport(0, 0, width, height);
		
		float* bgPtr = ofBgColorPtr();
		bool bClearAuto = ofbClearBg();
		
#ifdef TARGET_WIN32
		// TODO: unsure if this is required for SDL, copied from GLUT.
		// to do non auto clear on PC for now - we do something like "single" buffering --
		// it's not that pretty but it work for the most part
		if (bClearAuto == false) {
			glDrawBuffer(GL_FRONT);
		}
#endif
		
		if (bClearAuto == true || nFrameCount < 3) {
			glClearColor(bgPtr[0], bgPtr[1], bgPtr[2], bgPtr[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
*/
		
		// ------------------------------------------------------------
		// do frame drawing
		
		if (bEnableSetupScreen) {
//			ofSetupScreen();
		}
		
#ifdef OF_USING_POCO
		ofNotifyEvent(ofEvents().draw, voidEventArgs);
#else
		if (ofAppPtr) {
			ofAppPtr->draw();
		}
#endif
		
		
		// ------------------------------------------------------------
		// finish viewport
		
#ifdef TARGET_WIN32
		{
			// on a PC resizing a window with this method of accumulation (essentially single buffering)
			// is BAD, so we clear on resize events.
			if (nFramesSinceWindowResized < 3) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			} else {
				if (nFrameCount < 3 || nFramesSinceWindowResized < 3) {
					SDL_GL_SwapWindow(gScreen);
				} else {
					SDL_GL_SwapWindow(gScreen);
//					glFlush();
				}
			}
		}
#else
/*
		if (bClearAuto == false) {
			// in accum mode resizing a window is BAD, so we clear on resize events.
			if (nFramesSinceWindowResized < 3) {
				glClearColor(bgPtr[0], bgPtr[1], bgPtr[2], bgPtr[3]);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}
 */
///		SDL_GL_SwapBuffers();
        SDL_GL_SwapWindow(gScreen);
#endif
        
		
		// ------------------------------------------------------------
		// wait a moment plz! keep our framerate sane
		
		timeNow = ofGetElapsedTimef();
		lastFrameTime = timeNow - timeThen;
		if (lastFrameTime > 0.00001) {
			fps        = 1.0 / lastFrameTime;
			frameRate *= 0.9f;
			frameRate += 0.1f * fps;
		}
		timeThen = timeNow;
		
		// --------------
		
		if (nFrameCount != 0 && bFrameRateSet == true) {
			diffMillis = SDL_GetTicks() - prevMillis;
			if (diffMillis > millisForFrame) {
				; // we do nothing, we are already slower than target frame
			} else {
				waitMillis = millisForFrame - diffMillis;
				SDL_Delay(waitMillis);
			}
		}
		prevMillis = SDL_GetTicks(); // you have to measure here
		
		
		// ------------------------------------------------------------
		// increment the world
		
		nFrameCount++;
		nFramesSinceWindowResized++; // TODO: do we actually use this?
		
		
		// ------------------------------------------------------------
		// update the application
			
#ifdef OF_USING_POCO
		ofNotifyEvent(ofEvents().update, voidEventArgs);
#else
        if (ofAppPtr) {
            ofAppPtr->update();
        }
#endif
		
	}
}

//------------------------------------------------------------
void ofxSDLAppWindow::exitApp() {
	ofLog(OF_LOG_VERBOSE, "SDL OF app is being terminated!");
	
	// clean up SDL
	for (int j = 0; j < numJoys; j++) {
//		if (joys[j] && SDL_JoystickOpened(j)) {
        if (joys[j] && SDL_JoystickOpen(j)) {
			SDL_JoystickClose(joys[j]);
			joys[j] = NULL;
		}
	}
	SDL_Quit();
	
	OF_EXIT_APP(0);
}



//============================================================
// CURSORS

//------------------------------------------------------------
void ofxSDLAppWindow::hideCursor() {
	SDL_ShowCursor(SDL_DISABLE);
}

//------------------------------------------------------------
void ofxSDLAppWindow::showCursor() {
	SDL_ShowCursor(SDL_ENABLE);
}



//============================================================
// DISPLAY SIZING

//------------------------------------------------------------
ofPoint ofxSDLAppWindow::getWindowSize() {
	return ofPoint(windowW, windowH, 0);
}

//------------------------------------------------------------
ofPoint ofxSDLAppWindow::getScreenSize() {
    int w=0, h=0;
    SDL_GetWindowSize(gScreen, &w, &h);
    return ofPoint(w, h, 0);
///	const SDL_VideoInfo* desktop = SDL_GetVideoInfo();
///	return ofPoint(desktop->current_w, desktop->current_h, 0);
}



//============================================================
// FRAME RATE

//------------------------------------------------------------
float ofxSDLAppWindow::getFrameRate() {
	return frameRate;
}

//------------------------------------------------------------
double ofxSDLAppWindow::getLastFrameTime() {
	return lastFrameTime;
}

//------------------------------------------------------------
int ofxSDLAppWindow::getFrameNum() {
	return nFrameCount;
}

//------------------------------------------------------------
void ofxSDLAppWindow::setFrameRate(float targetRate) {
	// given this FPS, what is the amount of millis per frame
	// that should elapse?
	
	if (targetRate == 0) {
		bFrameRateSet = false;
		return;
	}
	
	frameRate             = targetRate;
	bFrameRateSet         = true;
	float durationOfFrame = 1.0f / frameRate;
	millisForFrame        = (int)(1000.0f * durationOfFrame);
}



//============================================================
// SETUP SCREEN

//------------------------------------------------------------
void ofxSDLAppWindow::enableSetupScreen() {
	bEnableSetupScreen = true;
}

//------------------------------------------------------------
void ofxSDLAppWindow::disableSetupScreen() {
	bEnableSetupScreen = false;
}



//============================================================
// JOYSTICK INFORMATION

//------------------------------------------------------------
int ofxSDLAppWindow::getControllerCount() {
	return numJoys;
}

//------------------------------------------------------------
string ofxSDLAppWindow::getControllerName(int num) {
	if (num >= numJoys || !joys[num]) {
		return "";
	}
	SDL_Joystick *joystick = SDL_JoystickOpen(num);
    string joyName(SDL_JoystickName(joystick));
///	string joyName(SDL_JoystickName(num));
	return joyName;
}

//------------------------------------------------------------
int ofxSDLAppWindow::getControllerNumButtons(int num) {
	if (num >= numJoys || !joys[num]) {
		return 0;
	}
	
	return SDL_JoystickNumButtons(joys[num]);
}

//------------------------------------------------------------
int ofxSDLAppWindow::getControllerNumAxes(int num) {
	if (num >= numJoys || !joys[num]) {
		return 0;
	}
	
	return SDL_JoystickNumAxes(joys[num]);
}



//============================================================
// EVENT HANDLERS

//------------------------------------------------------------
void ofxSDLAppWindow::joyDownHandler(SDL_Event* evt) {
	static ofxSDLJoyButtonEventArgs joyEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
#ifdef OF_USING_POCO
	joyEventArgs.device = evt->jbutton.which;
	joyEventArgs.button = evt->jbutton.button;
	// TODO why does this break?!
	//ofNotifyEvent(ofxSDLEvents.joyButtonReleased, joyEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->joyButtonPressed(evt->jbutton.which,
                                   evt->jbutton.button);
    }
#endif
}

//------------------------------------------------------------
void ofxSDLAppWindow::joyUpHandler(SDL_Event* evt) {
	static ofxSDLJoyButtonEventArgs joyEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
	if (ofAppPtr) {
		ofAppPtr->joyButtonReleased(evt->jbutton.which,
									evt->jbutton.button);
	}
	
#ifdef OF_USING_POCO
	joyEventArgs.device = evt->jbutton.which;
	joyEventArgs.button = evt->jbutton.button;
	//ofNotifyEvent(ofxSDLEvents.joyButtonReleased, joyEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->joyButtonReleased(evt->jbutton.which,
                                    evt->jbutton.button);
    }
#endif
}

//------------------------------------------------------------
void ofxSDLAppWindow::joyMovedHandler(SDL_Event* evt) {
	static ofxSDLJoyAxisEventArgs joyAxisEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
	float position = (float)evt->jaxis.value / 32768.0;
	
#ifdef OF_USING_POCO
	joyAxisEventArgs.device = evt->jaxis.which;
	joyAxisEventArgs.axis = evt->jaxis.axis;
	joyAxisEventArgs.position = position;
	//ofNotifyEvent(ofxSDLEvents.joyAxisMoved, joyEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->joyAxisMoved(evt->jaxis.which,
                               evt->jaxis.axis,
                               position);
    }
#endif
}

//------------------------------------------------------------
void ofxSDLAppWindow::mouseDownHandler(SDL_Event* evt) {
	static ofMouseEventArgs mouseEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
	int button = evt->button.button;
	if (button == SDL_BUTTON_RIGHT) button = OF_MOUSE_BUTTON_RIGHT;
	if (button == SDL_BUTTON_LEFT) button = OF_MOUSE_BUTTON_LEFT;
	if (button == SDL_BUTTON_MIDDLE) button = OF_MOUSE_BUTTON_MIDDLE;

#ifdef OF_USING_POCO
	mouseEventArgs.x = evt->button.x;
	mouseEventArgs.y = evt->button.y;
	mouseEventArgs.button = button;
	ofNotifyEvent(ofEvents().mousePressed, mouseEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->mouseX = evt->button.x;
        ofAppPtr->mouseY = evt->button.y;
		ofAppPtr->mousePressed(evt->button.x,
								evt->button.y,
								button); // are button consts the same as glut?
        // TODO: break out mouseScroll as a seperate action?
    }
#endif
	
	buttonInUse = evt->button.button;
}

//------------------------------------------------------------
void ofxSDLAppWindow::mouseUpHandler(SDL_Event* evt) {
	static ofMouseEventArgs mouseEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
	int button = evt->button.button;
	if (button == SDL_BUTTON_RIGHT) button = OF_MOUSE_BUTTON_RIGHT;
	if (button == SDL_BUTTON_LEFT) button = OF_MOUSE_BUTTON_LEFT;
	if (button == SDL_BUTTON_MIDDLE) button = OF_MOUSE_BUTTON_MIDDLE;

#ifdef OF_USING_POCO
	mouseEventArgs.x = evt->button.x;
	mouseEventArgs.y = evt->button.y;
	mouseEventArgs.button = button;//evt->button.button;
	ofNotifyEvent(ofEvents().mouseReleased, mouseEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->mouseX = evt->button.x;
        ofAppPtr->mouseY = evt->button.y;
        ofAppPtr->mouseReleased(evt->button.x,
                                evt->button.y,
								button); // are button consts the same as glut?
        // TODO: break out mouseScroll as a seperate action?
    }
#endif
	
	buttonInUse = 0;
}

//------------------------------------------------------------
void ofxSDLAppWindow::mouseMoveHandler(SDL_Event* evt) {
    static ofMouseEventArgs mouseEventArgs;
    
    if (nFrameCount == 0) {
        return;
    }
    
#ifdef OF_USING_POCO
    mouseEventArgs.x = evt->button.x;
    mouseEventArgs.y = evt->button.y;
    ofNotifyEvent(ofEvents().mouseMoved, mouseEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->mouseX = evt->button.x;
        ofAppPtr->mouseY = evt->button.y;
        ofAppPtr->mouseMoved(evt->button.x, evt->button.y);
    }
#endif
}

void ofxSDLAppWindow::keyDownHandler(SDL_Event* evt) {
	static ofKeyEventArgs keyEventArgs;
	
	// TODO: better handling of non chars and true unicode
	SDL_Keycode sym = evt->key.keysym.scancode;
///	char key = evt->key.keysym.unicode & 0x7F;
	
    std::map<SDL_Keycode, uint32_t>::iterator f = sdl_ofx_keymap.find(sym);
    if(f==sdl_ofx_keymap.end()){
        keyEventArgs.key = evt->key.keysym.sym;
    }else{
        keyEventArgs.key = sdl_ofx_keymap[sym];
    }
#ifdef OF_USING_POCO
	ofNotifyEvent(ofEvents().keyPressed, keyEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->keyPressed(keyEventArgs.key);
    }
#endif
		
	// --- quit sequences -----------------
	
//	if (keyEventArgs.key == SDLK_ESCAPE) {
//		exitApp();
//	}
	
#ifdef TARGET_OSX
///	if (sym == SDLK_q && evt->key.keysym.mod & KMOD_META) { // OSX quit command
//    if (keyEventArgs.key == SDLK_q && evt->key.keysym.mod & KMOD_ALT) { // OSX quit command
//		exitApp();
//	}
#endif
	
#ifdef TARGET_WIN32
	if (sym == SDLK_F4 && evt->key.keysym.mod & KMOD_ALT) { // Win quit command
		exitApp();
	}
#endif
	
}

void ofxSDLAppWindow::keyUpHandler(SDL_Event* evt) {
	static ofKeyEventArgs keyEventArgs;
	
	//PrintKeyInfo(&(evt->key));
	
	SDL_Keycode sym = evt->key.keysym.scancode;
///	char key = evt->key.keysym.unicode & 0x7F; // TODO: doesn't work
	
    std::map<SDL_Keycode, uint32_t>::iterator f = sdl_ofx_keymap.find(sym);
    if(f==sdl_ofx_keymap.end()){
        keyEventArgs.key = evt->key.keysym.sym;
    }else{
        keyEventArgs.key = sdl_ofx_keymap[sym];
    }
#ifdef OF_USING_POCO
	ofNotifyEvent(ofEvents().keyReleased, keyEventArgs);
#else
    if (ofAppPtr) {
        ofAppPtr->keyReleased(keyEventArgs.key);
    }
#endif
}

void ofxSDLAppWindow::textInputHandler(SDL_Event* evt) {
	
	if (SDL_strlen(evt->text.text) == 0 || evt->text.text[0] == '\n' || markedRect.w < 0)
		return;
    
    std::string t;
    ofAppPtr->imeChange("", 0);
    ofAppPtr->textInput(evt->text.text);
    fprintf(stderr, "input[%s]\n", evt->text.text);
	updateTextRect();
	
}

void ofxSDLAppWindow::textEditHandler(SDL_Event* evt) {

    if(evt->edit.length==0){
        ofAppPtr->imeChange(evt->edit.text, evt->edit.length);
        fprintf(stderr, "edit[%s] %d\n", evt->edit.text, evt->edit.length);
    }else{
        ofAppPtr->imeChange(evt->edit.text, evt->edit.start);
        fprintf(stderr, "edit[%s] %d\n", evt->edit.text, evt->edit.start);
    }
	updateTextRect();
}

int ofxSDLAppWindow::getWidth()
{
    return windowW;
}
int ofxSDLAppWindow::getHeight()
{
    return windowH;
}


void ofxSDLAppWindow::updateTextRect() {
	
	cout << markedText << endl;
	
}

char* ofxSDLAppWindow::utf8_advance(char *p, size_t distance) {
	
    size_t i = 0;
    for (; i < distance && p; ++i)
    {
        p = utf8_next(p);
    }
    return p;
}

char* ofxSDLAppWindow::utf8_next(char *p) {
	
    size_t len = utf8_length(*p);
    size_t i = 0;
    if (!len)
        return 0;
	
    for (; i < len; ++i)
    {
        ++p;
        if (!*p)
            return 0;
    }
    return p;
	
}

size_t ofxSDLAppWindow::utf8_length(unsigned char c) {
	
    c = (unsigned char)(0xff & c);
    if (c < 0x80)
        return 1;
    else if ((c >> 5) ==0x6)
        return 2;
    else if ((c >> 4) == 0xe)
        return 3;
    else if ((c >> 3) == 0x1e)
        return 4;
    else
        return 0;
	
}