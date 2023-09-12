/////////////////////////////////////////////////////////////////////////
// �t�@�C�����FHeapAllocator.h
/////////////////////////////////////////////////////////////////////////
#ifndef ___CORESYSTEM_HEAPALLOCATOR_H___
#define ___CORESYSTEM_HEAPALLOCATOR_H___

/////////////////
// �C���N���[�h //
/////////////////
#include <iostream>

//////////////////////////
// �I���W�i���C���N���[�h //
//////////////////////////
#include "AllocatorBase.h"

class HeapAllocator : public AllocatorBase {
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
	void* Allocate(std::size_t size, const char* typeName, const char* fileName, int line) override {

		// size�����������m�ۂ��ăA�h���X���擾����
		void* memory = std::malloc(size);

		// �������e�ʂ��m�ۂł��Ȃ������ꍇ
		if (!memory) {
			// �G���[���b�Z�[�W���R���\�[���ɏo�͂���
			std::cerr << "Failed to allocate: "
				<< "\nType: " << typeName
				<< "\nFile: " << fileName
				<< "\nLine: " << line << std::endl;
			
			// �������m�ێ��s���̗�O���X���[����
			throw std::bad_alloc();
		}
		return memory;
	}

	/*
	[�֐��T�v]
	���������J������

	[����]
	void*			ptr			�J�����郁�����|�C���^
	*/
	void Deallocate(void* ptr) override {
		// ���������J������
		std::free(ptr);
	}
};

#endif //!___CORESYSTEM_HEAPALLOCATOR_H___