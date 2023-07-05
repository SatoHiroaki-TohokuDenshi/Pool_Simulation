#pragma once
#include "Engine/GameObject.h"

//Ballを管理するクラス
class Ball : public GameObject
{
    int hModel_;    //モデル番号
    int number_;    //ボールの番号(1～9)白玉は0
    XMVECTOR velocity_;     //移動速度
public:
    //コンストラクタ
    Ball(GameObject* parent);

    //デストラクタ
    ~Ball();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //ボールの番号を指定する
    void SetNumber(int no);

    //移動速度の計算
    void CalcVeloCity();

    //壁の反射を計算する
    void CalcReflectWall();

    //反射するベクトルを計算する
    //引数　：法線ベクトル
    //戻り値：反射したベクトル
    XMVECTOR CalcReflection(XMVECTOR Nomal);

    //ボールに力を加える
    void AddForce(XMVECTOR f);

    //次のフレームにいる座標を返す
    XMFLOAT3 GetNextPosition() { return GetPosition() + velocity_; };

    //移動量のゲッター関数
    XMVECTOR GetVelocity() { return velocity_; };

    bool IsMoving() { return (Length(velocity_) == 0.0f); };
};