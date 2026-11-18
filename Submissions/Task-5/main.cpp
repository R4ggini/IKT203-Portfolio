#include <fstream>
#include <iostream>
#include <random>

#include "Classes/TBankAccount.h"
#include "Classes/TLinkedList.h"
#include "StructureReader.h"

TBankAccount* FindAccountByNumber(TBankAccount** accountArray, int arraySize, const std::string& accountNumber, SearchSummary &summary) {
	// Initializes search summary
	summary.comparisons = 0;
	auto startTime = SearchSummary::GetCurrentTime();

	for (int i = 0; i < arraySize; i++) {
		summary.comparisons++;
		if (accountArray[i]->GetAccountNumber() == accountNumber) {
			summary.timeSpentMs = SearchSummary::GetTimeDiff(startTime);
			return accountArray[i];
		}
	}
	summary.timeSpentMs = SearchSummary::GetTimeDiff(startTime);
	return nullptr;
}

void PrintEveryAccountInDateRange(TBankAccount** accountArray, int arraySize, time_t fromDate, time_t toDate, SearchSummary &summary) {
	// Initializes summary
	summary.comparisons = 0;
	auto startTime = SearchSummary::GetCurrentTime();

	for (int i = 0; i < arraySize; i++) {
		summary.comparisons++;
		if (fromDate < accountArray[i]->GetCreationTimestamp() && accountArray[i]->GetCreationTimestamp() < toDate) {
			std::cout << "Account Number: " << accountArray[i]->GetAccountNumber() << std::endl
				<< "Account Type: " << accountArray[i]->AccountTypeToString(accountArray[i]->GetAccountType()) << std::endl
				<< "Account Name: " << accountArray[i]->GetOwnerFirstName() << " " << accountArray[i]->GetOwnerLastName() << std::endl
				<< "Account Created: " << accountArray[i]->GetCreationTimestamp() << std::endl
				<< "Account Balance: " << accountArray[i]->GetBalance() << std::endl << std::endl;
		}
	}
	summary.timeSpentMs = SearchSummary::GetTimeDiff(startTime);
}

bool CompareAccountNumber(TBankAccount* account, void* searchKey) {
	auto* accountNumber = static_cast<std::string*>(searchKey);
	return account->GetAccountNumber() == *accountNumber;
}

bool CompareCreationMonth(TBankAccount* account, void* searchKey) {
	int month = *static_cast<int*>(searchKey);
	time_t creationDate = account->GetCreationTimestamp();
	std::tm* date = std::gmtime(&creationDate);
	return date->tm_mon + 1 == month;
}

int main()
{
	// Initialize list and array
	TLinkedList accountList(true);
	TBankAccount** accountArray = new TBankAccount *[5010];

	// Initialize rng for account generation
	std::mt19937 gen(2024); // set seed to get consistent test data
	std::uniform_int_distribution<> accountsPerName(5, 10);
	std::uniform_int_distribution<> accountType(0, 4);
	std::uniform_int_distribution<long long> time2024(1704067200, 1735689599); // 2024 timespan
	int accountCount = 0;

	ReadNamesFromFile([&](int index, int total, const std::string& firstName, const std::string& lastName) {
		for (int i = accountsPerName(gen); i > 0; i--) {
			auto* account = new TBankAccount(std::to_string(100000 + accountCount), static_cast<EBankAccountType>(accountType(gen)),firstName, lastName, time2024(gen));

			accountList.Append(account);
			accountArray[accountCount++] = account;
		}
		return accountCount < 5000;
	});

	SearchSummary summary;

	// Search for account near end of list
	std::string accountNumber = std::to_string(104880);
	TBankAccount* account = accountList.Find(CompareAccountNumber, &accountNumber, summary); // Will print out nullptr
	if (account != nullptr) std::cout << account->GetOwnerFirstName() << std::endl;
	else std::cout << "Account not found" << std::endl;
	std::cout << summary.comparisons << " comparisons" << std::endl;
	std::cout << summary.timeSpentMs << " ms" << std::endl << std::endl;

	// Search for account that doesnt exist
	accountNumber = std::to_string(110000);
	account = accountList.Find(CompareAccountNumber, &accountNumber, summary);
	if (account != nullptr) std::cout << account->GetOwnerFirstName() << std::endl;
	else std::cout << "Account not found" << std::endl;

	std::cout << summary.comparisons << " comparisons" << std::endl;
	std::cout << summary.timeSpentMs << " ms" << std::endl << std::endl;

	// List all accounts created in june 2024.
	int june = 6;
	TLinkedList* juneAccounts = accountList.Every(CompareCreationMonth, &june, summary);
	if (juneAccounts != nullptr) juneAccounts->Print();
	else std::cout << "No accounts found" << std::endl;
	delete juneAccounts;
	std::cout << summary.comparisons << " comparisons" << std::endl;
	std::cout << summary.timeSpentMs << " ms" << std::endl << std::endl;

	time_t startDate = 170406200; // 2024.01.01 00:00 UTC
	time_t endDate   = 1711929600; // 2024-04-01 00:00 UTC

	PrintEveryAccountInDateRange(accountArray, accountCount, startDate, endDate, summary);
	std::cout << summary.comparisons << " comparisons" << std::endl;
	std::cout << summary.timeSpentMs << " ms" << std::endl;

	delete[] accountArray;
	return 0;
}
