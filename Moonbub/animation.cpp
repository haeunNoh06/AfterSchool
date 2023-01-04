#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	// 애니메이션 관련 변수
	int fps;// 초당 프레임 갯수 (frame per sec)
	int idx;// 애니메이션 인덱스
	int frames;// 애니메이션 frame 수
	long ani_time;// 애니메이션이 바뀔 때의 시각
	long ani_delay;// 화면 전환의 텀

	int speed;// 속도
	//점프와 관련된 변수
	int is_jumping;// 점프 상태
	int jumping_time;// 점프를 시작하는 시각
	int jump_speed;// 점프 속도
};

int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	long start_time;
	long spent_time;// 게임 진행 시간

	const int GRAVITY = 5;// 중력
	const int PLATFORM_Y = 600;// 땅 바닥의 y좌표

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
	player.jump_speed = GRAVITY * 2;// 일정한 속도로 올라가거나 내려감

	start_time = clock();
	player.ani_time = start_time;
	player.jumping_time = start_time;
	player.is_jumping = 0;

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
					if (player.is_jumping == 0)
					{
						player.jumping_time = spent_time;
					}
					player.is_jumping = 1;// true
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

		//필요하다면 1000을 나중에 변수 처리할것
		if (spent_time - player.jumping_time > 1000)
		{
			player.is_jumping = 0;
		}

		player.sprite.move(0, GRAVITY);// 중력 적용
		
		if (player.is_jumping == 1)
		{
			player.sprite.move(0, -player.jump_speed);
		}

		// 플레이어가 땅바닥에 착지 하면
		if (player.sprite.getPosition().y + player.sprite.getSize().y > PLATFORM_Y)// 땅 바닥의 y좌표와 플레이어의 y좌표를 빼야 플레이어가 땅에 서있음
		{
			// 더 이상 내려갈 수 없게 한다
			player.sprite.setPosition(player.sprite.getPosition().x, PLATFORM_Y - player.sprite.getSize().y);
		}

		window.clear(Color::Magenta);

		window.draw(player.sprite);

		window.display();
	}

	return 0;
}