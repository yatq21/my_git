#ifndef HASH_UTILS_HPP
#define HASH_UTILS_HPP

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace hash_utils {

inline uint32_t left_rotate(uint32_t value, int count) {
    return (value << count) | (value >> (32 - count));
}

inline std::string sha1_hex(const std::vector<uint8_t>& input) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    std::vector<uint8_t> data = input;
    uint64_t bit_length = static_cast<uint64_t>(data.size()) * 8;

    data.push_back(0x80);
    while ((data.size() % 64) != 56) {
        data.push_back(0x00);
    }
    for (int i = 7; i >= 0; --i) {
        data.push_back(static_cast<uint8_t>((bit_length >> (i * 8)) & 0xFF));
    }

    for (size_t offset = 0; offset < data.size(); offset += 64) {
        uint32_t w[80] = {0};
        for (int i = 0; i < 16; ++i) {
            w[i] = (static_cast<uint32_t>(data[offset + i * 4]) << 24) |
                   (static_cast<uint32_t>(data[offset + i * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(data[offset + i * 4 + 2]) << 8) |
                   (static_cast<uint32_t>(data[offset + i * 4 + 3]));
        }
        for (int i = 16; i < 80; ++i) {
            w[i] = left_rotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for (int i = 0; i < 80; ++i) {
            uint32_t f;
            uint32_t k;
            if (i < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            uint32_t temp = left_rotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = left_rotate(b, 30);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    std::ostringstream oss;
    oss << std::hex << std::setfill('0')
        << std::setw(8) << h0
        << std::setw(8) << h1
        << std::setw(8) << h2
        << std::setw(8) << h3
        << std::setw(8) << h4;
    return oss.str();
}

inline std::string compute_commit_id_from_staging(const std::filesystem::path& staging_dir) {
    if (!std::filesystem::exists(staging_dir) || !std::filesystem::is_directory(staging_dir)) {
        return "";
    }

    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(staging_dir)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    if (files.empty()) {
        return "";
    }

    std::sort(files.begin(), files.end(), [](const std::filesystem::path& a, const std::filesystem::path& b) {
        return a.generic_string() < b.generic_string();
    });

    std::vector<uint8_t> payload;
    for (const auto& file_path : files) {
        std::string rel = std::filesystem::relative(file_path, staging_dir).generic_string();
        payload.insert(payload.end(), rel.begin(), rel.end());
        payload.push_back('\n');

        std::ifstream in(file_path, std::ios::binary);
        std::vector<char> bytes((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        payload.insert(payload.end(), bytes.begin(), bytes.end());
        payload.push_back('\n');
    }

    return sha1_hex(payload);
}

} // namespace hash_utils

#endif
