/*
* Exercise 5.21
* Author: sesiria  2018
* spell checking programm
* 1) load two dictionary system and user defined.
* 2) check a input stream of characters.
* 3) output: a list of words with the following
*   add one character.
*   remove one character.
*   exchange adjacent characters.
*  Note!:
*  1) You must configure the path of the dictionary as:
*  const string dicPath = "../Data/dict.txt"; // configure the path for the dictionary.
*  2) Due to the dictionary will cost a lot of memory. when you using the standard cout for tracking and debugging in VSCODE the process will be crashed.
*  but running this program in the command mode is OK!.
*/

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

using namespace std;

const string dicPath = "d://dict.txt"; // configure the path for the dictionary.

// singleton pattern.
class SpellChecker
{
public:
	static SpellChecker *getInstance()
	{
		if (m_pInst == nullptr)
		{
			m_pInst = new SpellChecker();
		}
		return m_pInst;
	}

	void testAdjacentTable()
	{
		cout << "adjacentTable size " << m_AdjacentDict.size() << endl;
		auto iter = m_AdjacentDict.begin();
		cout << iter->first << ":\t";
		printWordList(iter->second, 10);
	}

	bool checkSpell(const string & word)
	{
		bool bRet = (m_dictionary.find(word) == m_dictionary.end());
		if (bRet) {
			cout << word << " is not found in dictionary" << endl;
			printRecommendation(word);
		}
		else {
			cout << word << " is in dictionary" << endl;
		}
		cout << "***********************************" << endl;
		return bRet;
	}

	void printRecommendation(const string &word)
	{
		// print the recommend words add one character.
		auto iter = m_AdjacentDict.find(word);
		if (iter != m_AdjacentDict.end()) // found recommand
		{
			// only print max recommands.
			cout << "recommendation : add one character" << endl;
			printWordList(iter->second, maxRecommand);
		}

		// recommendation add one character.
		int nCount = 0;
		for (int i = 0; i < word.size(); ++i)
		{
			string cut = word;
			cut.erase(i, 1);
			if (m_dictionary.find(cut) != m_dictionary.end())
			{
				if (nCount == 0)
					cout << "recommendation : move one character\n" << cut;
				else
					cout << ", " << cut;
				++nCount;
			}
		}
		if (nCount > 0)
			cout << endl;

		// recommendation exchange adjacent characters.
		nCount = 0;
		for (int i = 0; i < word.size() - 1; ++i)
		{
			string exchange = word;
			std::swap(exchange[i], exchange[i + 1]);
			auto iter = m_dictionary.find(exchange);
			if (iter != m_dictionary.end())
			{
				if (nCount == 0)
					cout << "recommendation : exchange adjacent character\n" << exchange;
				else
					cout << ", " << exchange;
				++nCount;
			}
		}
		if (nCount > 0)
			cout << endl;
	}

private:
	static SpellChecker *m_pInst;
	vector<string> m_vecDict;
	unordered_set<string> m_dictionary;
	unordered_map<string, set<string>> m_AdjacentDict;

	const unsigned maxRecommand = 255;

	SpellChecker()
	{
		if (loadDictionary()) {
			buildHashTable();
			buildPatternTable();
		}

	}

	bool loadDictionary()
	{
		ifstream in;
		in.open(dicPath, std::ios::in | std::ios::binary);

		if (!in.is_open())
		{
			cout << "Error opening file";
			return false;
		}

		// load words
		string line;
		string word;
		while (getline(in, line)) {
			stringstream ssr(line);
			ssr >> word;
			if (word.size() > 0)
				m_vecDict.push_back(word);
		}

		cout << m_vecDict.size() << " words loaded" << endl;
		return true;
	}

	void buildHashTable()
	{
		for (auto & word : m_vecDict)
			m_dictionary.insert(word);

		cout << m_dictionary.size() << " words have been builded into hashTable" << endl;
	}

	// build pattern with the same length
	void buildPatternTable()
	{
		unordered_map<string, set<string>> adjWords;

		int nline = 0;
		for (auto &word : m_vecDict)
		{
			++nline;
			if (word.length() < 2)
				continue;
			for (int i = 0; i < word.length(); ++i)
			{
				string rep = word;
				rep.erase(i, 1);
				adjWords[rep].insert(word);
			}
		}
		m_AdjacentDict = std::move(adjWords);
	}

	void printWordList(const set<string> & list, int limits)
	{
		int nCount = 0;
		for (auto &words : list) {
			if (nCount >= limits)
				break;
			if (nCount > 0)
				cout << ", ";
			cout << words;
			++nCount;
		}
		cout << endl;
	}
};

SpellChecker *SpellChecker::m_pInst = nullptr;

int main()
{
	vector<string> list = { "wors", "wokr", "sql", "tdisk", "corect" };
	SpellChecker::getInstance();
	for (auto &word : list)
		SpellChecker::getInstance()->checkSpell(word);
	system("pause");
	return 0;
}