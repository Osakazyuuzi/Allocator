/////////////////////////////////////////////////////////////////////////
// ファイル名：HeapAllocator.h
/////////////////////////////////////////////////////////////////////////
#ifndef ___CORESYSTEM_HEAPALLOCATOR_H___
#define ___CORESYSTEM_HEAPALLOCATOR_H___

/////////////////
// インクルード //
/////////////////
#include <iostream>

//////////////////////////
// オリジナルインクルード //
//////////////////////////
#include "AllocatorBase.h"

class HeapAllocator : public AllocatorBase {
public:

	/*
	[関数概要]
	メモリを確保する

	[引数]
	std::size_t		size		バイト数
	const char*		typeName	確保する型名（デバッグ用）
	const char*		fileName	呼び出したファイル名（デバッグ用）
	int				line		呼び出した行数（デバッグ用）

	[戻り値]
	void*			確保したメモリブロックの先頭
	*/
	void* Allocate(std::size_t size, const char* typeName, const char* fileName, int line) override {

		// size分メモリを確保してアドレスを取得する
		void* memory = std::malloc(size);

		// メモリ容量が確保できなかった場合
		if (!memory) {
			// エラーメッセージをコンソールに出力する
			std::cerr << "Failed to allocate: "
				<< "\nType: " << typeName
				<< "\nFile: " << fileName
				<< "\nLine: " << line << std::endl;
			
			// メモリ確保失敗時の例外をスローする
			throw std::bad_alloc();
		}
		return memory;
	}

	/*
	[関数概要]
	メモリを開放する

	[引数]
	void*			ptr			開放するメモリポインタ
	*/
	void Deallocate(void* ptr) override {
		// メモリを開放する
		std::free(ptr);
	}
};

#endif //!___CORESYSTEM_HEAPALLOCATOR_H___