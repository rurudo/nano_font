#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

// SaveBinary
#include<fstream>

namespace nano_font
{

namespace detail
{
	constexpr int LastBit(int count, int bits) {
		return count % bits != 0 ? 1 : 0;
	}
}

using BinaryType = unsigned int;

namespace property {
	const int width = 3;
	const int height = 5;
	const int pixel_count = width * height;
	const int alphabet_count = 26;
	const int number_count = 10;
	const int space_count = 1;
	const int font_count = alphabet_count + number_count + space_count;

	namespace binary {
		const int count = pixel_count * property::font_count;
		const int bits = sizeof(BinaryType) * 8;
		const int size = binary::count / bits + detail::LastBit(binary::count, bits);
	}
}

struct Texture {
	int width = 0;
	int height = 0;
	bool flip = true;
};

const char raw[][property::width * property::height] = {
	{
		0, 1, 0,
		1, 0, 1,
		1, 1, 1,
		1, 0, 1,
		1, 0, 1,
	},
	{
		1, 1, 0,
		1, 0, 1,
		1, 1, 0,
		1, 0, 1,
		1, 1, 0,
	},
	{
		0, 1, 0,
		1, 0, 1,
		1, 0, 0,
		1, 0, 1,
		0, 1, 0,
	},
	{
		1, 1, 0,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 1, 0,
	},
	{
		1, 1, 1,
		1, 0, 0,
		1, 1, 1,
		1, 0, 0,
		1, 1, 1,
	},
	{
		1, 1, 1,
		1, 0, 0,
		1, 1, 0,
		1, 0, 0,
		1, 0, 0,
	},
	{
		0, 1, 0,
		1, 0, 1,
		1, 0, 0,
		1, 0, 1,
		0, 1, 1,
	},
	{
		1, 0, 1,
		1, 0, 1,
		1, 1, 1,
		1, 0, 1,
		1, 0, 1,
	},
	{
		1, 1, 1,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		1, 1, 1,
	},
	{
		0, 1, 1,
		0, 0, 1,
		0, 0, 1,
		1, 0, 1,
		0, 1, 0,
	},
	{
		1, 0, 1,
		1, 0, 1,
		1, 1, 0,
		1, 0, 1,
		1, 0, 1,
	},
	{
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 1, 1,
	},
	{
		1, 0, 1,
		1, 1, 1,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
	},
	{
		0, 0, 0,
		0, 0, 0,
		1, 1, 1,
		1, 0, 1,
		1, 0, 1,
	},
	{
		0, 1, 0,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		0, 1, 0,
	},
	{
		1, 1, 0,
		1, 0, 1,
		1, 1, 0,
		1, 0, 0,
		1, 0, 0,
	},
	{
		0, 1, 1,
		1, 0, 1,
		0, 1, 1,
		0, 0, 1,
		0, 0, 1,
	},
	{
		1, 1, 0,
		1, 0, 1,
		1, 1, 0,
		1, 0, 1,
		1, 0, 1,
	},
	{
		1, 1, 1,
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 1, 1,
	},
	{
		1, 1, 1,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
	},
	{
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		0, 1, 0,
	},
	{
		0, 0, 0,
		0, 0, 0,
		1, 0, 1,
		1, 0, 1,
		0, 1, 0,
	},
	{
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 1, 1,
		1, 0, 1,
	},
	{
		1, 0, 1,
		1, 0, 1,
		0, 1, 0,
		1, 0, 1,
		1, 0, 1,
	},
	{
		1, 0, 1,
		1, 0, 1,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
	},
	{
		1, 1, 1,
		0, 0, 1,
		0, 1, 0,
		1, 0, 0,
		1, 1, 1,
	},
	{
		1, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		1, 1, 1,
	},
	{
		1, 1, 1,
		0, 0, 1,
		1, 1, 1,
		1, 0, 0,
		1, 1, 1,
	},
	{
		1, 1, 1,
		0, 0, 1,
		1, 1, 1,
		0, 0, 1,
		1, 1, 1,
	},
	{
		1, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 0, 1,
		0, 0, 1,
	},
	{
		1, 1, 1,
		1, 0, 0,
		1, 1, 1,
		0, 0, 1,
		1, 1, 1,
	},
	{
		1, 1, 1,
		1, 0, 0,
		1, 1, 1,
		1, 0, 1,
		1, 1, 1,
	},
	{
		1, 1, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
	},
	{
		1, 1, 1,
		1, 0, 1,
		1, 1, 1,
		1, 0, 1,
		1, 1, 1,
	},
	{
		1, 1, 1,
		1, 0, 1,
		1, 1, 1,
		0, 0, 1,
		1, 1, 1,
	},
	{
		1, 1, 1,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 1, 1,
	},
	{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
	},
};

const std::array<BinaryType, property::binary::size> binary = {
	0x9d75dbea, 0xf76d6a9a, 0xa8967f3c, 0x97b7dba9, 0xbb559374, 0xb7de4936, 0xadaade05, 0xc9ae25d6,
	0xfe23ed75, 0x02b6d492, 0x5b7db55a, 0x53a4adb5, 0x7cfd24f9, 0x4f6f9e7e, 0xf79fe73e, 0xfdf7c927,
	0x0F6dfe7b
};

std::vector<bool> Data() {
	return std::vector<bool>(*raw, *raw + property::font_count * property::pixel_count);
}

char ToIndex(char code) {
	if('a' <= code && code <= 'z') {
		return code - 'a';
	} else if('A' <= code && code <= 'Z') {
		return code - 'A';
	} else if('0' <= code && code <= '9') {
		return property::alphabet_count + code -'0';
	}
	return property::font_count - 1;
}

using Pixels = std::vector<std::uint32_t>;
class Writer {
public:
	Writer(const Texture &texture) {
		pixels_ = std::vector<std::uint32_t>(texture.width * texture.height);
		auto indices = std::vector<std::uint8_t>(property::font_count);
		std::iota(indices.begin(), indices.end(), 0);
		for (const auto &index : indices)
		{
			Write(index, index, texture);
		}
	}

	Pixels Get() const {
		return pixels_;
	}
private:

	void Write(int index, int position, const Texture &texture) {
		for (int i = 0; i < property::height; ++i) {
			for (int j = 0; j < property::width; ++j) {
				auto binary_index = index * property::pixel_count + i * property::width + j;
				auto bits = nano_font::property::binary::bits;
				if (nano_font::binary.at(binary_index / bits) & 1 << (binary_index % bits)) {
					if(texture.flip) {
						pixels_.at((texture.height - 1 - i) * texture.width + j + position * property::width) = 0xFFFFFFFF;
					} else {
						pixels_.at(i * texture.width + j + position * property::width) = 0xFFFFFFFF;
					}
				}
			}
		}
	}

	Pixels pixels_;
};

Pixels Make(const Texture &texture) {
	auto writer = Writer(texture);
	return std::move(writer.Get());
}

namespace detail {
	void SaveBinary() {
		auto data = nano_font::Data();
		auto byte_count = data.size() / 8;
		if (data.size() / 8 != 0) {
			++byte_count;
		}

		auto bytes = std::vector<char>(byte_count);
		for (std::uint32_t i = 0; i < byte_count; ++i) {
			for (std::uint32_t j = 0; j < 8; ++j) {
				if (data.size() <= i * 8 + j) {
					break;
				}
				if (data.at(i * 8 + j)) {
					bytes.at(i) |= 1 << j;
				}
			}
		}

		std::ofstream stream("binary", std::ios::out | std::ios::binary);
		stream.write(bytes.data(), bytes.size());
	}
}

}
