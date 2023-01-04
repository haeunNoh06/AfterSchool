#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int fps;// 초당 프레임 갯수 (frame per sec)
	int idx;// 애니메이션 인덱스
	int frames;// 애니메이션 frame 수
	long ani_time;// 애니메이션이 바뀔 때의 시각
	long ani_delay;// 화면 전환의 텀
	int speed;// 속도

};

int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	long start_time;
	long spent_time;

	int gravity = 10;// 중력

	Texture run[10];
	run[0].loadFromFile("./resources/imgs/Run__000.png");
	run[1].loadFromFile("./resources/imgs/Run__001.png");
	run[2].loadFromFile("./resources/imgs/Run__002.png");
	run[3].loadFromFile("./resources/imgs/Run__003.png");
	run[4].loadFromFile("./resources/imgs/Run__004.png");
	run[5].loadFromFile("./resources/imgs/Run__005.png");
	run[6].loadFromFile("./resources/imgs/Run__006.png");
	run[7].loadFromFile("./resources/imgs/Run__007.png");
	run[8].loadFromFile("./resources/imgs/Run__008.png");
	run[9].loadFromFile("./resources/imgs/Run__009.png");

	// Player
	struct Player player;
	player.fps = 10;
	player.sprite.setTexture(&run[0]);
	player.sprite.setSize(Vector2f(90, 120));
	player.sprite.setPosition(200, 200);
	player.frames = 10;
	player.ani_delay = 1000 / player.frames / 2;// 0.5초마다 걸음
	player.speed = 5;

	start_time = clock();
	player.ani_time = start_time;

	while (window.isOpen())
	{
		spent_time = clock() - start_time;
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Space)
				{
					// 점프 기능
					player.sprite.move(0, -3);
				}
			default:
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.sprite.setScale(1, 1);
			player.sprite.move(player.speed, 0);

		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.sprite.setScale(-1, 1);
			player.sprite.move(-player.speed, 0);
		}

		// 0.1초마다 애니메이션 그림이 바뀜
		while (spent_time - player.ani_time > 1000/player.ani_delay)
		{
			// 반복하려고
			player.ani_time = spent_time;
			player.sprite.setTexture(&run[player.idx%player.frames]);
			player.idx++;
		}

		player.sprite.move(0, gravity);// 중력 적용

		window.clear(Color::Magenta);

		window.draw(player.sprite);

		window.display();
	}

	return 0;
}