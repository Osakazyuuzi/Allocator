/////////////////////////////////////////////////////////////////////////
// ファイル名：Allocator.h
/////////////////////////////////////////////////////////////////////////
#ifndef ___CORESYSTEM_ALLOCATOR_H___
#define ___CORESYSTEM_ALLOCATOR_H___

/////////////////
// インクルード //
/////////////////
#include <memory>

class Allocator {
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
	virtual void* Allocate(std::size_t size, const char* typeName, const char* fileName, int line) = 0;

	/*
	[関数概要]
	メモリを開放する

	[引数]
	void*			ptr			開放するメモリポインタ
	*/
	virtual void Deallocate(void* ptr) = 0;

	/*
	[関数概要]
	任意の型の変数を作成し、そのstd::unique_ptrを返す

	[テンプレート引数]
	T			型
	TArgs		コンストラクタの引数
	
	[引数]
	const char*		fileName	ファイル名（デバッグ用）
	int				line		行数（デバッグ用）
	*/
	template <typename T, typename... TArgs>
	std::unique_ptr<T> Make(const char* fileName, int line, TArgs... args) {

		// 型のサイズ分のメモリ容量を確保してメモリブロックのアドレスをポインタを取得する
		void* memory = Allocate(sizeof(T), typeid(T).name(), fileName, line);

		// メモリ容量が確保できなかった場合
		if (!memory) {
			// メモリ確保失敗時の例外をスローする
			throw std::bad_alloc();
		}

		// 確保したメモリにプレースメントnewで直接構築する
		return std::unique_ptr<T>(new(memory) T(std::forward<TArgs>(args)...));
	}
};

#endif //!___CORESYSTEM_ALLOCATOR_H___