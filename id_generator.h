#pragma once

#include <vector>
#include <string_view>

class alphabet {
public:
    explicit alphabet(std::string_view letters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char to_char(int value) const;
    int to_value(char letter) const;
    size_t size() const;

private:
    std::vector<char> data;
};

class id_generator {
public:
    /*
     * serial: local bkz eg (T002)
     * birth: birth date eg (010203) for 02/03/2001
     * expirency: expirency date eg (030201) for 02/01/2003
     */
    id_generator(std::string_view serial, std::string_view birth, std::string_view expirency);

    /*
     * Returns the id as string
     * Example:
     * IDD<<T0021SO4Y2<<<<<<<<<<<<<<<
     * 0102030<0302014D<<<<<<<<<<<<<4
     */
    std::string to_string() const;

private:
    char block_cksum(const std::vector<char>& block) const;
    char random_char() const;
    std::string serialize_block(const std::vector<char>& block) const;

    alphabet alpha;
    std::vector<char> block0;
    std::vector<char> block1;
    std::vector<char> block2;
    char cksum;
};