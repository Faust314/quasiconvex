#pragma once

#include <vector>
#include <limits>

namespace algo {

template <typename Item>
struct DefaultCompare {
	bool operator() (Item const & item1, Item const & item2);
};



template<typename Item, typename id_t, typename Compare = DefaultCompare<Item>>
requires std::predicate<Compare, Item const &, Item const &>
class Heap {
public:
	Heap () = default;
	explicit Heap (Compare cmp_);
	explicit Heap (std::vector<Item> items_);
	explicit Heap (std::vector<Item> items_, Compare cmp_);
	
	bool empty () const;
	id_t size () const;
	
	Item const & top () const;
	id_t top_id () const;
	
	bool has_item (id_t id);
	
	id_t push (Item item);
	void update (id_t id, Item item);
	
	void pop ();
	void erase (id_t id);
	
	void reserve (id_t size);
	void shrink_to_fit ();
	void clear ();
	
private:
	Compare cmp = Compare{};
	std::vector<id_t> items;
	std::vector<id_t> item_ids;
	std::vector<id_t> item_indexes;
	inline static id_t const MAX_ID = std::numeric_limits<id_t>::max();
	
	void swap_items (id_t ind1, id_t ind2);
	void shift_up (id_t ind);
	void shift_down (id_t ind);
};
	
} // namespace algo