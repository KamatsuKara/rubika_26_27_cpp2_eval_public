#include "Huffman.h"

#include <vector>
#include <queue>
#include <unordered_map>

#include <algorithm>

Huffman::~Huffman() {
	DeleteTree(RootNode);
}

bool Huffman::GenerateTree(const std::string& inputMessage) {
	auto cmp = [](Node*& n1, Node*& n2) {
		if (n1->Frequency != n2->Frequency)
			return n1->Frequency > n2->Frequency;
		else
			return n1->Token > n2->Token;
	};

	std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> nodes(cmp);

	std::unordered_map<char, int> frequency;

	for (char c : inputMessage) {
		frequency[c] += 1;
	}

	for (auto p : frequency) {
		nodes.push(new Node(p.first, (float)(p.second) / inputMessage.length()));
	}

	while (nodes.size() != 1)
	{
		Node* n1 = nodes.top();
		nodes.pop();
		Node* n2 = nodes.top();
		nodes.pop();

		Node* newNode = new Node();
		newNode->Frequency = n1->Frequency + n2->Frequency;
		newNode->Left = n1;
		newNode->Right = n2;

		nodes.push(newNode);
	}

	RootNode = nodes.top();
	UpdateCharCode(RootNode, "");

	return true;
}

void Huffman::UpdateCharCode(Node* n, std::string code) {
	if (n->Token != '\0') {
		CharCode[n->Token] = code;
	}
	else {
		UpdateCharCode(n->Left, code + "0");
		UpdateCharCode(n->Right, code + "1");
	}
}

std::string Huffman::Encode(const std::string& message) const {
	std::string ret = "";

	for (const char& c : message) {
		ret += CharCode.find(c)->second;
	}

	return ret;
}

std::string Huffman::Decode(const std::string& encodedMessage) const {
	std::string ret = "";
	Node* currentInspectNode = RootNode;

	for (const char& c : encodedMessage) {
		currentInspectNode = (c == '0' ? currentInspectNode->Left : currentInspectNode->Right);
		
		if (currentInspectNode->Token != '\0') {
			ret += currentInspectNode->Token;
			currentInspectNode = RootNode;
		}
	}

	return ret;
}

void Huffman::DeleteTree(Node* n) {
	if (n->Left != nullptr) DeleteTree(n->Left);
	if (n->Right != nullptr) DeleteTree(n->Right);

	delete n;
}