#pragma once

#include <string>
#include <unordered_map>
#include <list>

class LRUCache
{
public:
	LRUCache(int _capacity);

	std::string get(int key);
	void put(int key, std::string value);

private:
	int capacity;
	int currentCount;
	std::list<int> useOrder;
	std::unordered_map<int, std::pair<std::string, decltype(useOrder.begin())>> data;
};