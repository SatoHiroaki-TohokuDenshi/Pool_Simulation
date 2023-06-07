#include "Ball.h"
#include "Engine/Model.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1), number_(-1)
{
    velocity_ = XMVectorSet(0, 0, 0, 0);
}

//デストラクタ
Ball::~Ball() {
}

//初期化
void Ball::Initialize()
{
    if (hModel_ >= 0) {
        Model::Release(hModel_);
    }
}

//更新
void Ball::Update()
{
    //velocity_の長さを求める
    float len = Length(velocity_);
    //短くする（減速）
    len -= 0.001f;
    //単位ベクトルに長さの情報を加える
    velocity_ = XMVector3Normalize(velocity_) * len;

    //移動
    transform_.position_ += velocity_;
}

//描画
void Ball::Draw()
{
    if (hModel_ < 0)
        return;

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ball::Release()
{
}

//ボールの番号を指定する
void Ball::SetNumber(int no)
{
    number_ = no;
    //モデルデータのロード
    std::string fileName = "no" + std::to_string(number_) + ".fbx";
    hModel_ = Model::Load(fileName);
    assert(hModel_ >= 0);
}

//ボールに力を加える
void Ball::AddForce(XMVECTOR f)
{
    velocity_ += f;
}