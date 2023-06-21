#include "TestScene.h"
#include "Ball.h"
#include "Player.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	for (int i = 1; i < 9; i++) {
		Ball* b =  Instantiate<Ball>(this);
		b->SetNumber(i);
		b->SetPosition((float)(i - 4) * 1.4f, 0, (float)(i - 4) * 1.4f);
	}
	Player* p = Instantiate<Player>(this);
	Ball* b = Instantiate<Ball>(this);
	b->SetPosition(-10.0f, 0.0f, 10.0f);
	b->SetNumber(0);		//����
	p->SetMyBall(b);
}

//�X�V
void TestScene::Update()
{
	//�{�[�����߂荞�񂾏ꍇ�̏���
	std::list<Ball*> balls = FindGameObjects<Ball>();
	for (auto itr1 = balls.begin(); itr1 != balls.end(); itr1++) {
		for (auto itr2 = itr1; itr2 != balls.end(); itr2++) {
			//�����{�[�����w���Ă���ꍇ�̓X�L�b�v
			if (itr1 == itr2) continue;
			//2�̃{�[���̈ʒu���ׂ�
			XMVECTOR distance = (*itr1)->GetPosition() - (*itr2)->GetPosition();
			if (Length(distance) < 1.0f * 2.0f) {		//�d�Ȃ��Ă���Ȃ��
				float depth = 1.0f * 2.0f - Length(distance);		//�߂荞��ł����
				//�߂荞��ł���ʂ̔����̗ʂ����ړ�������
				distance = XMVector3Normalize(distance) * depth / 2.0f;//�ړ��������
				(*itr1)->SetPosition((*itr1)->GetPosition() + distance);
				(*itr2)->SetPosition((*itr2)->GetPosition() - distance);
			}
		}
	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
