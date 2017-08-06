#ifndef VENDING_MACHINE_KATA_VENDING_MACHINE_H_
#define VENDING_MACHINE_KATA_VENDING_MACHINE_H_

#include <string>
#include <vector>

namespace vending_machine_kata {


enum Coin {
	PENNY,
	NICKEL,
	DIME,
	QUARTER
};

class VendingMachine {
 public:
  VendingMachine();

  std::string GetDisplay() const;

  void AddCoin(Coin coin);

  std::vector<Coin> GetCoinReturn();

 private:
  int current_amount_;
};


}  // namespace vending_machine_kata


#endif  // VENDING_MACHINE_KATA_VENDING_MACHINE_H_
