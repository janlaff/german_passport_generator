#include "id_generator.h"

#include <array>
#include <sstream>
#include <algorithm>
#include <experimental/random>

alphabet::alphabet(std::string_view letters) : data(letters.cbegin(), letters.cend()) {}

char alphabet::to_char(int value) const {
    if (value >= data.size()) value -= data.size();
    return data[value];
}

int alphabet::to_value(char letter) const {
    for (auto i = 0; i < data.size(); ++i) {
        if (data[i] == letter) return i;
    }
}

size_t alphabet::size() const {
    return data.size();
}

id_generator::id_generator(std::string_view serial, std::string_view birth, std::string_view expirency) {
    // Copy serial number
    std::copy(serial.cbegin(), serial.cend(), std::back_inserter(block0));
    // Generate random values
    std::generate_n(std::back_inserter(block0), 5, [this]() { return random_char(); });
    // Generate checksum
    block0.push_back(block_cksum(block0));

    // Copy birth date
    std::copy(birth.cbegin(), birth.cend(), std::back_inserter(block1));
    // Generate checksum
    block1.push_back(block_cksum(block1));

    // Copy expirency date
    std::copy(expirency.cbegin(), expirency.cend(), std::back_inserter(block2));
    // Generate checksum
    block2.push_back(block_cksum(block2));

    // Generate final checksum
    auto tmp = std::vector<char>();
    // Copy all blocks to tmp
    std::copy(block0.cbegin(), block0.cend(), std::back_inserter(tmp));
    std::copy(block1.cbegin(), block1.cend(), std::back_inserter(tmp));
    std::copy(block2.cbegin(), block2.cend(), std::back_inserter(tmp));
    // Get checksum
    cksum = block_cksum(tmp);
}

std::string id_generator::to_string() const {
    auto ss = std::ostringstream();

    ss << "IDD<<" << serialize_block(block0) << "<<<<<<<<<<<<<<<\n";
    ss << serialize_block(block1) << "<" << serialize_block(block2);
    ss << "D<<<<<<<<<<<<<" << cksum;

    return ss.str();
}

char id_generator::block_cksum(const std::vector<char> &block) const {
    const auto factors = std::array { 7, 3, 1 };

    // Returns 7, 3, 1, 7, 3, 1, ...
    auto generate = [&factors, idx = 0]() mutable {
        auto val = factors[idx++];
        if (idx == factors.size()) idx = 0;
        return val;
    };

    auto sum = 0;
    std::for_each(block.cbegin(), block.cend(), [&](const char& val) {
        sum += alpha.to_value(val) * generate();
    });

    return alpha.to_char(sum % 10);
}

char id_generator::random_char() const {
    return alpha.to_char(std::experimental::randint(0, int(alpha.size() - 1)));
}

std::string id_generator::serialize_block(const std::vector<char> &block) const {
    return std::string(block.cbegin(), block.cend());
}