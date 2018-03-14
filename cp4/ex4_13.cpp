/*
* Exercise 4.51
* Author: sesiria  2018
* generate the index for a book.
* this problem could be resolved by regex expression which is more efficient.
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Property
{
	int pageNum;
	bool isExpanded;
};

class Entry
{
public:
	Entry(const std::string &entryName, bool bRange = false)
		: name(entryName), isRange(bRange)
	{
	}

	Entry(const Entry &rhs)
		: name(rhs.name), isRange(rhs.isRange), pageNum(rhs.pageNum)
	{
	}

	Entry(Entry &&rhs)
		: name(std::move(rhs.name)), isRange(std::move(rhs.isRange)), pageNum(std::move(rhs.pageNum))
	{
	}

	~Entry()
	{
		/*for(auto &x : children)
		delete x.second;*/
	}

	Entry &operator=(const Entry &rhs)
	{
		Entry copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	Entry &operator=(Entry &&rhs)
	{
		std::swap(name, rhs.name);
		std::swap(isRange, rhs.isRange);
		std::swap(pageNum, rhs.pageNum);
		std::swap(children, rhs.children);
		return *this;
	}


	void setRange(bool bRange)
	{
		this->isRange = bRange;
	}

	void addPageNum(int nPage)
	{
		pageNum.insert(nPage);
	}

	void printEntry()
	{
		printEntry(0);
	}

	void printChildren()
	{
		for (auto &x : children)
			x.second.printEntry(0);
	}

	void appendChild(const std::vector<std::string> &vec, const Property &prop)
	{
		std::map<std::string, Entry>::iterator iter;
		for (int i = 0; i < vec.size(); ++i)
		{
			if (i == 0)
			{
				if ((iter = children.find(vec[i])) == children.end()) // can't find the entry
				{
					children.insert(std::make_pair(vec[i],  Entry{vec[i], false})); // insert the entry.
					iter = children.find(vec[i]);
				}
			}
			else
			{
				Entry & current = iter->second;
				if ((iter = current.children.find(vec[i])) == current.children.end())
				{
					current.children.insert(std::make_pair(vec[i], Entry{ vec[i], false }));
					iter = current.children.find(vec[i]);
				}
			}
		}
		iter->second.setRange(prop.isExpanded);
		iter->second.addPageNum(prop.pageNum);
	}

private:
	std::string name;
	bool isRange;
	std::set<int> pageNum;
	std::map<std::string, Entry> children;

	void printEntry(int depth) const
	{
		for (int i = 0; i < depth; ++i)
			std::cout << "\t";

		std::cout << name << ": ";

		int i = 0;
		for (auto iter = pageNum.begin(); iter != pageNum.end(); ++iter)
		{
			if (i > 0)
				std::cout << ((isRange) ? "-" : ", ");
			std::cout << *iter;
			++i;
		}
		std::cout << std::endl;

		// traversel for all children.
		for (auto &x : children)
			x.second.printEntry(depth + 1);
	}
};

Entry g_tree{ "" };

// parse entry
void parseEntry(const std::string &entry)
{
	static const std::string blankEntry = "IX: {} {0}";
	if (entry.size() < blankEntry.size()) // illegal entry
		return;

	if (entry.substr(0, 3) != "IX:") // check entry header
		return;

	int posStart = entry.find("{", 3); // find "{"
	if (posStart >= entry.size())      // can't find
		return;

	int posEnd = entry.find("}", posStart); // find "}"
	if (posEnd >= entry.size())             // can't find "}"
		return;

	int pos = posStart + 1;
	bool bExpanded = false;
	bool isStart = false;
	std::vector<std::string> vec;
	int titleStart, titleEnd;
	for (titleStart = titleEnd = pos; pos < posEnd; ++pos)
	{
		if (entry[pos] == '!')
		{
			vec.push_back(entry.substr(titleStart, pos - titleStart));
			titleStart = pos + 1;
			titleEnd = titleStart;
		}
		else if (entry[pos] == '|') // end of the full title name
		{
			bExpanded = true;
		}
		else if (entry[pos] == '(')
		{
			if (!bExpanded) // illegal entry.
				return;

			isStart = true;
		}
		else if (entry[pos] == ')')
		{
			if (!bExpanded) // illegal entry.
				return;
			isStart = false;
		}
		else
		{
			++titleEnd; // normal literal
		}
	}
	vec.push_back(entry.substr(titleStart, titleEnd - titleStart));

	// seek page number
	if((pos = entry.find("{", posEnd)) >= entry.size())
		return;

	++pos;

	if ((posEnd = entry.find("}", pos)) >= entry.size())
		return;

	std::stringstream ssr(entry.substr(pos, posEnd - pos));
	int pageNum = 0;
	ssr >> pageNum;

	g_tree.appendChild(vec, { pageNum, bExpanded});
}

/* test.txt
IX: {Series|(} {2}
IX: {Series!geometric|(} {4}
IX: {Euler's constant} {4}
IX: {Series!geometric|)} {4}
IX: {Series!arithmetic|(} {4}
IX: {Series!arithmetic|)} {5}
IX: {Series!harmonic|(} {5}
IX: {Euler's constant} {5}
IX: {Series!harmonic|)} {5}
IX: {Series|)} {5}
*/

int main(int argc, char **argv)
{
	std::fstream f("d:\\test.txt");

	std::string line;
	while (getline(f, line))
	{
		parseEntry(line);
	}

	g_tree.printChildren();

	return 0;
}