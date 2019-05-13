#include "longest_string.h"

int longest_string_value(vector <string> strings) {
	int max_length = 0;
	const int strings_size = strings.size();
	if (strings_size) {
		for (size_t i = 0; i < strings_size; i++) {
			const string str = strings[i];
			const int length = strlen(str.c_str());
			if (length > max_length)
				max_length = length;
		}
	}
	return max_length;
}

int longest_string_value(string* strings, const int strings_size) {
	int max_length = 0;
	if (strings_size) {
		for (size_t i = 0; i < strings_size; i++) {
			const string str = strings[i];
			const int length = strlen(str.c_str());
			if (length > max_length)
				max_length = length;
		}
	}
	return max_length;
}