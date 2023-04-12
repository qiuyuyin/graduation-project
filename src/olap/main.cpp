#include <iostream>
#include <string>
#include <zstd.h>

int main() {
    std::string uncompressed = "Hello, World!";
    std::string compressed;
    compressed.resize(ZSTD_compressBound(uncompressed.size()));

    size_t compressed_size = ZSTD_compress(
        compressed.data(), compressed.size(),
        uncompressed.data(), uncompressed.size(),
        1  // 压缩级别
    );

    std::string decompressed;
    decompressed.resize(uncompressed.size());

    size_t decompressed_size = ZSTD_decompress(
        decompressed.data(), decompressed.size(),
        compressed.data(), compressed_size
    );

    std::cout << decompressed << std::endl;
    return 0;
}