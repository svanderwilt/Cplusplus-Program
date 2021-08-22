#include "InvestmentAccount.h"

// Constructor
InvestmentAccount::InvestmentAccount(double t_initialInvestment, double t_monthlyDeposit, double t_interestRate, int t_numYears) {
	m_initialInvestment = t_initialInvestment;
	m_monthlyDeposit = t_monthlyDeposit;
	m_interestRate = t_interestRate;
	m_numYears = t_numYears;
}

// getter for initialInvestment
float InvestmentAccount::initialInvestment() const { return m_initialInvestment; }

// getter for monthlyDeposit
float InvestmentAccount::monthlyDeposit() const { return m_monthlyDeposit; }

// getter for interestRate
float InvestmentAccount::interestRate() const { return m_interestRate; }

// getter for numYears
int InvestmentAccount::numYears() const { return m_numYears; }