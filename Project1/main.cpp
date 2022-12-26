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
	player.setSize(Vector2f(40, 40));//�÷��̾� �׸� ũ��
	player.setPosition(100, 100);//�÷��̾� �⺻ x, y��ǥ
	player.setFillColor(Color::Red);//������ �׸�

	int player_speed = 5;//�÷��̾� �ӵ�


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

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.move(-1*player_speed, 0);//���� �̵�
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.move(0, -1 * player_speed);//���� �̵�
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.move(0, player_speed);//�Ʒ��� �̵�
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(player_speed, 0);//������ �̵�
		}

		window.clear(Color::Black);//�÷��̾� ��ü ���� (��� �����)


		//ȭ���� ������ �ִ� ���� ��� �׷��� ��
		window.draw(player);//player �����ֱ�(�׷��ֱ�)
		window.display();
	}

	return 0;
}