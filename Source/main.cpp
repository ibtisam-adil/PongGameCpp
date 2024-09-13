#include "galba.h"

const unsigned STAGE_WIDTH = 1080;
const unsigned STAGE_HEIGHT = 720;
const float PADDLE_SPEED = 12.0f;
const float BALL_SPEED = 8.0f;

struct Paddle {
	float x = 0.0f;
	float y = 0.0f;
	float width = 20.0f;
	float height = 100.0f;
	Key upKey = Key::Up;
	Key downKey = Key::Down;

	Rectangle getCollider() {
		Rectangle rect{ x, y, width, height };
		return rect;
	}

	void render() {
		draw_rectangle(
			round_to_int(x),
			round_to_int(y),
			round_to_int(width),
			round_to_int(height)
		);
	}

	void update() {
		if (is_key_held_down(upKey)) {
			y -= PADDLE_SPEED;
		}
		else if (is_key_held_down(downKey)) {
			y += PADDLE_SPEED;
		}
		if (y < 0.0f) {
			y = 0.0f;
		}
		else if (y + height > STAGE_HEIGHT) {
			y = STAGE_HEIGHT - height;
		}
	}
};

struct Ball {
	float x = STAGE_WIDTH / 2;
	float y = STAGE_HEIGHT / 2;
	float width = 20.0f;
	float height = 20.0f;
	float radius = 15.0f;
	float velX = 0.0f;
	float velY = 0.0f;

	Ball() {
		velX = random_float_in_range(-BALL_SPEED, BALL_SPEED);
		velY = random_float_in_range(-BALL_SPEED, BALL_SPEED);
	}

	Rectangle getCollider() {
		Rectangle rect{ x, y, width, height };
		return rect;
	}

	void render() {
		draw_rectangle(
			round_to_int(x),
			round_to_int(y),
			round_to_int(width),
			round_to_int(height)
		);
	}

	void update() {
		x += velX;
		y += velY;
		if (x > STAGE_WIDTH || x < 0) {
			velX *= -1.0f;
		}
		if (y > STAGE_HEIGHT || y < 0) {
			velX *= -1.0f;
		}
	}
};

int main()
{
	initialize(STAGE_WIDTH, STAGE_HEIGHT, "Window");

	Paddle p1;
	p1.x = 20.0f;
	p1.y = (STAGE_HEIGHT / 2.0f) - (p1.height / 2.0f);

	Paddle p2;
	p2.x = STAGE_WIDTH - p2.width * 2;
	p2.y = (STAGE_HEIGHT / 2.0f) - (p2.height / 2.0f);
	p2.upKey = Key::Left;
	p2.downKey = Key::Right;

	Ball ball;

	while (is_window_open())
	{
		clear_window();
		ball.update();
		p1.update();
		p2.update();

		auto ballRect = ball.getCollider();
		auto paddleRect = p1.getCollider();
		auto paddleRect2 = p2.getCollider();

		if (CheckCollisionRecs(ballRect, paddleRect)
			|| CheckCollisionRecs(ballRect, paddleRect2)) {
			ball.velX *= -1.0f;
		}

		p1.render();
		p2.render();
		ball.render();
		display();
	}

	return 0;
}