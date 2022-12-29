/**
*  TODO List
* 1) ������ : �ӵ�����, ������ ����
* 2) �Ѿ� �ý��� ����
* 3) sound effect ����
*/


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
	int is_fired;// �߻� ����
};

struct Enemy {
	RectangleShape sprite;
	int speed;
	int life;
};

struct Item {
	RectangleShape sprite;
	int delay;
	int is_presented;//�������� ��Ÿ���°�
	long presented_time;
};

struct Textures {
	Texture bg; // ��� �̹���
	Texture enemy;// �� �̹���
	Texture gameover;// ���� ���� �̹���
	Texture item_delay;// ���� ������ �̹���
	Texture item_speed;// �̼� ������ �̹���
	Texture player;// �÷��̾� �̹���
	Texture bullet;// �Ѿ� �̹���
};

struct SBuffers {
	SoundBuffer BGM;
	SoundBuffer rumble;
};

//obj1�� obj2�� �浹 ���� �浹�ϸ� 1�� ��ȯ �ƴϸ� 0���� ��ȯ
int is_collide(RectangleShape obj1, RectangleShape obj2) {
	return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}

// �������� - const�� ó���Ͽ� �߰��� ���� �ٲ� �� ���� �͸� ���������� ����
const int ENEMY_NUM = 10;// ���� �ִ� ����
const int BULLET_NUM = 50;// �Ѿ� �ִ� ����
const int ITEM_NUM = 2;// �������� �ִ� ����
const int W_WIDTH = 1280, W_HEIGHT = 575;// â�� ũ��
const int GO_WIDTH = 880, GO_HEIGHT = 468;// ���ӿ��� �׸��� ũ��

int main(void) {

	//�̹���
	struct Textures t;
	t.bg.loadFromFile("./resources/image/background.jpg");
	t.enemy.loadFromFile("./resources/image/enemy.png"); 
	t.gameover.loadFromFile("./resources/image/gameover.png");
	t.player.loadFromFile("./resources/image/player.png");
	t.item_delay.loadFromFile("./resources/image/item_damage.png");
	t.item_speed.loadFromFile("./resources/image/item_speed.png");
	t.bullet.loadFromFile("./resources/image/bullet.png");

	// BGM
	struct SBuffers sb;
	sb.BGM.loadFromFile("./resources/sound/bgm.ogg");
	sb.rumble.loadFromFile("./resources/sound/rumble.flac");// �� ���� �� ȿ����

	srand(time(0));//���� �Լ� ���

	//640 x 480 ������ ȭ�� ����
	//��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AfterSchool");
	window.setFramerateLimit(60);//1�ʿ� 60�� �����ش�. �÷��̾ ���� ���� �ʵ��� �ϱ�

	long start_time = clock();// ���� ���� �ð�
	long spent_time;// ���� ���� �ð�
	long fired_time = 0;// �ֱ� �Ѿ��� �߻�� �ð�
	int is_gameover = 0;

	// BGM
	Sound BGM_sound;
	BGM_sound.setBuffer(sb.BGM);
	BGM_sound.setLoop(1);// BGM ���� �ݺ�
	BGM_sound.play();

	// text ��Ʈ
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Candara.ttf");//C����̺꿡 �ִ� ��Ʈ ��������

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
	player.life = 1;// �÷��̾� ����

	// �Ѿ�
	int bullet_speed = 20;// �Ѿ� �ӵ�
	int bullet_idx = 0;// �߻�� ������ �ε��� ������ų ��
	int bullet_delay = 500;	// �Ѿ��� delay�� ����� �Ӽ��̹Ƿ� struct�� ���� ����. 0.5�ʸ��� ����
	Sound bullet_sound;
	bullet_sound.setBuffer(sb.rumble);

	struct Bullet bullet[BULLET_NUM];
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].sprite.setTexture(&t.bullet);// �����͸� �Ѱ��ֱ� ������ �ּҰ� �Ѱ��ֱ�
		bullet[i].sprite.setSize(Vector2f(40, 40));// �Ѿ� ũ��
		bullet[i].sprite.setPosition(player.x+110, player.y+20);// �Ѿ� �ʱ� ��ġ
		bullet[i].is_fired = 0;// �Ѿ� �߻� ���� (0:false, 1:true)
	}

	// enemy
	struct Enemy enemy[ENEMY_NUM];
	Sound enemy_explosion_sound;
	enemy_explosion_sound.setBuffer(sb.rumble);
	int enemy_score = 100;
	int enemy_respawn_time = 8;

	/* enemy update */
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].sprite.setTexture(&t.enemy);// �����͸� �Ѱ��ֱ� ������ �ּҰ� �Ѱ��ֱ�
		enemy[i].sprite.setSize(Vector2f(70, 70));// �� ũ��
		enemy[i].sprite.setPosition(rand()%300+W_WIDTH*0.9, rand() % 380);// ���� ȭ���� 90%���� ������ ����
		enemy[i].life = 1;// ���� ����
		enemy[i].speed = -(rand() % 5 + 1);// �������� �־����� ���� �ӵ�
	}

	// item�� ���� Ư��
	struct Item item[ITEM_NUM];
	item[0].sprite.setTexture(&t.item_speed);// �̼� �̹��� �ּ� ����
	item[0].delay = 25000;// 25�ʸ��� �̼� ������ ����
	item[1].sprite.setTexture(&t.item_delay);// ���� �̹��� �ּ� ����
	item[1].delay = 20000;// 20�ʸ��� ���� ������ ����

	for (int i = 0; i < ITEM_NUM; i++)
	{
		// item�� ���� Ư��
		item[0].sprite.setSize(Vector2f(70,70));
		item[0].is_presented = 0;
		item[0].presented_time = 0;// �������� ���� ���� ����
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
			case Event::Closed://������
				window.close();//������â�� ����
				break;
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
		// �Ѿ� �߻�
		printf("bullet_idx %d\n", bullet_idx);
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			// delay�� Ŭ �� �۵� ( ���� �ð��� �߻� �ð��� 0.5�ʸ�ŭ�� ���̰� ���� �Ѿ� �߻�)
			if (spent_time - fired_time > bullet_delay)
			{
				//�Ѿ��� �߻� �Ǿ����� �ʴٸ� �Ѿ� �߻�
				if (!bullet[bullet_idx].is_fired)
				{
					bullet[bullet_idx].sprite.setPosition(player.x + 110, player.y + 20);// �Ѿ� �ʱ� ��ġ (�ӽ� �׽�Ʈ)
					bullet[bullet_idx].is_fired = 1;
					bullet_idx++;// ���� �Ѿ� �߻� �����ϵ���
					bullet_idx = bullet_idx % BULLET_NUM;// 50�� ��� idx�� 0���� �ٲ�
					bullet_sound.play();// �Ѿ� �߻� �Ҹ�
					fired_time = spent_time;// �Ѿ� ���� (���� �� �ڿ� ���� �� ������ ������ ������ ���Ͻ��� ��)
				}
			}
		}

		for (int i = 0; i < BULLET_NUM; i++)
		{
			if (bullet[i].is_fired) {
				bullet[i].sprite.move(bullet_speed, 0);
				if (bullet[i].sprite.getPosition().x > W_WIDTH)
					bullet[i].is_fired = 0;
			}
		}

		//enemy���� �浹
		//intersects : �÷��̾�� �� ���̿��� �������� �ִ°�
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			// 10�� ���� enemy�� ��
			if (spent_time % (1000 * enemy_respawn_time) < 1000 / 60 + 1) // 1�ʵ��� 60�������� �ݺ��Ǳ� ������
			{
				// ������ �������϶��� ���� ����
				if (!is_gameover)
				{
					enemy[i].sprite.setSize(Vector2f(70, 70));
					enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 505);// 90%���� ������ ����
					enemy[i].life = 1;
					// 10�ʸ��� enemy �ӵ� +1
					enemy[i].speed = -(rand() % 3 + 1 + (spent_time / 1000 / enemy_respawn_time));
				}
			}

			if (enemy[i].life > 0)
			{
				// enemy���� �浹
				if (is_collide(player.sprite, enemy[i].sprite) || is_collide(bullet[i].sprite, enemy[i].sprite))
				{
					enemy[i].life -= 1;//���� ���� ���̱�
					player.score += enemy_score;

					if (enemy[i].life == 0)
					{
						enemy_explosion_sound.play();
					}
				}

				// enemy�� x��ǥ�� 0�� �Ǹ�
				else if (enemy[i].sprite.getPosition().x < 0)
				{
					player.life -= 1;// player ��� 1 ����
					enemy[i].life = 0;// �� ���ֱ�
				}

				// �Ѿ˰� enemy�� �浹
				for (int j = 0; j < BULLET_NUM; j++)
				{
					if (is_collide(bullet[j].sprite, enemy[i].sprite))
					{
						if (bullet[j].is_fired)
						{
							enemy[i].life -= 1;
							player.score += enemy_score;

							if (enemy[i].life == 0)
							{
								enemy_explosion_sound.play();
							}
							bullet[j].is_fired = 0;
						}
					}
				}
				enemy[i].sprite.move(enemy[i].speed, 0);
			}
		}

		/* item update */
		// TODO : item[1]�� �� ��
		for (int i = 0; i < ITEM_NUM; i++)
		{
			if (!item[i].is_presented)
			{
				if (spent_time - item[i].presented_time > item[i].delay)
				{
					item[i].sprite.setPosition(rand() % (W_WIDTH) * 0.8, rand() % W_HEIGHT * 0.8);
					item[i].is_presented = 1;// �������� �� (true)
				}
			}
			if (item[i].is_presented)
			{

				// TODO : �浹 �� ������ ȿ���� �ְ� �������
			}
		}

		// ���� �ð��� ������ ����
		sprintf(info, "life: %d | score: %d | time: %d\n", player.life, player.score, spent_time/1000);

		text.setString(info);
		//ȭ���� ������ �ִ� ���� ��� �׷��� ��
		//draw�� ���߿� ȣ���Ҽ��� �켱������ ������

		//window.clear(Color::Black);//�÷��̾� ��ü ���� (��� �����)
		window.draw(bg_sprite);

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].life > 0)  window.draw(enemy[i].sprite);//�� �����ֱ�
		}
		if (item[0].is_presented)
			window.draw(item[0].sprite);
		window.draw(player.sprite);//�÷��̾� �����ֱ�(�׷��ֱ�)
		window.draw(text);

		// �߻�� �Ѿ˸� �׸���
		for (int i = 0; i < BULLET_NUM; i++)
		{
			if (bullet[i].is_fired)
				window.draw(bullet[i].sprite);
		}
		if (is_gameover)
		{
			window.draw(gameover_sprite);
			// TODO : ������ ���ߴ� ���� ������ ��
		}

		window.display();
	}

	return 0;
}