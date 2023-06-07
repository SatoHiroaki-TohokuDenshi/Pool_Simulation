#include "Player.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), myBall_(nullptr), direction_(0.0f), power_(0.1f)
     ,hModel_(-1)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    transform_.scale_.x *= 0.3f;
    transform_.scale_.y *= 0.3f;
    transform_.scale_.z *= 0.3f;
    //モデルデータのロード
    hModel_ = Model::Load("no0.fbx");
    assert(hModel_ >= 0);
}

//更新
void Player::Update()
{
    if (Input::IsKey(DIK_A)) {
        direction_ -= 0.03f;
    }
    if (Input::IsKey(DIK_D)) {
        direction_ += 0.03f;
    }
    if (Input::IsKeyDown(DIK_SPACE)) {
        //玉を発射する
        XMVECTOR base = XMVectorSet(0, 0, power_, 0);   //移動量のスカラー
        XMMATRIX yrot = XMMatrixRotationY(direction_);  //回転行列
        XMVECTOR v = XMVector3Transform(base, yrot);    //スカラー値に方向をつける
        myBall_->AddForce(v);
    }
}

//描画
void Player::Draw()
{
    if (hModel_ < 0)
        return;
    XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);     //移動量のスカラー
    XMMATRIX yrot = XMMatrixRotationY(direction_);  //回転行列
    XMVECTOR v = XMVector3Transform(base, yrot);    //スカラー値に方向をつける
    transform_.position_ = myBall_->GetPosition() + v;

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}