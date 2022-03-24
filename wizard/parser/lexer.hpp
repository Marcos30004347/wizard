#ifndef WIZARD_TOKEN_HPP
#define WIZARD_TOKEN_HPP

#include "utils/types.hpp"

#include <iterator>
#include <vector>

enum TokenTag {
	TOKEN_STRING_LITERAL,
};

struct Token {
	u32 file;
	u32 line;
	u32 column;
	
	TokenTag tag; 
};

struct TokenBucket {
	// Maximum Tokens on Bucket.
	const static u32 size = 256;

	// Linear array of tokens.
	Token tokens[size];
};

struct TokenKey {
	u32 bucket;
	u32 index;
};

#endif //WIZARD_TOKEN_HPP


