#include <stdio.h>
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


	RectangleShape enemy;//��
	enemy.setSize(Vector2f(70, 70));//�� ������
	enemy.setPosition(500, 300);//�� ���� ��ġ
	enemy.setFillColor(Color::Yellow);//�� ����


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

		window.clear(Color::Black);//�÷��̾� ��ü ���� (��� �����)


		//ȭ���� ������ �ִ� ���� ��� �׷��� ��
		//draw�� ���߿� ȣ���Ҽ��� �켱������ ������
		window.draw(player);//�÷��̾� �����ֱ�(�׷��ֱ�)
		window.draw(enemy);//�� �����ֱ�

		window.display();
	}

	return 0;
}