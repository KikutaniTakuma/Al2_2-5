#pragma once

class Frame {
public:
	Frame(void);

public:
	// �t���[��
	unsigned long long frame;

public:
	// �X�^�[�g�t���O
	bool startFlag;

	// �X�^�[�g�֐�
	void Start(void);

	// ��~
	void Pause(void);

	// �X�g�b�v
	void Stop(void);

	// ���X�^�[�g
	void Restart(void);

	int operator%(int num);
};