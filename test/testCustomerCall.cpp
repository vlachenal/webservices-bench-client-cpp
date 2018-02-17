#include <iostream>

#include "thriftClientTestSuite.hpp"

int
main(void) {
  std::cout << "Enter on testCustomerCall" << std::endl;
  ThriftClientTestSuite& suite = ThriftClientTestSuite::getInstance();
  suite.initializeTestSuite();
  std::cout << "Client has been successfully initialized" << std::endl;
  Customer cust;
  cust.firstName = "Chuck";
  cust.lastName = "Norris";
  cust.email = "chuck.norris@yopmail.com";
  cust.birthDate = 666;
  cust.address.lines.push_back("1 rue des Nuages");
  cust.address.zipCode = "33500";
  cust.address.city = "Libourne";
  cust.address.country = "France";
  Phone phone;
  phone.number = "+33836656565";
  phone.type = PhoneType::LANDLINE;
  cust.phones.push_back(phone);
  std::cout << "Create " << cust.firstName << ' ' << cust.lastName << std::endl;
  ClientCall call = suite.createCustomer(cust, -1);
  if(!call.ok) {
    std::cerr << "Call has failed: " << call.errMsg << std::endl;
    return 1;
  }
  std::cout << "New customer ID is " << cust.id << std::endl;
  std::cout << "Exit testCustomerCall" << std::endl;
  return 0;
}
