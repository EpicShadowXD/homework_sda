#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <optional>
#include <map>
#include <complex>

template <typename T>
concept NumericType = std::is_arithmetic_v<T> or std::is_floating_point_v<T>;

template <typename T>
[[maybe_unused]]
void bubbleSort(std::vector<T>& vec) requires(NumericType<T>) {
    for (auto i = 0; i < vec.size() - 1; ++i)
        for (auto j = 0; j < vec.size() - i - 1; ++j)
            if (vec[j] > vec[j + 1])
                std::swap(vec[j], vec[j + 1]);
}

template <typename T>
[[maybe_unused]]
void selectionSort(std::vector<T>& vec) requires(NumericType<T>) {
    for (auto i = 0; i < vec.size() - 1; ++i) {
        auto minIndex = i;

        for (auto j = i + 1; j < vec.size(); ++j)
            if (vec[j] < vec[minIndex])
                minIndex = j;
        std::swap(vec[i], vec[minIndex]);
    }
}

template <typename T>
[[maybe_unused]]
void counterSort(std::vector<T>& vec) requires(NumericType<T>) {
    std::map<T, size_t> countMap;

    for (const T& value : vec) ++countMap[value];

    auto index = 0;
    for (const auto& pair : countMap) {
        const auto value = pair.first;
        const auto frequency = pair.second;

        for (auto i = 0; i < frequency; ++i) vec[index++] = value;
    }
}

template <typename T>
void merge(std::vector<T>& vec, T left, T mid, T right) requires(NumericType<T>) {
    auto n1 = mid - left + 1;
    auto n2 = right - mid;

    std::vector<T> leftArray(n1), rightArray(n2);

    std::copy(vec.begin() + left, vec.begin() + left + n1, leftArray.begin());
    std::copy(vec.begin() + mid + 1, vec.begin() + right + 1, rightArray.begin());

    auto i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j])
            vec[k++] = leftArray[i++];
        else
            vec[k++] = rightArray[j++];
    }

    while (i < n1) vec[k++] = leftArray[i++];
    while (j < n2) vec[k++] = rightArray[j++];
}

template <typename T>
void mergeSort(std::vector<T>& vec, T left, T right) requires(NumericType<T>) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

template <typename T>
T partition(std::vector<T>& vec, T low, T high) requires(NumericType<T>) {
    auto pivot = vec[high];
    auto i = (low - 1);

    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[high]);
    return (i + 1);
}

template <typename T>
void quickSort(std::vector<T>& vec, T low, T high) requires(NumericType<T>) {
    if (low < high) {
        auto pi = partition(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

template <typename T>
[[maybe_unused]]
void insertionSort(std::vector<T>& vec) requires(NumericType<T>) {
    for (size_t i = 1; i < vec.size(); ++i) {
        auto key = vec[i];
        auto j = i - 1;

        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }

        vec[j + 1] = key;
    }
}

template <typename T>
[[maybe_unused]]
void shellSort(std::vector<T>& vec) requires(NumericType<T>) {
    for (size_t gap = vec.size() / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < vec.size(); ++i) {
            T key = vec[i];
            size_t j = i;

            while (j >= gap && vec[j - gap] > key) {
                vec[j] = vec[j - gap];
                j -= gap;
            }

            vec[j] = key;
        }
    }
}

template <typename T>
[[maybe_unused]]
void radixSort(std::vector<T>& vec) requires(NumericType<T>) {
    // Determine the maximum number of digits
    auto maxDigits = 0;
    auto maxElement = *std::max_element(vec.begin(), vec.end());
    while (maxElement > 0) {
        maxDigits++;
        maxElement /= 10;
    }

    // Create auxiliary buckets for each digit
    std::vector<std::vector<T>> buckets(10);

    // Perform radix sorting for each digit
    for (auto digit = 0; digit < maxDigits; ++digit) {
        // Distribute elements to buckets based on their digit
        for (const T& element : vec) {
            auto bucketIndex = element / (static_cast<int>(std::pow(10, digit))) % 10;
            buckets[bucketIndex].push_back(element);
        }

        // Clear the original vector and collect elements from buckets
        vec.clear();
        for (auto& bucket : buckets) {
            vec.insert(vec.end(), bucket.begin(), bucket.end());
            bucket.clear();
        }
    }
}


template <typename T>
[[maybe_unused]]
T binarySearch(std::vector<T>& vec, T target) requires(NumericType<T>) {
    auto left = 0;
    auto right = vec.size() - 1;

    while (left <= right) {
        auto mid = left + (right - left) / 2;

        if (vec[mid] == target)
            return mid;
        else if (vec[mid] < target)
            left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

enum SortingState {
    EXIT,
    BUBBLE_SORT,
    SELECTION_SORT,
    COUNTER_SORT,
    MERGE_SORT,
    QUICK_SORT,
    INSERTION_SORT,
    SHELL_SORT,
    RADIX_SORT,
    BINARY_SEARCH,
};

// optional number for binary search
template <typename T>
void mySort(std::vector<T>& vec, SortingState state, const std::optional<T> number) {
    switch (state) {
        case EXIT:
            exit(0);
            break;
        case BUBBLE_SORT:
            bubbleSort(vec);
            break;
        case SELECTION_SORT:
            selectionSort(vec);
            break;
        case COUNTER_SORT:
            counterSort(vec);
            break;
        case MERGE_SORT:
            mergeSort(vec, 0, static_cast<int>(vec.size() - 1));
            break;
        case QUICK_SORT:
            quickSort(vec);
            break;
        case INSERTION_SORT:
            insertionSort(vec);
            break;
        case SHELL_SORT:
            shellSort(vec);
            break;
        case RADIX_SORT:
            radixSort(vec);
            break;
        case BINARY_SEARCH:
            binarySearch(vec, number);
            break;
        default:
            std::cout << "Invalid sorting state provided" << std::endl;
    }
}