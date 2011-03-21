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



/* Print all information about a key event */
void PrintKeyInfo( SDL_KeyboardEvent *key ){
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
	//PrintModifiers( key->keysym.mod );
}

/* Print modifier info */
void PrintModifiers( SDLMod mod ){
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
static SDL_Surface* gScreen;
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
	
	// Request a 16-bit depth buffer (without this, there is no depth buffer)
	value = 16;
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, value);
	
	// Request double-buffered OpenGL
	//     The fact that windows are double-buffered on Mac OS X has no effect
	//     on OpenGL double buffering.
	value = 1;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, value);
	
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	
	//GL_MULTISAMPLE_ARB
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	Uint32 flags = 0;
	
	flags = SDL_OPENGL;
	flags |= SDL_INIT_JOYSTICK;
	flags |= SDL_INIT_TIMER;
	if (screenMode != OF_WINDOW) {
		flags |= SDL_FULLSCREEN;
	}
	
	// Create window
	gScreen = SDL_SetVideoMode(w, h, 0, flags);
	if (gScreen == NULL) {
		fprintf(stderr, "Couldn't set %ix%i OpenGL video mode: %s\n", w, h, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	windowW = w;
	windowH = h;
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
	
	SDL_EnableUNICODE(1);
	
	// ------------------------------------------------------------
	// connect controllers
	
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	
	numJoys = SDL_NumJoysticks();
	for (int j = 0; j < numJoys; j++) {
		joys[j] = SDL_JoystickOpen(j);
	}
	
	
	// ------------------------------------------------------------
	// setup application
	
	ofAppPtr = (ofxSDLApp*) appPtr;
	
	if (ofAppPtr) {
		ofAppPtr->setup();
		ofAppPtr->update();
	}
	
#ifdef OF_USING_POCO
	ofNotifyEvent(ofEvents.setup, voidEventArgs);
	ofNotifyEvent(ofEvents.update, voidEventArgs);
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
					// TODO
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
		
		
		// ------------------------------------------------------------
		// do frame drawing
		
		if (bEnableSetupScreen) {
			ofSetupScreen();
		}
		
		if (ofAppPtr) {
			ofAppPtr->draw();
		}
		
#ifdef OF_USING_POCO
		ofNotifyEvent(ofEvents.draw, voidEventArgs);
#endif
		
		
		// ------------------------------------------------------------
		// finish viewport
		
#ifdef TARGET_WIN32
		if (bClearAuto == false) {
			// on a PC resizing a window with this method of accumulation (essentially single buffering)
			// is BAD, so we clear on resize events.
			if (nFramesSinceWindowResized < 3) {
				glClearColor(bgPtr[0], bgPtr[1], bgPtr[2], bgPtr[3]);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			} else {
				if (nFrameCount < 3 || nFramesSinceWindowResized < 3) {
					SDL_GL_SwapBuffers();
				} else {
					glFlush();
				}
			}
		} else {
			SDL_GL_SwapBuffers();
		}
#else
		if (bClearAuto == false) {
			// in accum mode resizing a window is BAD, so we clear on resize events.
			if (nFramesSinceWindowResized < 3) {
				glClearColor(bgPtr[0], bgPtr[1], bgPtr[2], bgPtr[3]);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}
		SDL_GL_SwapBuffers();
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
		
		if (ofAppPtr) {
			ofAppPtr->update();
		}
		
#ifdef OF_USING_POCO
		ofNotifyEvent(ofEvents.update, voidEventArgs);
#endif
		
	}
}

//------------------------------------------------------------
void ofxSDLAppWindow::exitApp() {
	ofLog(OF_LOG_VERBOSE, "SDL OF app is being terminated!");
	
	// clean up SDL
	for (int j = 0; j < numJoys; j++) {
		if (joys[j] && SDL_JoystickOpened(j)) {
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
	const SDL_VideoInfo* desktop = SDL_GetVideoInfo();
	return ofPoint(desktop->current_w, desktop->current_h, 0);
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
	
	string joyName(SDL_JoystickName(num));
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
	
	if (ofAppPtr) {
		ofAppPtr->joyButtonPressed(evt->jbutton.which,
								   evt->jbutton.button);
	}
	
#ifdef OF_USING_POCO
	joyEventArgs.device = evt->jbutton.which;
	joyEventArgs.button = evt->jbutton.button;
	// TODO why does this break?!
	//ofNotifyEvent(ofxSDLEvents.joyButtonReleased, joyEventArgs);
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
#endif
}

//------------------------------------------------------------
void ofxSDLAppWindow::joyMovedHandler(SDL_Event* evt) {
	static ofxSDLJoyAxisEventArgs joyAxisEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
	float position = (float)evt->jaxis.value / 32768.0;
	
	if (ofAppPtr) {
		ofAppPtr->joyAxisMoved(evt->jaxis.which,
							   evt->jaxis.axis,
							   position);
	}
	
#ifdef OF_USING_POCO
	joyAxisEventArgs.device = evt->jaxis.which;
	joyAxisEventArgs.axis = evt->jaxis.axis;
	joyAxisEventArgs.position = position;
	//ofNotifyEvent(ofxSDLEvents.joyAxisMoved, joyEventArgs);
#endif
}

//------------------------------------------------------------
void ofxSDLAppWindow::mouseDownHandler(SDL_Event* evt) {
	static ofMouseEventArgs mouseEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
	if (ofAppPtr) {
		ofAppPtr->mouseX = evt->button.x;
		ofAppPtr->mouseY = evt->button.y;
		ofAppPtr->mousePressed(evt->button.x,
							   evt->button.y,
							   evt->button.button); // are button consts the same as glut?
		// TODO: break out mouseScroll as a seperate action?
	}
	
#ifdef OF_USING_POCO
	mouseEventArgs.x = evt->button.x;
	mouseEventArgs.y = evt->button.y;
	mouseEventArgs.button = evt->button.button;
	ofNotifyEvent(ofEvents.mousePressed, mouseEventArgs);
#endif
	
	buttonInUse = evt->button.button;
}

//------------------------------------------------------------
void ofxSDLAppWindow::mouseUpHandler(SDL_Event* evt) {
	static ofMouseEventArgs mouseEventArgs;
	
	if (nFrameCount == 0) {
		return;
	}
	
	if (ofAppPtr) {
		ofAppPtr->mouseX = evt->button.x;
		ofAppPtr->mouseY = evt->button.y;
		ofAppPtr->mouseReleased(evt->button.x,
								evt->button.y,
								evt->button.button); // are button consts the same as glut?
		// TODO: break out mouseScroll as a seperate action?
	}
	
#ifdef OF_USING_POCO
	mouseEventArgs.x = evt->button.x;
	mouseEventArgs.y = evt->button.y;
	mouseEventArgs.button = evt->button.button;
	ofNotifyEvent(ofEvents.mouseReleased, mouseEventArgs);
#endif
	
	buttonInUse = 0;
}

void ofxSDLAppWindow::keyDownHandler(SDL_Event* evt) {
	static ofKeyEventArgs keyEventArgs;
	
	// TODO: better handling of non chars and true unicode
	SDLKey sym = evt->key.keysym.sym;
	char key = evt->key.keysym.unicode & 0x7F;
	
	if (ofAppPtr) {
		ofAppPtr->keyPressed(sym);
	}
	
#ifdef OF_USING_POCO
	keyEventArgs.key = sym;
	ofNotifyEvent(ofEvents.keyPressed, keyEventArgs);
#endif
	
	// for text input
	if (SDLK_RETURN) {
		text[0]=0x00;
	}
	if (SDLK_BACKSPACE) {
		int textlen=SDL_strlen(text);
		
		do {
			if (textlen==0) {
				break;
			}
			if ((text[textlen-1] & 0x80) == 0x00) {
				/* One byte */
				text[textlen-1]=0x00;
				break;
			}
			if ((text[textlen-1] & 0xC0) == 0x80) {
				/* Byte from the multibyte sequence */
				text[textlen-1]=0x00;
				textlen--;
			}
			if ((text[textlen-1] & 0xC0) == 0xC0) {
				/* First byte of multibyte sequence */
				text[textlen-1]=0x00;
				break;
			}
		} while(1);
		
	}
	
	// --- quit sequences -----------------
	
	if (sym == SDLK_ESCAPE) {
		exitApp();
	}
	
#ifdef TARGET_OSX
	if (sym == SDLK_q && evt->key.keysym.mod & KMOD_META) { // OSX quit command
		exitApp();
	}
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
	
	SDLKey sym = evt->key.keysym.sym;
	char key = evt->key.keysym.unicode & 0x7F; // TODO: doesn't work
	
	if (ofAppPtr) {
		ofAppPtr->keyReleased(sym);
	}
	
#ifdef OF_USING_POCO
	keyEventArgs.key = sym;
	ofNotifyEvent(ofEvents.keyReleased, keyEventArgs);
#endif
}

void ofxSDLAppWindow::textInputHandler(SDL_Event* evt) {
	
	if (SDL_strlen(evt->text.text) == 0 || evt->text.text[0] == '\n' || markedRect.w < 0)
		return;
	
	//fprintf(stderr, "Keyboard: text input \"%s\"\n", evt->text.text);
	
	if (SDL_strlen(text) + SDL_strlen(evt->text.text) < sizeof(text))
		SDL_strlcat(text, evt->text.text, sizeof(text));
	
	//fprintf(stderr, "text inputed: %s\n", text);
	
	// After text inputed, we can clear up markedText because it
	// is committed
	markedText[0] = 0;
	
	updateTextRect();
	
}

void ofxSDLAppWindow::textEditHandler(SDL_Event* evt) {
	
	//	fprintf(stderr, "text editing \"%s\", selected range (%d, %d)\n",
	//			evt->edit.text, evt->edit.start, evt->edit.length);
	
	strcpy(markedText, evt->edit.text);
	cursor = evt->edit.start;
	
	updateTextRect();	
	
}

void ofxSDLAppWindow::updateTextRect() {
	
	//	int textlen = SDL_strlen(text);
	//	for (int i = 0; i < textlen; i++) {
	//		cout << text[i];
	//	}
	//cout << text << endl;	
	cout << markedText << endl;
	
	//    int w = 0, h = textRect.h;
	//    SDL_Rect cursorRect, underlineRect;
	//	
	//    SDL_FillRect(gScreen, &textRect, backColor);
	//	
	//    if (*text)
	//    {
	//        RenderText(gScreen, font, text, textRect.x, textRect.y, textColor);
	//        TTF_SizeUTF8(font, text, &w, &h);
	//    }
	//	
	//    markedRect.x = textRect.x + w;
	//    markedRect.w = textRect.w - w;
	//    if (markedRect.w < 0)
	//    {
	//        SDL_Flip(screen);
	//        // Stop text input because we cannot hold any more characters
	//        SDL_StopTextInput();
	//        return;
	//    }
	//    else
	//    {
	//        SDL_StartTextInput();
	//    }
	//	
	//    cursorRect = markedRect;
	//    cursorRect.w = 2;
	//    cursorRect.h = h;
	//	
	//    SDL_FillRect(gScreen, &markedRect, backColor);
	//    if (markedText[0])
	//    {
	//        if (cursor)
	//        {
	//            char *p = utf8_advance(markedText, cursor);
	//            char c = 0;
	//            if (!p)
	//                p = &markedText[strlen(markedText)];
	//			
	//            c = *p;
	//            *p = 0;
	//            TTF_SizeUTF8(font, markedText, &w, 0);
	//            cursorRect.x += w;
	//            *p = c;
	//        }
	//        RenderText(gScreen, font, markedText, markedRect.x, markedRect.y, textColor);
	//        TTF_SizeUTF8(font, markedText, &w, &h);
	//		
	//        underlineRect = markedRect;
	//        underlineRect.y += (h - 2);
	//        underlineRect.h = 2;
	//        underlineRect.w = w;
	//		
	//        SDL_FillRect(gScreen, &underlineRect, lineColor);
	//    }
	//	
	//    SDL_FillRect(gScreen, &markedRect, backColor);
	//    if (markedText[0])
	//    {
	//        if (cursor)
	//        {
	//            char *p = utf8_advance(markedText, cursor);
	//            char c = 0;
	//            if (!p)
	//                p = &markedText[strlen(markedText)];
	//			
	//            c = *p;
	//            *p = 0;
	//            TTF_SizeUTF8(font, markedText, &w, 0);
	//            cursorRect.x += w;
	//            *p = c;
	//        }
	//        RenderText(gScreen, font, markedText, markedRect.x, markedRect.y, textColor);
	//        TTF_SizeUTF8(font, markedText, &w, &h);
	//		
	//        underlineRect = markedRect;
	//        underlineRect.y += (h - 2);
	//        underlineRect.h = 2;
	//        underlineRect.w = w;
	//		
	//        SDL_FillRect(gScreen, &underlineRect, lineColor);
	//    }
	
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