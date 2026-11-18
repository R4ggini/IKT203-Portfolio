//
// Created by Lande on 15.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TBANKACCOUNT_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TBANKACCOUNT_H

#include <string>
#include <ctime>
#include "EBankAccountType.h"

class TBankAccount {
public:
    TBankAccount(std::string accountNumber, EBankAccountType accountType,
        std::string ownerFirstName, std::string ownerLastName, time_t creationTimestamp);

    std::string GetAccountNumber();
    EBankAccountType GetAccountType();
    std::string GetOwnerFirstName();
    std::string GetOwnerLastName();
    time_t GetCreationTimestamp();
    float GetBalance();
    std::string AccountTypeToString(EBankAccountType accountType);
private:
    std::string accountNumber;
    EBankAccountType accountType;
    std::string ownerFirstName;
    std::string ownerLastName;
    time_t creationTimestamp;
    float balance;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TBANKACCOUNT_H
