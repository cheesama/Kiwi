#pragma once

struct KForm;
struct KMorpheme;
struct KChunk
{
	union 
	{
		const KForm* form;
		struct
		{
			unsigned short _;
			unsigned char begin;
			unsigned char end;
		};
	};

	KChunk(const KForm* _form) : form(_form) {  }
	KChunk(unsigned char _begin, unsigned char _end) : _(0xFFFF), begin(_begin), end(_end) {}
	const KMorpheme* getMorpheme(size_t idx, KMorpheme* tmp, const char* ostr) const;
	size_t getCandSize() const;
	bool isStr() const { return _ == 0xFFFF; }
};

struct KTrie
{
#ifdef  _DEBUG
	static int rootID;
	int id;
	char currentChar = 0;
#endif //  _DEBUG

	KTrie* next[51] = {nullptr,};
	KTrie* fail = nullptr;
	const KForm* exit = nullptr;
	KTrie();
	~KTrie();
	void build(const char* str, const KForm* form);
	KTrie* findFail(char i) const;
	void fillFail();
	const KForm* search(const char* begin, const char* end) const;
	vector<pair<const KForm*, int>> searchAllPatterns(const string& str) const;
	vector<vector<KChunk>> split(const string& str, bool hasPrefix = false) const;
};

