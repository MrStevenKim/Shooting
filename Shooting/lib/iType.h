#pragma once

// 정의 : 실체 없음. 헤더파일, 선언x(할당x) + Macro

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "iPoint.h"
#include "iSize.h"
#include "iRect.h"

#include "iArray.h"
#include "iString.h"

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;

enum iKeyState {
    iKeyStateBegan = 0,
    iKeyStateMoved,
    iKeyStateEnded
};

#define keyboard_left   1
#define keyboard_right  2
#define keyboard_up     4
#define keyboard_down   8
#define keyboard_space  16

struct Texture {
    void* texID;// Gluint texID;
    int width, height;
    int potWidth, potHeight;
    int retainCount;
};

#define TOP     1
#define VCENTER 2
#define BOTTOM  4

#define LEFT    8
#define HCENTER 16
#define RIGHT   32

#define REVERSE_NONE    0
#define REVERSE_WIDTH   1
#define REVERSE_HEIGHT  2

