#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace sf;

int main(void) {

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// ȭ�� ũ��, ����
	window.setFramerateLimit(60);// 60�ʸ��� �� ���� ���ư���

	// f : �Ҽ�
	// Vector2i : ����
	Vector2i mouse_pos;// ���콺 ��ǥ
	int click_cnt = 0;// ���콺 ���� Ƚ��

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);// ���콺 ��ǥ �ǽð����� �ޱ�

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			// �� �� ������ �� ���� ����
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Right)
				{
					click_cnt++;
				}
			}
		}

		//���콺 ��ġ�� �ϳ��ۿ� ����
		//������ ���ȴٸ�
		//���콺 ���� ���¸� ������ ������
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			click_cnt++;
		}

		printf("(%d, %d) Ŭ�� Ƚ�� : %d\n", mouse_pos.x, mouse_pos.y, click_cnt);// ���콺 x�� y�� ���
	}

	return 0;
}