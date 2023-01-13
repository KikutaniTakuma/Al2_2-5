#pragma once

#include "Game/Object/Object.h"
#include "Game/Frame/Frame.h"
#include <array>
#include <Novice.h>

class Effect : public Object {
private:
	struct Emitter {
		Vector2D rightTop;
		Vector2D leftBottom;
	};

	struct Particle {
		Vector2D pos;
		Vector2D moveVec;
		float spd;
		float size;
		bool flg;
		int alpha;
	};

public:
	Effect(Camera* camera);

private:
	Emitter emitter;
	Quad particleBuf;
	std::array<Particle, std::size_t(400)> particle;
	Frame frame;
	const int frequency;
	float acceleration;
	int count;

	BlendMode blend;

public:
	void Update() override;
	void Draw(Texture& tex) override;
};