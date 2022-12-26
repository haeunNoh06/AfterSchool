#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {

	//640 x 480 ������ ȭ�� ����
	//��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
	RenderWindow window(VideoMode(640, 480), "AfterSchool");
	window.setFramerateLimit(60);//1�ʿ� 60�� �����ش�. �÷��̾ ���� ���� �ʵ��� �ϱ�

	//�׸� ����� �÷��̾�
	RectangleShape player;
	player.setSize(Vector2f(40, 40));//�÷��̾� ������
	player.setPosition(100, 100);//�÷��̾� ���� ��ġ
	player.setFillColor(Color::Red);//�÷��̾� ����
	int player_speed = 5;//�÷��̾� �ӵ�


	RectangleShape enemy[5];//��
	int enemy_life[5];//���� ü��
	for (int i = 0; i < 5; i++)
	{
		enemy[i].setSize(Vector2f(70, 70));
		enemy[i].setPosition(500, 100 * i);
		enemy_life[i] = 1;
		enemy[i].setFillColor(Color::Yellow);//�� ����
	}


	//���� ��Ű�� �����? -> ���� �ݺ�
	while (window.isOpen()) //������â�� �����ִ� ���� ��� �ݺ�
	{ 
		Event event;//�̺�Ʈ ����
		while (window.pollEvent(event)) //�̺�Ʈ�� �߻�. �̺�Ʈ�� �߻��ؾ� event �ʱ�ȭ�� ��
		{
			switch (event.type)
			{
				//����(x)��ư�� ������ Event::Closed(0) 
			case Event::Closed ://������
				window.close();//������â�� ����
			}
		}

		//��� if�� �ؼ� ����Ű ��������
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.move(-1*player_speed, 0);//���� �̵�
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.move(0, -1 * player_speed);//���� �̵�
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.move(0, player_speed);//�Ʒ��� �̵�
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(player_speed, 0);//������ �̵�
		}

		//enemy���� �浹
		//intersects : �÷��̾�� �� ���̿��� �������� �ִ°�
		for (int i = 0; i < 5; i++)
		{
			if (enemy_life[i] > 0)
			{
				if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds()))
				{
					printf("enemy[%d]���� �浹\n", i);
					enemy_life[i] -= 1;//���� ���� ���̱�
				}
			}
		}

		window.clear(Color::Black);//�÷��̾� ��ü ���� (��� �����)

		for (int i = 0; i < 5; i++)
		{
			if (enemy_life[i] > 0)  window.draw(enemy[i]);//�� �����ֱ�
		}
		//ȭ���� ������ �ִ� ���� ��� �׷��� ��
		//draw�� ���߿� ȣ���Ҽ��� �켱������ ������
		window.draw(player);//�÷��̾� �����ֱ�(�׷��ֱ�)

		window.display();
	}

	return 0;
}