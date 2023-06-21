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
    if (hModel_ >= 0) {
        Model::Release(hModel_);
    }
}

//初期化
void Ball::Initialize()
{
}

//更新
void Ball::Update()
{
    //移動速度を計算する
    CalcVeloCity();

    //ボール同士の反射
    std::list<Ball*> all = GetParent()->FindGameObjects<Ball>();
    for (std::list<Ball*>::iterator itr = all.begin(); itr != all.end(); itr++) {
        if (*itr == this) continue;
        XMFLOAT3 next = transform_.position_ + velocity_;   //次のフレームの自分
        XMFLOAT3 other = (*itr)->GetNextPosition();         //次のフレームの相手
        //2個の玉の距離が玉の直径より短い
        if (Length(next - other) < 1.0f * 2.0f) {
            //相手に力を加える
            XMVECTOR n = other - next;
            n = XMVector3Normalize(n);      //nの長さを1にする
            XMVECTOR powDot = XMVector3Dot(velocity_, n);
            float pow = XMVectorGetX(powDot);   //押す力の大きさ
            XMVECTOR push = n * pow;
            velocity_ -= push;
            (*itr)->AddForce(push);

            //相手から力を受け取る
            n = next - other;
            n = XMVector3Normalize(n);      //nの長さを1にする
            powDot = XMVector3Dot(velocity_, n);
            pow = XMVectorGetX(powDot);     //押す力の大きさ
            push = n * pow;
            (*itr)->AddForce(-push);        //相手から引く
            this->AddForce(push);           //自分に加える


        }
    }
    
    //壁との反射を計算する
    CalcReflectWall();



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

//移動速度の計算
void Ball::CalcVeloCity() {
    //velocity_の長さを求める
    float len = Length(velocity_);
    //短くする（減速）
    len -= 0.001f;
    if (len < 0.0f) len = 0.0f;
    //単位ベクトルに長さの情報を加える
    velocity_ = XMVector3Normalize(velocity_) * len;
}

//壁の反射を計算する
void Ball::CalcReflectWall() {
    XMVECTOR n = XMVectorSet(-1, 0, 0, 0);     //壁の法線ベクトル
    XMFLOAT3 nextPos = transform_.position_ + velocity_;
    if (nextPos.x >= 30.0f) {
        n = XMVectorSet(-1,0,0,0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
    if (nextPos.x <= -30.0f) {
        n = XMVectorSet( 1, 0, 0, 0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
    if (nextPos.z >= 20.0f) {
        n = XMVectorSet( 0, 0, -1, 0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
    if (nextPos.z <= -20.0f) {
        n = XMVectorSet( 0, 0,  1, 0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
}

//反射するベクトルを計算する
//引数　：法線ベクトル
//戻り値：反射したベクトル
XMVECTOR Ball::CalcReflection(XMVECTOR Nomal) {
    XMVECTOR ipvec = XMVector3Dot(velocity_, Nomal);
    float ip = XMVectorGetX(ipvec);         //壁を押す力の大きさ
    XMVECTOR push = Nomal * ip;             //壁を押すベクトル
    XMVECTOR through = velocity_ - push;    //壁に沿ったベクトル
    push *= -1;                             //押し返されるベクトル
    return (push + through);                //反射するベクトル
}