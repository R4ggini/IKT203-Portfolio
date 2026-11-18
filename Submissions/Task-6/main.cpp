#include <chrono>
#include <iostream>
#include <random>

#include "StructureReader.h"
#include "Classes/TBankAccount.h"
#include "Classes/TLinkedList.h"
#include "Classes/TSort.h"

int CompareLastName(TBankAccount* a, TBankAccount* b) {
	auto aName = a->GetOwnerLastName();
	auto bName = b->GetOwnerLastName();
	if (aName < bName) return -1;
	if (aName > bName) return 1;
	return 0;
}

int CompareBalance(TBankAccount* a, TBankAccount* b) {
	auto aBalance = a->GetBalance();
	auto bBalance = b->GetBalance();
	if (aBalance < bBalance) return -1;
	if (aBalance > bBalance) return 1;
	return 0;
}

void PrintArray(TBankAccount** array, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << array[i]->GetAccountNumber() << ", "
		<< TBankAccount::AccountTypeToString(array[i]->GetAccountType()) << ", "
		<< array[i]->GetOwnerFirstName() << ", "
		<< array[i]->GetOwnerLastName() << ", "
		<< array[i]->GetCreationTimestamp() << ", "
		<< array[i]->GetBalance() << std::endl;
	}
}

void PrintOperationSummary(OperationSummary* operationSummary) {
	std::cout << "Time spent: " << operationSummary->timeSpentMs << " ms" << std::endl
		<< "Comparisons: " << operationSummary->comparisons << std::endl
		<< "Swaps: " << operationSummary->swaps << std::endl;
}

int main()
{
	// Initialize list and array
	auto* accountList = new TLinkedList(true);
	auto** accountArray = new TBankAccount *[5010];

	// Initialize rng for account generation
	std::mt19937 gen(std::random_device{}()); // random seed, so the test data changes every run
	std::uniform_int_distribution<> accountsPerName(5, 10);
	std::uniform_int_distribution<> accountType(0, 4);
	std::uniform_int_distribution<long long> time2024(1704067200, 1735689599); // 2024 timespan
	std::uniform_int_distribution<> accountNumber(100000, 999999);
	int accountCount = 0;

	ReadNamesFromFile([&](int index, int total, const std::string& firstName, const std::string& lastName) {
		for (int i = accountsPerName(gen); i > 0; i--) {
			auto* account = new TBankAccount(std::to_string(accountNumber(gen)), static_cast<EBankAccountType>(accountType(gen)),firstName, lastName, time2024(gen));

			accountList->Append(new TLinkedList::TNode(account, nullptr));
			accountArray[accountCount++] = account;
		}
		return accountCount < 5000;
	});
	auto *sorter = new TSort(accountList, accountArray, accountCount);

	// Selection sort
	OperationSummary selectionSortListSummary{};
	auto selectionSortedList = sorter->SelectionSort(&CompareLastName ,accountList, &selectionSortListSummary);
	selectionSortedList->Print();
	PrintOperationSummary(&selectionSortListSummary);

	OperationSummary selectionSortArraySummary{};
	auto selectionSortedArray = sorter->SelectionSort(&CompareLastName ,accountArray, accountCount, &selectionSortArraySummary);
	PrintArray(selectionSortedArray, accountCount);
	PrintOperationSummary(&selectionSortArraySummary);

	// Bubble sort
	OperationSummary bubbleSortSummary{};
	auto bubbleSortedArray = sorter->BubbleSort(&CompareLastName ,accountArray, accountCount, &bubbleSortSummary);
	PrintArray(bubbleSortedArray, accountCount);
	PrintOperationSummary(&bubbleSortSummary);

	// Quick sort
	OperationSummary quickSortSummary{};
	TBankAccount** quickSortedArray = sorter->QuickSort(&CompareLastName, accountArray, accountCount, &quickSortSummary);
	PrintArray(quickSortedArray, accountCount);
	PrintOperationSummary(&quickSortSummary);

	// Merge sort
	OperationSummary mergeSortSummary{};
	TLinkedList* mergeSortedList = sorter->MergeSort(&CompareLastName, accountList, &mergeSortSummary);
	mergeSortedList->Print();
	PrintOperationSummary(&mergeSortSummary);

	std::cout << std::endl;
	selectionSortListSummary.Print();
	selectionSortArraySummary.Print();
	bubbleSortSummary.Print();
	quickSortSummary.Print();
	mergeSortSummary.Print();

	// Initialization for binary search
	OperationSummary binarySearchSummary{};
	TBankAccount* target = quickSortedArray[4000];

	// Test binary search on unsorted list
	TBankAccount* result = sorter->BinarySearch(&CompareLastName, target, &binarySearchSummary);
	std::cout << result << std::endl;

	// Test binary search on sorted list
	sorter->SortArrayByLastName(&CompareLastName, &binarySearchSummary); // sorts list stored in object

	TBankAccount* binarySearchFunction = sorter->BinarySearch(&CompareLastName, target, &binarySearchSummary); // sorted list
	if (binarySearchFunction != nullptr) std::cout << binarySearchFunction->GetOwnerLastName() << std::endl;

	// Linear search on unsorted list
	OperationSummary linearSearchSummary{};
	TBankAccount* linearSearchFunction = accountList->Find(&CompareLastName, target, linearSearchSummary);
	if (linearSearchFunction != nullptr) std::cout << linearSearchFunction->GetOwnerLastName() << std::endl << std::endl;

	// Print out summary for binary and linear search
	binarySearchSummary.Print();
	linearSearchSummary.Print();

	// Free memory
	delete selectionSortedList;
	delete[] selectionSortedArray;
	delete[] bubbleSortedArray;
	delete[] quickSortedArray;
	delete mergeSortedList;
	delete sorter;
	delete accountList; // owns the accounts, deletes them too
	delete[] accountArray;
	return 0;
}
