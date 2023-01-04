#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>//SoundBuffer 사용
//#include <SFML/Audio/SoundSource.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int x;
	int y;

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

// 장애물
struct Obstacle {
	RectangleShape sprite;
	int speed;
};

struct Textures {
	Texture run[10];
	Texture jump[10];
	Texture bg;
	Texture obstacle;// 장애물
};

const int OBSTACLE_NUM = 3;// 장애물 수
const int GRAVITY = 5;// 중력
const int PLATFORM_Y = 600;// 땅 바닥의 y좌표
const int W_WIDTH = 1200, W_HEIGHT = 800;// 창의 크기


int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	srand(time(0));

	long start_time;
	long spent_time;// 게임 진행 시간


	struct Textures t;
	t.bg.loadFromFile("./resources/imgs/background.png");
	t.obstacle.loadFromFile("./resources/imgs/obstacle.png");
	t.run[0].loadFromFile("./resources/imgs/Run__000.png");
	t.run[1].loadFromFile("./resources/imgs/Run__001.png");
	t.run[2].loadFromFile("./resources/imgs/Run__002.png");
	t.run[3].loadFromFile("./resources/imgs/Run__003.png");
	t.run[4].loadFromFile("./resources/imgs/Run__004.png");
	t.run[5].loadFromFile("./resources/imgs/Run__005.png");
	t.run[6].loadFromFile("./resources/imgs/Run__006.png");
	t.run[7].loadFromFile("./resources/imgs/Run__007.png");
	t.run[8].loadFromFile("./resources/imgs/Run__008.png");
	t.run[9].loadFromFile("./resources/imgs/Run__009.png");
	t.jump[0].loadFromFile("./resources/imgs/Jump__000.png");
	t.jump[1].loadFromFile("./resources/imgs/Jump__001.png");
	t.jump[2].loadFromFile("./resources/imgs/Jump__002.png");
	t.jump[3].loadFromFile("./resources/imgs/Jump__003.png");
	t.jump[4].loadFromFile("./resources/imgs/Jump__004.png");
	t.jump[5].loadFromFile("./resources/imgs/Jump__005.png");
	t.jump[6].loadFromFile("./resources/imgs/Jump__006.png");
	t.jump[7].loadFromFile("./resources/imgs/Jump__007.png");
	t.jump[8].loadFromFile("./resources/imgs/Jump__008.png");
	t.jump[9].loadFromFile("./resources/imgs/Jump__009.png");

	// Player
	struct Player player;
	player.fps = 10;
	player.sprite.setTexture(&t.run[0]);
	player.sprite.setSize(Vector2f(90, 120));
	player.sprite.setPosition(200, 200);
	player.x = player.sprite.getPosition().x;// 플레이어 x좌표
	player.y = player.sprite.getPosition().y;// 플레이어 y좌표
	player.frames = 10;
	player.ani_delay = 1000 / player.frames / 2;// 0.5초마다 걸음
	player.speed = 5;
	player.jump_speed = GRAVITY * 3;// 일정한 속도로 올라가거나 내려감

	// 장애물
	struct Obstacle ob[OBSTACLE_NUM];
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		ob[i].sprite.setTexture(&t.obstacle);
		ob[i].sprite.setPosition(W_WIDTH, W_HEIGHT);
		ob[i].speed = -(rand()%5+1);
	}

	//배경
	Sprite bg_sprite;
	bg_sprite.setTexture(t.bg);
	bg_sprite.setPosition(0, 0);

	// text 폰트
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Candara.ttf");//C드라이브에 있는 폰트 가져오기

	// 텍스트
	Text text;
	char info[40];
	text.setFont(font);//폰트 세팅
	text.setCharacterSize(24);//폰트 크기
	text.setFillColor(Color(0, 0, 0));//RGB로 흰색 표현
	text.setPosition(10, 10);//텍스트 위치 0,0

	start_time = clock();
	player.ani_time = start_time;
	player.jumping_time = start_time;
	player.is_jumping = 0;

	while (window.isOpen())
	{
		spent_time = clock() - start_time;

		player.x = player.sprite.getPosition().x;// 플레이어 x좌표
		player.y = player.sprite.getPosition().y;// 플레이어 y좌표

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

		// 시작 시간은 변하지 않음
		sprintf(info, "time: %d\n",spent_time / 1000);

		text.setString(info);

		// 0.1초마다 애니메이션 그림이 바뀜
		while (spent_time - player.ani_time > 1000 / player.ani_delay)
		{
			// 반복하려고
			player.ani_time = spent_time;
			player.sprite.setTexture(&t.run[player.idx % player.frames]);
			player.idx++;
		}

		//필요하다면 1000을 나중에 변수 처리할것
		if (spent_time - player.jumping_time > 500)
		{
			player.is_jumping = 0;
		}

		player.sprite.move(0, GRAVITY*2);// 중력 적용

		if (player.is_jumping == 1)
		{
			player.idx = 0;
			// 0.1초마다 애니메이션 그림이 바뀜
			while (spent_time - player.ani_time > 1000 / player.ani_delay)
			{
				// 반복하려고
				player.ani_time = spent_time;
				player.sprite.setTexture(&t.jump[player.idx % player.frames]);
				player.idx++;
			}
			player.sprite.move(0, -player.jump_speed);
		}

		// 플레이어가 땅바닥에 착지 하면
		if (player.sprite.getPosition().y + player.sprite.getSize().y > PLATFORM_Y)// 땅 바닥의 y좌표와 플레이어의 y좌표를 빼야 플레이어가 땅에 서있음
		{
			// 더 이상 내려갈 수 없게 한다
			player.sprite.setPosition(player.sprite.getPosition().x, PLATFORM_Y - player.sprite.getSize().y);
		}

		window.clear(Color::Blue);

		window.draw(bg_sprite);

		window.draw(player.sprite);

		window.draw(text);

		window.display();
	}

	return 0;
}