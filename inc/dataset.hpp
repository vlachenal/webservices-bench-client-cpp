/*
 * Copyright © 2017 Vincent Lachenal
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */
#ifndef DATASET_HPP
#define DATASET_HPP

#include "singleton.hpp"

#include "customer_types.h"

#include <vector>


/*!
 * \brief Test suite dataset
 *
 * \author Vincent Lachenal
 */
class DataSet: public anch::Singleton<DataSet> {
  friend anch::Singleton<DataSet>;

  // Attributes +
private:
  /*! Dataset customers list */
  std::vector<Customer> _customers;
  // Attributes -


  // Constructors +
private:
  /*!
   * \ref DataSet private constructor
   */
  DataSet();
  // Constructors -


  // Destructor +
private:
  /*!
   * \ref DataSet destructor
   */
  virtual ~DataSet();
  // Destructor -


  // Methods +
public:
  /*!
   * Get Thrift data
   *
   * \return the test suite data set
   */
  inline std::vector<Customer>& getData() {
    return _customers;
  }
  // Methods -

};

#endif // DATASET_HPP
