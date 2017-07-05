#pragma once

#include <gslib.h>
enum class KEY :unsigned int
{
	ESCAPE = 0x01,
	NUM_1 = 0x02,
	NUM_2 = 0x03,
	NUM_3 = 0x04,
	NUM_4 = 0x05,
	NUM_5 = 0x06,
	NUM_6 = 0x07,
	NUM_7 = 0x08,
	NUM_8 = 0x09,
	NUM_9 = 0x0A,
	NUM_0 = 0x0B,
	MINUS = 0x0C,
	EQUALS = 0x0D,
	BACK = 0x0E,
	TAB = 0x0F,
	Q = 0x10,
	W = 0x11,
	E = 0x12,
	R = 0x13,
	T = 0x14,
	Y = 0x15,
	U = 0x16,
	I = 0x17,
	O = 0x18,
	P = 0x19,
	LBRACKET = 0x1A,
	RBRACKET = 0x1B,
	RETURN = 0x1C,
	LCONTROL = 0x1D,
	A = 0x1E,
	S = 0x1F,
	D = 0x20,
	F = 0x21,
	G = 0x22,
	H = 0x23,
	J = 0x24,
	K = 0x25,
	L = 0x26,
	SEMICOLON = 0x27,
	APOSTROPHE = 0x28,
	GRAVE = 0x29,
	LSHIFT = 0x2A,
	BACKSLASH = 0x2B,
	Z = 0x2C,
	X = 0x2D,
	C = 0x2E,
	V = 0x2F,
	B = 0x30,
	N = 0x31,
	M = 0x32,
	COMMA = 0x33,
	PERIOD = 0x34,
	SLASH = 0x35,
	RSHIFT = 0x36,
	MULTIPLY = 0x37,
	LMENU = 0x38,
	SPACE = 0x39,
	CAPITAL = 0x3A,
	F1 = 0x3B,
	F2 = 0x3C,
	F3 = 0x3D,
	F4 = 0x3E,
	F5 = 0x3F,
	F6 = 0x40,
	F7 = 0x41,
	F8 = 0x42,
	F9 = 0x43,
	F10 = 0x44,
	NUMLOCK = 0x45,
	SCROLL = 0x46,
	NUMPAD7 = 0x47,
	NUMPAD8 = 0x48,
	NUMPAD9 = 0x49,
	SUBTRACT = 0x4A,
	NUMPAD4 = 0x4B,
	NUMPAD5 = 0x4C,
	NUMPAD6 = 0x4D,
	ADD = 0x4E,
	NUMPAD1 = 0x4F,
	NUMPAD2 = 0x50,
	NUMPAD3 = 0x51,
	NUMPAD0 = 0x52,
	DECIMAL = 0x53,
	F11 = 0x57,
	F12 = 0x58,
	F13 = 0x64,
	F14 = 0x65,
	F15 = 0x66,
	KANA = 0x70,
	CONVERT = 0x79,
	NOCONVERT = 0x7B,
	YEN = 0x7D,
	NUMPADEQUAL = 0x8D,
	CIRCUMFLEX = 0x90,
	AT = 0x91,
	COLON = 0x92,
	UNDERLINE = 0x93,
	KANJI = 0x94,
	STOP = 0x95,
	AX = 0x96,
	UNLABELED = 0x97,
	NUMPADENTER = 0x9C,
	RCONTROL = 0x9D,
	NUMPADCOMMA = 0xB3,
	DIVIDE = 0xB5,
	SYSRQ = 0xB7,
	RMENU = 0xB8,
	HOME = 0xC7,
	UP = 0xC8,
	PRIOR = 0xC9,
	LEFT = 0xCB,
	RIGHT = 0xCD,
	END = 0xCF,
	DOWN = 0xD0,
	NEXT = 0xD1,
	INSERT = 0xD2,
	KDELETE = 0xD3,
	LWIN = 0xDB,
	RWIN = 0xDC,
	APPS = 0xDD,
};
enum class MOUSE : unsigned int
{
	LEFT = 0x0001U,
	RIGHT = 0x0002U,
	CENTER = 0x0004U,
	BUTTON_4 = 0x0008U,
};
class Input
{
public:
	static Input& getInstance()
	{
		static Input self;
		return self;
	}

	const bool keyDown(KEY _key)const
	{
		return gsGetKeyTrigger(static_cast<unsigned int>(_key)) == GS_TRUE;
	}
	const bool keyState(KEY _key)const
	{
		return gsGetKeyState(static_cast<unsigned int>(_key)) == GS_TRUE;
	}
	const bool mouseDown(MOUSE _mouse)const
	{
		return gsGetMouseButtonTrigger(static_cast<GMOUSTATE>(_mouse)) == GS_TRUE;
	}
	const bool mouseState(MOUSE _mouse)const
	{
		return gsGetMouseButtonState(static_cast<GMOUSTATE>(_mouse)) == GS_TRUE;
	}
	const bool mouseUp(MOUSE _mouse)const
	{
		return gsGetMouseButtonDetach(static_cast<GMOUSTATE>(_mouse)) == GS_TRUE;
	}
	const GSvector2 mousePosition()const
	{
		int x, y;
		gsGetMouseCursorPosition(&x, &y);
		return GSvector2(x, y);
	}
	const GSvector2 mouseMove()const
	{
		int x, y;
		gsGetMouseVelocity(&x, &y, 0);
		return GSvector2(x, y);
	}
	const float up_down()const
	{
		float v = keyState(KEY::UP) ? 1.0f : 0.0f;
		v -= keyState(KEY::DOWN) ? 1.0f : 0.0f;
		return v;
	}
	const float right_left()const
	{
		float v = this->keyState(KEY::RIGHT) ? 1.0f : 0.0f;
		v -= this->keyState(KEY::LEFT) ? 1.0f : 0.0f;
		return v;
	}
	const GSvector2 velocity()const
	{
		GSvector2 v(0.0f, 0.0f);
		if (keyState(KEY::W))
		{
			v.y += 1;
		}
		if (keyState(KEY::S))
		{
			v.y -= 1;
		}
		if (keyState(KEY::A))
		{
			v.x += 1;
		}
		if (keyState(KEY::D))
		{
			v.x -= 1;
		}
		return v.normalize();
	}
	void mouseClamp(const GSvector2& _min, const GSvector2& _max)
	{
		GSvector2 v = mousePosition();
		GSvector2 next(0, 0);
		gsVector2Maximize(&next, &v, &_min);
		gsVector2Minimize(&next, &next, &_max);
		gsSetMouseCursorPosition(next.x, next.y);
	}

private:
	Input(){}
	Input(const Input&);
	Input& operator=(const Input&);
};