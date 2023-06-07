#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Ball : public GameObject
{
    int hModel_;    //���f���ԍ�
    int number_;    //�{�[���̔ԍ�(1�`9)���ʂ�0
    XMVECTOR velocity_;     //�ړ����x
public:
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�{�[���̔ԍ����w�肷��
    void SetNumber(int no);
};