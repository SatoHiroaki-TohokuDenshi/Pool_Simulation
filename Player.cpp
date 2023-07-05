#include "Player.h"
#include "Ball.h"
#include "Ready.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

namespace {
    const float GAUGE_TIME = 0.5f;
}

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), myBall_(nullptr), direction_(0.0f), power_(0.1f)
     ,hModel_(-1), isPull_(false), pullBegin_(0.0f, 0.0f, 0.0f), pullEnd_(0.0f, 0.0f, 0.0)
     ,state_(S_ROTATE), chargeLv_(0.0f), pGauge(nullptr), isCountUp_(true), isOperate_(true)
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
    pGauge->DoDraw(false);
    pGauge->SetPosition(-0.95f, 0.85f);
    pGauge->SetValue(chargeLv_);
}

//更新
void Player::Update()
{
    Ready* pReady = (Ready*)FindObject("Ready");
    if (pReady != nullptr && pReady->Finished())
        return;
    //通常の入力
    {
        //if (!isCharge_) {
        //    if (Input::IsKey(DIK_A)) {
        //        direction_ -= 0.03f;
        //    }
        //    if (Input::IsKey(DIK_D)) {
        //        direction_ += 0.03f;
        //    }
        //}
        if (Input::IsKeyDown(DIK_SPACE)) {
            //玉を発射する
            XMVECTOR base = XMVectorSet(0, 0, power_, 0);   //移動量のスカラー
            XMMATRIX yrot = XMMatrixRotationY(direction_);  //回転行列
            XMVECTOR v = XMVector3Transform(base, yrot);    //スカラー値に方向をつける
            myBall_->AddForce(v);
        }
    }

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

        if (Input::IsKeyDown(DIK_RETURN)) {
            isOperate_ = false;
            pGauge->DoDraw(true);
            pGauge->SetValue(0.0f);
            state_ = S_POWER;
        }
        break;
    case S_POWER:
        //角度決定に戻る
        if (Input::IsKeyDown(DIK_ESCAPE)) {
            isOperate_ = true;
            pGauge->DoDraw(false);
            state_ = S_ROTATE;
        }
        if (isCountUp_) {
            chargeLv_ = 0.01f;
            pGauge->AddValue(pGauge->MAX / GAUGE_TIME / 60.0f);
            if (pGauge->GetValue() >= pGauge->MAX) isCountUp_ = false;
        }
        else {
            chargeLv_ = -0.01f;
            pGauge->AddValue(-(pGauge->MAX / GAUGE_TIME / 60.0f));
            if (pGauge->GetValue() <= pGauge->MIN) isCountUp_ = true;
        }

        //打ち出す
        if (Input::IsKeyDown(DIK_RETURN)) {
            chargeLv_ = pGauge->GetValue();
            if (abs(pGauge->MAX - pGauge->GetValue()) == 0.1) chargeLv_ = 2.0f;   //スーパーショット
            XMVECTOR base = XMVectorSet(0, 0, power_ + chargeLv_, 0);   //移動量のスカラー
            XMMATRIX yrot = XMMatrixRotationY(direction_);  //回転行列
            XMVECTOR v = XMVector3Transform(base, yrot);    //スカラー値に方向をつける
            myBall_->AddForce(v);
            chargeLv_ = 0.0f;
            pGauge->DoDraw(false);
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
        if (flag) {
            isOperate_ = true;
            state_ = S_ROTATE;
        }
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

    if (isOperate_) {
        Model::SetTransform(hModel_, transform_);
        Model::Draw(hModel_);
    }
}

//開放
void Player::Release()
{
}