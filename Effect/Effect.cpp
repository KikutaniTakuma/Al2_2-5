#include "Effect/Effect.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Mouse/Mouse.h"
#include "Game/KeyInput/KeyInput.h"

Effect::Effect(Camera* camera) :
	Object(camera),
	acceleration(2.0f),
	emitter({ {-3.0f, -3.0f}, { 3.0f, 3.0f} }),
	particle({Vector2D(), Vector2D(), 2.0f,0.0f,false,255}),
	frequency(2),
	count(0),
	particleBuf(Quad()),
	blend(BlendMode::kBlendModeNormal)
{
	pos.Set({640.0f,360.0f}, {0.0f,0.0f});
	frame.Restart();

	for (auto& i : particle) {
		i = { Vector2D(), Vector2D(), 2.0f,0.0f,false,255 };
	}
}

void Effect::Update() {
	if (key.Pushed(DIK_1)) {
		blend = kBlendModeNormal;
	}
	if (key.Pushed(DIK_3)) {
		blend = kBlendModeAdd;
	}
	if (key.Pushed(DIK_4)) {
		blend = kBlendModeSubtract;
	}
	if (key.Pushed(DIK_0)) {
		blend = kBlendModeNone;
	}

	if (Mouse::LongPush(Mouse::Button::LEFT_BUTTON)) {
		pos.worldPos = { static_cast<float>(Mouse::x), static_cast<float>(Mouse::y) };
	}

	for (int i = count; i < count + frequency && count < particle.size(); i++) {
		if (!particle[i].flg) {
			particle[i].flg = true;
			particle[i].size = static_cast<float>(math.Random(55, 60));
			particle[i].pos = pos.worldPos;
			particle[i].pos.x += static_cast<float>(math.Random(static_cast<int>(emitter.leftBottom.x), static_cast<int>(emitter.rightTop.x)));
			particle[i].pos.y += static_cast<float>(math.Random(static_cast<int>(emitter.leftBottom.y), static_cast<int>(emitter.rightTop.y)));
			particle[i].moveVec = { particle[i].spd, particle[i].spd };
			particle[i].moveVec.Rotate(static_cast<float>(math.Random(0, 359)));
		}
	}
	count += frequency;

	math.Clamp(count, 0, static_cast<int>(particle.size()));
	if (count == particle.size()) {
		count = 0;
	}

	for (auto& i : particle) {
		if (i.flg) {
			i.alpha -= static_cast<int>(acceleration);
			i.pos += i.moveVec;
			if (i.alpha < 0) {
				i= { Vector2D(), Vector2D(), 2.0f,0.0f,false,255 };
			}
		}
	}
}

void Effect::Draw(Texture& tex) {
	Novice::DrawLine(0, 360, 1280, 360, WHITE);
	Novice::DrawLine(640, 0, 640, 720, WHITE);

	Novice::ScreenPrintf(0, 0, "1 : aBlend  3 : add  4 : sub  0 : None");
	if (blend == kBlendModeNormal) {
		Novice::ScreenPrintf(0, 20, "DX_BLENDMODE_ALPHA");
	}
	else if (blend == kBlendModeAdd) {
		Novice::ScreenPrintf(0, 20, "DX_BLENDMODE_ADD");
	}
	else if (blend == kBlendModeSubtract) {
		Novice::ScreenPrintf(0, 20, "DX_BLENDMODE_SUB");
	}
	else if (blend == kBlendModeNone) {
		Novice::ScreenPrintf(0, 20, "DX_BLENDMODE_NOBLEND");
	}
	Novice::ScreenPrintf(0, 80, "    : MOWA MOWA");

	Novice::SetBlendMode(blend);

	for (auto& i : particle) {
		if (i.flg) {
			particleBuf.Set(i.pos, { i.size,i.size });
			camera->DrawQuad(particleBuf, tex, 0, false, 0xffffff00 + i.alpha);
		}
	}

	Novice::SetBlendMode(kBlendModeNormal);
}
