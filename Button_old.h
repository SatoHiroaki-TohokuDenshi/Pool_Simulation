/*
#pragma once
#include <vector>
#include <string>
#include "Engine/GameObject.h"

//Button���Ǘ�����N���X
class Button : public GameObject
{
private:
    std::vector<int> hPict_;
    bool isHover_;
    XMFLOAT3 center_;
    XMFLOAT3 size_;
public:
    //�R���X�g���N�^
    Button(GameObject* parent);

    //�f�X�g���N�^
    ~Button();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

public:
    void LoadFile(std::string fileName);
    void SetPosition(int x, int y);
    void Hovered(bool hovered);

    bool MouseInArea(XMFLOAT3 mousePos);
};
*/