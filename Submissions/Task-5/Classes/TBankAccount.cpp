//
// Created by Lande on 15.11.2026.
//

#include "TBankAccount.h"

#include <chrono>
#include <random>
#include <utility>

TBankAccount::TBankAccount(std::string accountNumber, EBankAccountType accountType, std::string ownerFirstName, std::string ownerLastName, time_t creationTimestamp)
    : accountNumber(std::move(accountNumber)), accountType(accountType), ownerFirstName(std::move(ownerFirstName)), ownerLastName(std::move(ownerLastName)), creationTimestamp(creationTimestamp) {

    // Initializes random number generator to generate balance
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 0);

    if (accountType == EBankAccountType::Loan) {
        dis = std::uniform_int_distribution<>(-50000, -25000);
    } else if (accountType == EBankAccountType::Credit) {
        dis = std::uniform_int_distribution<>(-1000, -0);
    } else {
        dis = std::uniform_int_distribution<>(0, 1000);
    }
    balance = static_cast<float>(dis(gen));
}

std::string TBankAccount::GetAccountNumber() {
    return accountNumber;
}

EBankAccountType TBankAccount::GetAccountType() {
    return accountType;
}

std::string TBankAccount::GetOwnerFirstName() {
    return ownerFirstName;
}

std::string TBankAccount::GetOwnerLastName() {
    return ownerLastName;
}

time_t TBankAccount::GetCreationTimestamp() {
    return creationTimestamp;
}

float TBankAccount::GetBalance() {
    return balance;
}

std::string TBankAccount::AccountTypeToString(EBankAccountType accountType) {
    if (accountType == EBankAccountType::Savings) return "Savings";
    if (accountType == EBankAccountType::Credit)  return "Credit";
    if (accountType == EBankAccountType::Pension) return "Pension";
    if (accountType == EBankAccountType::Loan)    return "Loan";
    return "Checking";
}
