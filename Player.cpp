#include "Player.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), myBall_(nullptr), direction_(0.0f), power_(0.1f)
     ,hModel_(-1), isPull_(false), pullBegin_(0.0f, 0.0f, 0.0f), pullEnd_(0.0f, 0.0f, 0.0)
     ,state_(S_ROTATE), chargeMax_(1.0f), chargeLv_(0.0f), pGauge(nullptr), isCharge_(false), isCountUp(true)
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

    pGauge = Instantiate<Gauge>(this);
    pGauge->SetValue(chargeMax_, chargeLv_);
}

//更新
void Player::Update()
{
    //通常の入力
    //if (!isCharge_) {
    //    if (Input::IsKey(DIK_A)) {
    //        direction_ -= 0.03f;
    //    }
    //    if (Input::IsKey(DIK_D)) {
    //        direction_ += 0.03f;
    //    }
    //}
    //if (Input::IsKeyDown(DIK_SPACE)) {
    //    //玉を発射する
    //    XMVECTOR base = XMVectorSet(0, 0, power_, 0);   //移動量のスカラー
    //    XMMATRIX yrot = XMMatrixRotationY(direction_);  //回転行列
    //    XMVECTOR v = XMVector3Transform(base, yrot);    //スカラー値に方向をつける
    //    myBall_->AddForce(v);
    //}

    //任意の操作方法
    //モンスト風
    //マウスのクリックで入力開始
    //引っ張って離すと反対向きに発射
    {
        if (!isPull_) {
            if (Input::IsMouseButtonDown(0)) {
                isPull_ = true;
                pullBegin_.x = Input::GetMousePosition().x;
                pullBegin_.z = Input::GetMousePosition().y;
            }
        }
        else {
            if (Input::IsMouseButtonUp(0)) {
                isPull_ = false;
                pullEnd_.x = Input::GetMousePosition().x;
                pullEnd_.z = Input::GetMousePosition().y;
                direction_ = (float)atan2((double)(pullBegin_.x - pullEnd_.x),
                    (double)(pullEnd_.z - pullBegin_.z));
                XMVECTOR pullvec = pullBegin_ - pullEnd_;
                //pullvec = XMVector3Normalize(pullvec);
                power_ = Length(pullvec) / 300.0f;

                XMVECTOR base = XMVectorSet(0, 0, power_, 0);   //移動量のスカラー
                XMMATRIX yrot = XMMatrixRotationY(direction_);  //回転行列
                XMVECTOR v = XMVector3Transform(base, yrot);    //スカラー値に方向をつける
                myBall_->AddForce(v);
                power_ = 0.1f;
            }
            else {
                pullEnd_.x = Input::GetMousePosition().x;
                pullEnd_.z = Input::GetMousePosition().y;
                direction_ = (float)atan2((double)(pullBegin_.x - pullEnd_.x),
                    (double)(pullEnd_.z - pullBegin_.z));
            }
        }
    }

    //ゴルフ風
    //A/Dで方向を決定
    //Enterでパワーを溜める
    //0→満タン→0という風に推移する
    //ピッタリ満タンの場合はスーパーショット
    switch (state_) {
    case S_ROTATE:
        if (Input::IsKey(DIK_A)) direction_ -= 0.03f;
        if (Input::IsKey(DIK_D)) direction_ += 0.03f;
        if (Input::IsKeyDown(DIK_RETURN)) state_ = S_POWER;
        break;
    case S_POWER:
        //角度決定に戻る
        if (Input::IsKeyDown(DIK_ESCAPE)) state_ = S_ROTATE;
        if (chargeLv_ < -0.1f) isCountUp = true;
        else if (chargeLv_ >= chargeMax_) isCountUp = false;

        if (isCountUp) {
            chargeLv_ += 0.01f;
            pGauge->SetValue(chargeMax_, chargeLv_);
        }
        else {
            chargeLv_ -= 0.01f;
            pGauge->SetValue(chargeMax_, chargeLv_);
        }

        //打ち出す
        if (Input::IsKeyDown(DIK_RETURN)) {
            if (abs(chargeMax_ - chargeLv_) == 0.1) chargeLv_ = 2.0f;   //スーパーショット
            XMVECTOR base = XMVectorSet(0, 0, power_ + chargeLv_, 0);   //移動量のスカラー
            XMMATRIX yrot = XMMatrixRotationY(direction_);  //回転行列
            XMVECTOR v = XMVector3Transform(base, yrot);    //スカラー値に方向をつける
            myBall_->AddForce(v);
            chargeLv_ = 0.0f;
            state_ = S_MOVE;
        }
        break;
    case S_MOVE:
        std::list<Ball*> all = GetParent()->FindGameObjects<Ball>();
        bool flag = true;
        for (auto itr : all) {
            if ((*itr).IsMoving()) {
                flag = false;
                break;
            }
        }
        if (flag) state_ = S_ROTATE;
        break;
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