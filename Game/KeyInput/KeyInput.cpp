#include "KeyInput.h"
#include <Novice.h>

KeyInput key;

char KeyInput::Keys(int num) {
	return keys[num];
}

char KeyInput::PreKeys(int num) {
	return preKeys[num];
}

bool KeyInput::Pushed(int num) {
	return keys[num] && !preKeys[num];
}

bool KeyInput::LongPush(int num) {
	return keys[num] && preKeys[num];
}

bool KeyInput::Released(int num) {
	return !keys[num] && preKeys[num];
}

void KeyInput::Input() {
	memcpy(preKeys, keys, KEY_MAX_NUM);
	Novice::GetHitKeyStateAll(keys);
}