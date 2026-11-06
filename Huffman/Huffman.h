#pragma once

#include <string>
#include <unordered_map>

// Feel free to add anything you need

struct Node
{
	Node(char t, float f) :Token(t), Frequency(f), Left(nullptr), Right(nullptr) {}
	Node() :Token('\0'), Frequency(0), Left(nullptr), Right(nullptr) {}

	char Token;
	float Frequency;

	Node* Left;
	Node* Right;
};

class Huffman
{
public:
	~Huffman();

	bool GenerateTree(const std::string& inputMessage);

	std::string Encode(const std::string& message) const;

	std::string Decode(const std::string& encodedMessage) const;

private:
	Node* RootNode;
	std::unordered_map<char, std::string> CharCode;
	
	void UpdateCharCode(Node*, std::string);
	void DeleteTree(Node*);
};