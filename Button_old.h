/*
#pragma once
#include <vector>
#include <string>
#include "Engine/GameObject.h"

//Buttonを管理するクラス
class Button : public GameObject
{
private:
    std::vector<int> hPict_;
    bool isHover_;
    XMFLOAT3 center_;
    XMFLOAT3 size_;
public:
    //コンストラクタ
    Button(GameObject* parent);

    //デストラクタ
    ~Button();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

public:
    void LoadFile(std::string fileName);
    void SetPosition(int x, int y);
    void Hovered(bool hovered);

    bool MouseInArea(XMFLOAT3 mousePos);
};
*/