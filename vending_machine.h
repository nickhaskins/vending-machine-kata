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

enum Product {
	COLA,
	CHIPS,
	CANDY
};

class VendingMachine {
 public:
  VendingMachine();

  std::string GetDisplay() const;

  void AddCoin(Coin coin);

  std::vector<Coin> GetCoinReturn();

  void PurchaseProduct(Product product);

  std::vector<std::string> GetDispensedProducts();

 private:
  int current_amount_;
};


}  // namespace vending_machine_kata


#endif  // VENDING_MACHINE_KATA_VENDING_MACHINE_H_
