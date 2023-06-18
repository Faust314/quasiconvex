#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <functional>
#include <string>

namespace graphics::svg {

typedef double coord_t;

struct Object {
	std::string name;
	std::vector<std::string> lines;
	
	std::string & new_line(std::string const & line = "");
	std::string & operator()();
	
	explicit Object(std::string  name_);
	
	Object(Object const & object);
	Object(Object && object) noexcept ;
	
	Object & operator = (Object const & object);
	Object & operator = (Object && object) noexcept;
	
	void print(std::ofstream & ofs, const std::string& space) const;
};



class File {
public:
	static std::function<std::string (coord_t)> to_str;
	
	typedef uint8_t layer_number_t;
	
	struct Layer {
		std::string name;
		layer_number_t number{};
		std::vector<Object> objects;
		
		Layer() = default;
		
		void add_object(Object && obj);
		
		inline void print (std::ofstream & ofs, const std::string& space) const;
	};
	
	File();
	explicit File (std::string  file_name_, double width_ = 2560, double height_ = 1600, double zoom_view_ = 0.8);
	
	void set_name(std::string const & file_name_);
	void set_width(double width_);
	void set_height(double height_);
	void set_zoom_view(double zoom_view_);
	
	inline double get_width() const;
	inline double get_height() const;
	
	
	
	void set_layer_count(layer_number_t count);
	layer_number_t get_layer_count() const;
	
	void choose_layer(std::string const & name);
	void choose_layer(layer_number_t number);
	void set_layer(std::string const & name, layer_number_t number);
	inline Layer & get_layer(std::string const & name);
	inline Layer const & get_layer(std::string const & name) const;
	inline Layer & get_layer(layer_number_t number = 0);
	inline Layer const & get_layer(layer_number_t number = 0) const;
	bool check_layer_names_consistency () const;
	
	void add_object(Object && obj, std::string const & layer_name);
	void add_object(Object && obj, layer_number_t layer_number);
	void add_object(Object && obj);
	
	std::string & new_line(std::string const & line = "");
	std::string & last_line();
	
	void print(const std::string& dir) const;
	
	
	
private:
	constexpr static double display_width = double(2560);
	constexpr static double display_height = double(1600);
	
	std::string file_name;
	double width;
	double height;
	double zoom_view;
	
	std::vector<Layer> layers;
	std::unordered_map<std::string, layer_number_t> layer_numbers;
	
	Layer * layer;
	
	void print_prefix(std::ofstream & ofs) const;
	static void print_suffix(std::ofstream & ofs);
};



} // namespace graphics::svg
