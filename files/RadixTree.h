#ifndef RADIXTREE_H_
#define RADIXTREE_H_

#include <string>
#include <vector>
using namespace std;

template <typename ValueType>
class RadixTree {
public:
	RadixTree();
	~RadixTree();
	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;

private:
	struct RadixNode {
		string m_stored;
		bool m_end;

		RadixNode* m_edges[128];
		ValueType m_vtype;

		RadixNode()
			:m_end(false), m_stored("")
		{
			for (int i = 0; i < 128; i++) {
				m_edges[i] = nullptr;
			}
		}
		~RadixNode()
		{
			for (int i = 0; i < 128; i++) {
				delete m_edges[i];
			}
		}
	};
	RadixNode* m_root = new RadixNode;

	void radixInsert(RadixNode* root, string key, ValueType value)
	{
		if (key.empty()) {
			root->m_end = true;
			root->m_vtype = value;
			return;
		}

		int edge = key[0];
		if (root->m_edges[edge] == nullptr) {
			root->m_edges[edge] = new RadixNode;
			root->m_edges[edge]->m_stored = key;
			//root->m_stored = key;
			radixInsert(root->m_edges[edge], "", value);
			return;

		}

		int complength = 0;
		string currKey = root->m_edges[edge]->m_stored;
		while (complength < min(currKey.length(), key.length()) && currKey[complength] == key[complength]) {
			complength++;
		}

		if (complength == currKey.length()) {
			//ins a bigger similar key
			radixInsert(root->m_edges[edge], key.substr(complength), value);

		}
		else if (complength == key.length()) {
			//ins a smaller similar key
			RadixNode* addNode = new RadixNode;
			addNode->m_edges[currKey[complength]] = root->m_edges[edge];
			addNode->m_edges[currKey[complength]]->m_stored = currKey.substr(complength);
			root->m_edges[edge] = addNode;
			root->m_edges[edge]->m_stored = key;
			radixInsert(root->m_edges[edge], "", value);

		}
		else {
			//not similar
			RadixNode* addNode = new RadixNode;
			addNode->m_edges[currKey[complength]] = root->m_edges[edge];
			addNode->m_edges[currKey[complength]]->m_stored = currKey.substr(complength);
			root->m_edges[edge] = addNode;
			root->m_edges[edge]->m_stored = key.substr(0, complength);
			radixInsert(root->m_edges[edge], key.substr(complength), value);

		}
	}

	RadixNode* radixSearch(RadixNode* root, string key) const
	{
		if (key.empty()) {
			if (root->m_end) { return root; }
			else { return nullptr; }
		}

		int edge = key[0];

		if (root->m_edges[edge] == nullptr) {
			//not found
			return nullptr;
		}

		string currKey = root->m_edges[edge]->m_stored;
		int minlen = min(currKey.length(), key.length());

		if (currKey.substr(0, minlen) != key.substr(0, minlen)) {
			//doesn't fully match
			return nullptr;
		}
		if (currKey.length() == minlen) {
			//partial key matches 
			return radixSearch(root->m_edges[edge], key.substr(currKey.length()));
		}
		else {
			//entire s matches
			return nullptr;
		}
	}
};

template <typename ValueType>
inline
RadixTree<ValueType>::RadixTree()
{
}

template <typename ValueType>
inline
RadixTree<ValueType>::~RadixTree()
{

}

template <typename ValueType>
inline
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
	radixInsert(m_root, key, value);
}

template <typename ValueType>
inline
ValueType* RadixTree<ValueType>::search(std::string key) const
{
	if (radixSearch(m_root, key) == nullptr) {
		return nullptr;
	}

	return &(radixSearch(m_root, key)->m_vtype);
}

#endif
//credit to Discussion2C for RadixTree setup