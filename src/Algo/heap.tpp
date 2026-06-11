#pragma once
#include "heap.hpp"

#include <numeric>

namespace algo {

template <typename Item>
bool DefaultCompare<Item>::operator() (Item const & item1, Item const & item2) {
	return item1 <= item2;
}





template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &> Heap<Item, id_t, Compare>::Heap (Compare cmp_) {
	cmp = cmp_;
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
Heap<Item, id_t, Compare>::Heap (std::vector<Item> items_) {
	items = std::move(items_);
	std::iota(item_indexes.begin(), item_indexes.end(), 0);
	std::iota(item_ids.begin(), item_ids.end(), 0);
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
Heap<Item, id_t, Compare>::Heap (std::vector<Item> items_, Compare cmp_) :
	Heap(std::move(items_))
{
	cmp = std::move(cmp_);
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
bool Heap<Item, id_t, Compare>::empty () const {
	return item_ids.empty();
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
id_t Heap<Item, id_t, Compare>::size () const {
	return item_ids.size();
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
Item const & Heap<Item, id_t, Compare>::top () const {
	assert(! empty());
	return items[item_ids[0]];
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>id_t Heap<Item, id_t, Compare>::top_id () const {
	return item_ids[0];
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>bool Heap<Item, id_t, Compare>::has_item (id_t id) {
	assert(0 < id && id < item_ids.size());
	return item_indexes[id] != MAX_ID;
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
id_t Heap<Item, id_t, Compare>::push (Item item) {
	item_indexes.push_back(item_ids.size());
	item_ids.push_back(item_indexes.size() - 1);
	items.push_back(std::move(item));
	shift_up(item_ids.size() - 1);
	return item_indexes.size() - 1;
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::update (id_t id, Item item) {
	assert(has_item(id));
	if (cmp(item, items[id])) {
		items[id] = std::move(item);
		shift_up(item_indexes[id]);
	} else {
		items[id] = std::move(item);
		shift_down(item_indexes[id]);
	}
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::pop () {
	assert(! empty());
	item_indexes[item_ids.back()] = 0;
	item_indexes[item_ids.front()] = MAX_ID;
	item_ids.front() = item_ids.back();
	item_ids.pop_back();
	shift_down(0);
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::erase (id_t id) {
	assert(has_item(id));
	item_ids[item_indexes[id]] = item_ids.back();
	item_indexes[item_ids.back()] = item_indexes[id];
	item_indexes[id] = MAX_ID;
	item_ids.pop_back();
	shift_down(item_indexes[id]);
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::reserve (id_t size) {
	items.reserve(size);
	item_ids.reserve(size);
	item_indexes.reserve(size);
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::shrink_to_fit () {
	items.shrink_to_fit();
	item_ids.shrink_to_fit();
	item_indexes.shrink_to_fit();
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::clear () {
	items.clear();
	item_ids.clear();
	item_indexes.clear();
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>void
Heap<Item, id_t, Compare>::swap_items (id_t ind1, id_t ind2) {
	item_indexes[item_ids[ind1]] = ind2;
	item_indexes[item_ids[ind2]] = ind1;
	std::swap(item_ids[ind1], item_ids[ind2]);
}



template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::shift_up (id_t ind) {
	while (ind > 0) {
		id_t parent = (ind - 1) / 2;
		if (cmp(items[item_ids[ind]], items[item_ids[parent]])) {
			swap_items(ind, parent);
			ind = parent;
		} else {
			break;
		}
	}
}

template <typename Item, typename id_t, typename Compare>
requires std::predicate<Compare, Item const &, Item const &>
void Heap<Item, id_t, Compare>::shift_down (id_t ind) {
	while (true) {
		id_t left = 2 * ind;
		id_t right = 2 * ind + 1;
		if (left < size() && cmp(items[item_ids[left]], items[item_ids[ind]])) {
			swap_items(ind, left);
			ind = left;
		} else if (right < size() && cmp(items[item_ids[right]], items[item_ids[ind]])) {
			swap_items(ind, right);
			ind = right;
		} else {
			break;
		}
	}
}

} // namespace algo