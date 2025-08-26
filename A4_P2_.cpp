#include <iostream>
#include <string>
#include <queue>
#include <array>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string inputLine;
    std::getline(std::cin, inputLine);

    std::array<long long, 128> characterFrequency{};
    for (char ch : inputLine) {
        characterFrequency[static_cast<unsigned char>(ch)]++;
    }

    int distinctCharacters = 0;
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> frequencyQueue;
    for (long long frequency : characterFrequency) {
        if (frequency > 0) {
            distinctCharacters++;
            frequencyQueue.push(frequency);
        }
    }

    if (distinctCharacters == 0) {
        std::cout << 0 << '\n';
        return 0;
    }

    if (distinctCharacters == 1) {
        std::cout << inputLine.size() << '\n';
        return 0;
    }

    long long totalBits = 0;
    while (frequencyQueue.size() > 1) {
        long long smallest = frequencyQueue.top();
        frequencyQueue.pop();
        long long nextSmallest = frequencyQueue.top();
        frequencyQueue.pop();
        long long mergedFrequency = smallest + nextSmallest;
        totalBits += mergedFrequency;
        frequencyQueue.push(mergedFrequency);
    }

    std::cout << totalBits << '\n';
    return 0;
}