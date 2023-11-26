#include <iostream>
#include <omp.h>
#include <vector>

const unsigned int MILLION = 1'000'000;

void FillingRandomValues(std::vector<int>& vec, int min, int max)
{
    std::srand(unsigned(std::time(nullptr)));

    #pragma omp parallel for
    for (int i = 0; i < vec.size(); i++)
        vec[i] = std::rand() % (max - min + 1) + min;
}

std::vector<char> Compress(const std::vector<int>& decompressed)
{
    std::vector<char> compressed(decompressed.size());

    #pragma omp parallel for
    for (int i = 0; i < decompressed.size(); i++)
        compressed[i] = static_cast<char>(decompressed[i]);

    return compressed;
}

std::vector<int> Decompress(const std::vector<char>& compressed)
{
    std::vector<int> decompressed(compressed.size());

    #pragma omp parallel for
    for (int i = 0; i < compressed.size(); i++)
        decompressed[i] = static_cast<int>(compressed[i]);

    return decompressed;
}

int main()
{
    int min = 1;
    int max = 100;

    std::vector<int> originalData(MILLION);

    FillingRandomValues(originalData, min, max);

    std::vector<char> compressedData = Compress(originalData);
    std::vector<int> decompressedData = Decompress(compressedData);

    std::cout << "Compressed data size: " << compressedData.size() * sizeof(char) << " byte" << std::endl;
    std::cout << "Decompressed data size: " << decompressedData.size() * sizeof(int) << " byte" << std::endl;

    return 0;
}