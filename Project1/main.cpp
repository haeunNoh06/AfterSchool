#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {

	//640 x 480 ������ ȭ�� ����
	//��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
	RenderWindow window(VideoMode(640, 480), "AfterSchool");

	//�׸� ����� �÷��̾�
	RectangleShape player;
	player.setSize(Vector2f(40, 40));//�÷��̾� �׸� ũ��
	player.setPosition(100, 100);//�÷��̾� �⺻ x, y��ǥ
	player.setFillColor(Color::Red);//������ �׸�

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
		//ȭ���� ������ �ִ� ���� ��� �׷��� ��
		window.draw(player);//player �����ֱ�(�׷��ֱ�)
		window.display();
	}

	return 0;
}