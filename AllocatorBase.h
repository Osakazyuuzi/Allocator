/////////////////////////////////////////////////////////////////////////
// �t�@�C�����FAllocator.h
/////////////////////////////////////////////////////////////////////////
#ifndef ___CORESYSTEM_ALLOCATOR_H___
#define ___CORESYSTEM_ALLOCATOR_H___

/////////////////
// �C���N���[�h //
/////////////////
#include <memory>

class Allocator {
public:

	/*
	[�֐��T�v]
	���������m�ۂ���

	[����]
	std::size_t		size		�o�C�g��
	const char*		typeName	�m�ۂ���^���i�f�o�b�O�p�j
	const char*		fileName	�Ăяo�����t�@�C�����i�f�o�b�O�p�j
	int				line		�Ăяo�����s���i�f�o�b�O�p�j

	[�߂�l]
	void*			�m�ۂ����������u���b�N�̐擪
	*/
	virtual void* Allocate(std::size_t size, const char* typeName, const char* fileName, int line) = 0;

	/*
	[�֐��T�v]
	���������J������

	[����]
	void*			ptr			�J�����郁�����|�C���^
	*/
	virtual void Deallocate(void* ptr) = 0;

	/*
	[�֐��T�v]
	�C�ӂ̌^�̕ϐ����쐬���A����std::unique_ptr��Ԃ�

	[�e���v���[�g����]
	T			�^
	TArgs		�R���X�g���N�^�̈���
	
	[����]
	const char*		fileName	�t�@�C�����i�f�o�b�O�p�j
	int				line		�s���i�f�o�b�O�p�j
	*/
	template <typename T, typename... TArgs>
	std::unique_ptr<T> Make(const char* fileName, int line, TArgs... args) {

		// �^�̃T�C�Y���̃������e�ʂ��m�ۂ��ă������u���b�N�̃A�h���X���|�C���^���擾����
		void* memory = Allocate(sizeof(T), typeid(T).name(), fileName, line);

		// �������e�ʂ��m�ۂł��Ȃ������ꍇ
		if (!memory) {
			// �������m�ێ��s���̗�O���X���[����
			throw std::bad_alloc();
		}

		// �m�ۂ����������Ƀv���[�X�����gnew�Œ��ڍ\�z����
		return std::unique_ptr<T>(new(memory) T(std::forward<TArgs>(args)...));
	}
};

#endif //!___CORESYSTEM_ALLOCATOR_H___