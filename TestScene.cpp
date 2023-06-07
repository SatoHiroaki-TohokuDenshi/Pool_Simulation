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
	b->SetNumber(0);		//����
	p->SetMyBall(b);
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
