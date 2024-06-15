// zabawa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <ranges>

void quicksort(std::vector<int> & vec_to_sort, int left_idx, int right_idx) {

    if (right_idx - left_idx > 1) {
        int pivot = vec_to_sort[right_idx];
        int i = left_idx, j = left_idx;
        while (j < right_idx) {
            if (vec_to_sort[j] <= pivot) {
                int temp = vec_to_sort[i];
                vec_to_sort[i] = vec_to_sort[j];
                vec_to_sort[j] = temp;
                j++;
                i++;

            }
            else {
                //swap i and j
                j++;
            }
        }
        //swap i-th and j
        int temp = vec_to_sort[i];
        vec_to_sort[i] = vec_to_sort[j];
        vec_to_sort[j] = temp;

        quicksort(vec_to_sort, left_idx, i - 1);
        quicksort(vec_to_sort, i + 1, right_idx);
    }
    else if(right_idx - left_idx == 1){
        if (vec_to_sort[left_idx] > vec_to_sort[right_idx]) {
            int temp = vec_to_sort[left_idx];
            vec_to_sort[left_idx] = vec_to_sort[right_idx];
            vec_to_sort[right_idx] = temp;
        }
    }

}

#define NUM_COUNT 5000000

int main()
{
    std::vector<int> numbers{};

    /*std::ofstream myfile_out;
    myfile_out.open("numbers.txt", std::ofstream::out | std::ofstream::trunc);*/

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100000); 

    for (int i = 0; i < NUM_COUNT; ++i) {

        //myfile_out << dist(rng) << std::endl;
        numbers.push_back(dist(rng));
    }

    //myfile_out.close();

    //std::ifstream myfile("numbers.txt");



    //if (myfile.is_open())
    {
        
        std::string line{""};
        /*while (std::getline(myfile, line)) {
            
            if (line.size() > 0) {
                int i = 0;
                int liczba = 0;
                for (; i < line.size(); ) {
                    char a = line.at(i);
                    if (a == ' ') {
                        if (liczba != 0) {
                            numbers.push_back(liczba);
                        }
                        liczba = 0;
                        ++i;
                    }
                    else if (a == '\n') {
                        if (liczba != 0) {
                            numbers.push_back(liczba);
                        }
                        break;
                    }
                    else {
                        int int_a = a - '0';
                        liczba = liczba * 10 + int_a;
                        ++i;
                    }
                }
                if (liczba != 0) {
                    numbers.push_back(liczba);
                }
                liczba = 0;
            }
        }*/
        //myfile.close();

        auto numbers_unsorted{ numbers };

        auto start = std::chrono::high_resolution_clock::now();

        quicksort(numbers, 0, numbers.size() - 1);

        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        auto start2 = std::chrono::high_resolution_clock::now();
        std::sort(numbers_unsorted.begin(), numbers_unsorted.end());
        //std::sort(numbers.begin(), numbers.end());
        //std::ranges::sort(numbers_unsorted);
        auto stop2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);


        //std::ofstream myfile_out_sorted;// ("liczby.txt");
        //myfile_out_sorted.open("num_sorted.txt", std::ofstream::out | std::ofstream::trunc);


        //for(int & num : numbers)
        //{
        //    //myfile_out_sorted << num << std::endl;

        //}

        //myfile_out_sorted.close();


        std::cout << std::endl;

        double ratio = (double)duration2.count() / (double)duration.count();

        std::cout << "Time to sort " << NUM_COUNT << " numbers in Quicksort: " << duration.count() << " microseconds";
        std::cout << std::endl;
        std::cout << "Time to sort " << NUM_COUNT << " numbers in std::sort " << duration2.count() << " microseconds";
        std::cout << std::endl;
        if (ratio > 1) {
            std::cout << "std::sort is " << std::fixed << std::setprecision(2) << ratio << " times slower" << std::endl;
        }
        else {
            std::cout << "quicksort is " << std::fixed << std::setprecision(2) << 1/ratio << " times slower" << std::endl;
        }

    }
    
}

