#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {

	//640 x 480 ������ ȭ�� ����
	//��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
	RenderWindow window(VideoMode(640, 480), "AfterSchool");

	//���� ��Ű�� �����? -> ���� �ݺ�
	while (window.isOpen()) { //������â�� �����ִ� ���� ��� �ݺ�
		
		Event event;//�̺�Ʈ ����
		while (window.pollEvent(event)) {//�̺�Ʈ�� �߻�. �̺�Ʈ�� �߻��ؾ� event �ʱ�ȭ�� ��
			//����(x)��ư�� ������
			if (event.type == Event::Closed)//Event::Closed��� �̺�Ʈ�� �߻��ϸ�
				window.close();//������â�� ����
		}

	}

	printf("Hello World");

	return 0;
}