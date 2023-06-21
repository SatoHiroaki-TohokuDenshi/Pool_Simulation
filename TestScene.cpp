#include "TestScene.h"
#include "Ball.h"
#include "Player.h"
#include "Engine/Camera.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
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
	b->SetNumber(0);		//白玉
	p->SetMyBall(b);
}

//更新
void TestScene::Update()
{
	//ボールがめり込んだ場合の処理
	std::list<Ball*> balls = FindGameObjects<Ball>();
	for (auto itr1 = balls.begin(); itr1 != balls.end(); itr1++) {
		for (auto itr2 = itr1; itr2 != balls.end(); itr2++) {
			//同じボールを指している場合はスキップ
			if (itr1 == itr2) continue;
			//2個のボールの位置を比べる
			XMVECTOR distance = (*itr1)->GetPosition() - (*itr2)->GetPosition();
			if (Length(distance) < 1.0f * 2.0f) {		//重なっているならば
				float depth = 1.0f * 2.0f - Length(distance);		//めり込んでいる量
				//めり込んでいる量の半分の量だけ移動させる
				distance = XMVector3Normalize(distance) * depth / 2.0f;//移動させる量
				(*itr1)->SetPosition((*itr1)->GetPosition() + distance);
				(*itr2)->SetPosition((*itr2)->GetPosition() - distance);
			}
		}
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
