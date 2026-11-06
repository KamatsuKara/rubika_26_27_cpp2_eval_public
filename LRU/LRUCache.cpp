#include "LRUCache.h"

LRUCache::LRUCache(int _capacity):capacity(_capacity),currentCount(0){

}

std::string LRUCache::get(int key) {
	auto d = data.find(key);
	if (d != data.end()) {
		useOrder.remove(key);
		useOrder.push_front(key);
		return d->second;
	}
	else return "";
}

void LRUCache::put(int key, std::string value) {
	auto d = data.find(key);
	if (d != data.end()) {
		useOrder.emplace_front(key);
		d->second = value;
	}
	else {
		if (currentCount == capacity) {
			data.erase(useOrder.back());
			useOrder.pop_back();
		}
		else {
			currentCount++;
		}
		data.insert({ key, value });
		useOrder.push_front(key);
	}
}