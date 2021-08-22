/**
 * InvestmentAccount
 *
 * stores account details
 *
 * @author Scott Vanderwilt
 * Contact: scott.vanderwilt@snhu.edu
 *
 */
#ifndef INVESTMENTACCOUNT_H_
#define INVESTMENTACCOUNT_H_
#include <vector>
class InvestmentAccount
{
private:
		double m_initialInvestment;
		double m_monthlyDeposit;
		double m_interestRate;
		int m_numYears;

public:
		InvestmentAccount(double, double, double, int);
		float initialInvestment() const;
		float monthlyDeposit() const;
		float interestRate() const;
		int numYears() const;

};
#endif
