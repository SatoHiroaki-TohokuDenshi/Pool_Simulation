#pragma once
#include "Engine/GameObject.h"

//ReadyText���Ǘ�����N���X
class Ready : public GameObject {
private:
	int hPict_;    //�摜�ԍ�
public:
	//�R���X�g���N�^
	Ready(GameObject* parent);

	//�f�X�g���N�^
	~Ready();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//Ready�̃J�E���g���I����Ă��邩
	bool Finished();
};