#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>//SoundBuffer ���
//#include <Windows.h>// sleep() ���

using namespace sf;

struct Player {
	RectangleShape sprite;// sprite : �׸��� �Ǵ� �κ�
	int speed;
	int score;
	int life;
	float x, y;// player ��ǥ
};

//�Ѿ�
struct Bullet {
	RectangleShape sprite;
	int speed;
	int is_fired;// �߻� ����

};

struct Enemy {
	RectangleShape sprite;
	SoundBuffer explosion_buffer;
	Sound explosion_sound;//�Ҹ��� ���� ������ ����
	int speed;
	int score;
	int life;
	int respawn_time;
};

struct Textures {
	Texture bg; // ��� �̹���
	Texture gameover;// ���� ���� �̹���
	Texture player;// �÷��̾� �̹���
	Texture enemy;// �� �̹���
	Texture bullet;// �Ѿ� �̹���
};

//obj1�� obj2�� �浹 ���� �浹�ϸ� 1�� ��ȯ �ƴϸ� 0���� ��ȯ
int is_collide(RectangleShape obj1, RectangleShape obj2) {
	return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}


// �������� - const�� ó���Ͽ� �߰��� ���� �ٲ� �� ���� �͸� ���������� ����
const int ENEMY_NUM = 10;// ���� �ִ� ����
const int W_WIDTH = 1280, W_HEIGHT = 575;// â�� ũ��
const int GO_WIDTH = 880, GO_HEIGHT = 468;// ���ӿ��� �׸��� ũ��

int main(void) {

	//�̹���
	struct Textures t;
	t.bg.loadFromFile("./resources/image/background.jpg");
	t.gameover.loadFromFile("./resources/image/gameover.png");
	t.player.loadFromFile("./resources/image/player.png");
	t.enemy.loadFromFile("./resources/image/enemy.png");
	t.bullet.loadFromFile("./resources/image/bullet.png");

	srand(time(NULL));//���� �Լ� ���

	//640 x 480 ������ ȭ�� ����
	//��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AfterSchool");
	window.setFramerateLimit(60);//1�ʿ� 60�� �����ش�. �÷��̾ ���� ���� �ʵ��� �ϱ�


	long start_time = clock();// ���� ���� �ð�
	long spent_time;// ���� ���� �ð�
	int is_gameover = 0;

	// BGM
	SoundBuffer BGM_buffer;
	BGM_buffer.loadFromFile("./resources/sound/bgm.ogg");
	Sound BGM_sound;
	BGM_sound.setBuffer(BGM_buffer);
	BGM_sound.setLoop(1);// BGM ���� �ݺ�
	BGM_sound.play();

	// text ��Ʈ
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");//C����̺꿡 �ִ� ��Ʈ ��������

	Text text;
	char info[40];
	text.setFont(font);//��Ʈ ����
	text.setCharacterSize(24);//��Ʈ ũ��
	text.setFillColor(Color(255, 255, 255));//RGB�� ��� ǥ��
	text.setPosition(0, 0);//�ؽ�Ʈ ��ġ 0,0

	//���
	Sprite bg_sprite;
	bg_sprite.setTexture(t.bg);
	bg_sprite.setPosition(0, 0);

	//gameover
	Sprite gameover_sprite;
	gameover_sprite.setTexture(t.gameover);
	gameover_sprite.setPosition(0,0);//game over �׸� ��� ��Ÿ����

	// �÷��̾�
	struct Player player;
	player.sprite.setTexture(&t.player);// �����͸� �Ѱ��ֱ� ������ �ּҰ� �Ѱ��ֱ�
	player.sprite.setSize(Vector2f(150, 150));//�÷��̾� ������
	player.sprite.setPosition(100, 100);//�÷��̾� ���� ��ġ
	player.x = player.sprite.getPosition().x;// x��ǥ
	player.y = player.sprite.getPosition().y;// y��ǥ
	player.speed = 7;//�÷��̾� �ӵ�
	player.score = 0;//�÷��̾� �ʱ� ����
	player.life = 1;

	// �Ѿ�
	struct Bullet bullet;
	bullet.sprite.setTexture(&t.bullet);// �����͸� �Ѱ��ֱ� ������ �ּҰ� �Ѱ��ֱ�
	bullet.sprite.setSize(Vector2f(40, 40));// �Ѿ� ũ��
	bullet.sprite.setPosition(player.x+110, player.y+20);// �Ѿ� �ʱ� ��ġ (�ӽ� �׽�Ʈ)
	bullet.speed = 20;// �Ѿ� �ӵ�
	bullet.is_fired = 0;// �Ѿ� �߻� ���� (0:false, 1:true)

	// enemy
	struct Enemy enemy[ENEMY_NUM];

	/* enemy update */
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// TODO : ������ ��ȿ������ �ڵ��̹Ƿ� ���߿� refactoring
		enemy[i].sprite.setTexture(&t.enemy);// �����͸� �Ѱ��ֱ� ������ �ּҰ� �Ѱ��ֱ�
		enemy[i].explosion_buffer.loadFromFile("./resources/sound/rumble.flac");
		enemy[i].explosion_sound.setBuffer(enemy[i].explosion_buffer);
		enemy[i].score = 100;
		enemy[i].respawn_time = 8;
		enemy[i].sprite.setSize(Vector2f(70, 70));
		enemy[i].sprite.setPosition(rand()%300+W_WIDTH*0.9, rand() % 380);// 90%���� ������ ����
		enemy[i].life = 1;
		enemy[i].speed = -(rand() % 5 + 1);
	}


	//���� ��Ű�� �����? -> ���� �ݺ�
	while (window.isOpen()) //������â�� �����ִ� ���� ��� �ݺ�
	{ 
		spent_time = clock() - start_time;// �ð��� ������ ���� ����

		//�Ѿ��� �÷��̾� ����ٴ� �� �ֵ��� 
		player.x = player.sprite.getPosition().x;	//�÷��̾� x��ǥ
		player.y = player.sprite.getPosition().y;	//�÷��̾� y��ǥ

		Event event;//�̺�Ʈ ����
		while (window.pollEvent(event)) //�̺�Ʈ�� �߻�. �̺�Ʈ�� �߻��ؾ� event �ʱ�ȭ�� ��
		{
			switch (event.type)
			{
			//����(x)��ư�� ������ Event::Closed(0) 
			case Event::Closed ://������
				window.close();//������â�� ����
				break;
			//Ű���带 ������ �� 
			case Event::KeyPressed: 
			//case�� �ȿ� ������ ������ ������ �߰�ȣ�� �ľ� ��
			{
				break;
			}
			}
		}

		/* game ���� update */
		if (player.life <= 0)
		{
			is_gameover = 1;// 1 == true
		}

		/* player update */
		//����Ű
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.sprite.move(-1 * player.speed, 0);//���� �̵�
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.sprite.move(0, -1 * player.speed);//���� �̵�
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.sprite.move(0, player.speed);//�Ʒ��� �̵�
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.sprite.move(player.speed, 0);//������ �̵�
		}

		//player �̵� ���� ����
		// TODO : ������ �Ʒ��� ������ �ǵ���� ��ġ��
		if (player.x < 0)
		{
			player.sprite.setPosition(0, player.y);
		}
		else if (player.x > W_WIDTH - 150)
		{
			player.sprite.setPosition(W_WIDTH - 150, player.y);
		}
		if (player.y < 0)
		{
			player.sprite.setPosition(player.x, 0);
		}
		else if (player.y > W_HEIGHT - 150)
		{
			player.sprite.setPosition(player.x, W_HEIGHT - 150);
		}

		/* bullet update */
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			//�Ѿ��� �߻� �Ǿ����� �ʴٸ�
			if (!bullet.is_fired)
				bullet.sprite.setPosition(player.x + 110, player.y + 20);// �Ѿ� �ʱ� ��ġ (�ӽ� �׽�Ʈ)
			bullet.is_fired = 1;
		}

		if (bullet.is_fired) {
			bullet.sprite.move(bullet.speed, 0);
			if (bullet.sprite.getPosition().x > W_WIDTH)
				bullet.is_fired = 0;
		}

		//enemy���� �浹
		//intersects : �÷��̾�� �� ���̿��� �������� �ִ°�
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			// 10�� ���� enemy�� ��
			if (spent_time % (1000 * enemy[i].respawn_time ) < 1000 / 60) // 1�ʵ��� 60�������� �ݺ��Ǳ� ������
			{
				enemy[i].sprite.setSize(Vector2f(70, 70));
				enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);// 90%���� ������ ����
				enemy[i].life = 1;
				// 10�ʸ��� enemy �ӵ� +1
				enemy[i].speed = -(rand() % 3 + 1 + (spent_time/1000/enemy[i].respawn_time));
			}
			
			if (enemy[i].life > 0)
			{
				// enemy���� �浹
				if (is_collide(player.sprite, enemy[i].sprite) || is_collide(bullet.sprite, enemy[i].sprite)) 
				{
					enemy[i].life -= 1;//���� ���� ���̱�
					player.score += enemy[i].score;

					// TODO : �ڵ� refactoring �ʿ�
					if (enemy[i].life == 0)
					{
						enemy[i].explosion_sound.play();
					}
				}

				// enemy�� x��ǥ�� 0�� �Ǹ�
				else if (enemy[i].sprite.getPosition().x < 0)
				{
					player.life -= 1;// player ��� 1 ����
					enemy[i].life = 0;// �� ���ֱ�
				}

				// �Ѿ˰� enemy�� �浹
				if (is_collide(bullet.sprite, enemy[i].sprite))
				{
					enemy[i].life -= 1;
					player.score += enemy[i].score;

					// TODO : �ڵ� refactoring �ʿ�
					if (enemy[i].life == 0)
					{
						enemy[i].explosion_sound.play();
					}
					bullet.is_fired = 0;
				}

				enemy[i].sprite.move(enemy[i].speed, 0);
			}

		}

		// ���� �ð��� ������ ����
		sprintf(info, "life: %d score: %d time: %d\n", player.life, player.score, spent_time/1000);

		text.setString(info);

		window.clear(Color::Black);//�÷��̾� ��ü ���� (��� �����)
		window.draw(bg_sprite);

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].life > 0)  window.draw(enemy[i].sprite);//�� �����ֱ�
		}

		//ȭ���� ������ �ִ� ���� ��� �׷��� ��
		//draw�� ���߿� ȣ���Ҽ��� �켱������ ������
		window.draw(player.sprite);//�÷��̾� �����ֱ�(�׷��ֱ�)
		if (bullet.is_fired)
			window.draw(bullet.sprite);
		window.draw(text);
		window.draw(bullet.sprite);// �Ѿ� �׸���

		if (is_gameover)
		{
			window.draw(gameover_sprite);
			// TODO : ������ ���ߴ� ���� ������ ��
		}

		window.display();
	}

	return 0;
}