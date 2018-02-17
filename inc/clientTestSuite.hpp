/*
 * Copyright © 2017 Vincent Lachenal
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */
#ifndef CLIENT_TEST_SUITE_HPP
#define CLIENT_TEST_SUITE_HPP

#include "dataset.hpp"

#include "logger/logger.hpp"
#include "threadPool.hpp"

#include <string>
#include <list>
#include <atomic>



/*!
 * \brief Test suite abstract class
 *
 * \author Vincent Lachenal
 */
template<typename T, typename C>
class ClientTestSuite {

  // Attributes +
protected:
  /*! Data set */
  DataSet& _data;

  /*! CPU */
  std::string _cpu;

  /*! Memory */
  std::string _memory;

  /*! Test suite customers */
  std::vector<T> _customers;

  /*! Calls */
  std::vector<C> _calls;

  /*! Number of simultaneous calls */
  int _nbThread;

  /*! Test suite comment */
  std::string _comment;

private:
  /*! Mutex */
  std::mutex _mutex;
  // Attributes -


  // Constructors +
protected:
  /*!
   * \ref ClientTestSuite default constructor
   */
  ClientTestSuite(): _data(DataSet::getInstance()), _cpu(), _memory(), _customers(), _calls(), _nbThread(1), _comment() {
    // Nothing to do
  }
  // Constructors -


  // Destructor +
public:
  /*!
   * \ref ClientTestSuite destructor
   */
  ~ClientTestSuite() {
    // Nothing to do
  }
  // Destructor -


  // Methods +
public:
  /*!
   * Delete all customers
   */
  virtual void deleteAll() = 0;

  /*!
   * Initialize test suite: fill customers list from data set
   */
  virtual void initializeTestSuite() = 0;

  /*!
   * Create customer
   *
   * \param customer the customer to create
   * \param requestSeq the request sequence
   *
   * \return the call statitics
   */
  virtual C createCustomer(T& customer, int requestSeq) = 0;

  /*!
   * List all customers
   *
   * \param requestSeq the request sequence
   *
   * \return the call statitics
   */
  virtual C listAll(uint32_t requestSeq) = 0;

  /*!
   * Get customer details
   *
   * \param requestSeq the request sequence
   * \param customerthe customer customer
   *
   * \return the call statitics
   */
  virtual C getDetails(const T& customer, int requestSeq) = 0;

  /*!
   * Consolidate statistics
   */
  virtual void consolidateStats() = 0;

  /*!
   * Logger accessor
   *
   * \return the logger
   */
  virtual const anch::logger::Logger& logger() const = 0;

  /*!
   * Run test suite
   *
   * \param nbThread the number of simultaneous calls
   * \param comment the test suite comment
   */
  void runTest(int nbThread, const std::string& comment) {
    // Initialization +
    logger().info("Initialization");
    _comment = comment;
    _nbThread = nbThread;
    initializeTestSuite();
    deleteAll();
    logger().info("Found ", _customers.size(), " customers in data set");
    // Initialization -

    // Customer creations +
    {
      logger().info("Customers creation");
      std::atomic_uint seq(1);
      anch::ThreadPool threadPool(_nbThread);
      for(T& customer : _customers) {
	threadPool.add([&seq, this](T& cust) {
	    C call = this->createCustomer(cust, seq.fetch_add(1));
	    std::lock_guard<std::mutex> lock(this->_mutex);
	    this->_calls.push_back(call);
	  }, customer);
      }
      threadPool.start();
      threadPool.awaitTermination(std::chrono::seconds(-1));
    }
    // Customer creations -

    // List all +
    {
      logger().info("List all");
      std::atomic_uint seq(1);
      anch::ThreadPool threadPool(_nbThread);
      for(std::size_t i = 0 ; i < _customers.size() ; ++i) {
	threadPool.add([&seq, this]() {
	    C call = this->listAll(seq.fetch_add(1));
	    std::lock_guard<std::mutex> lock(this->_mutex);
	    this->_calls.push_back(call);
	  }
	  );
      }
      threadPool.start();
      threadPool.awaitTermination(std::chrono::seconds(-1));
    }
    // List all -

    // Get details +
    {
      logger().info("Get details");
      std::atomic_uint seq(1);
      anch::ThreadPool threadPool(_nbThread);
      for(const T& customer : _customers) {
	threadPool.add([&seq, this](const T& cust) {
	    C call = this->getDetails(cust, seq.fetch_add(1));
	    std::lock_guard<std::mutex> lock(this->_mutex);
	    this->_calls.push_back(call);
	  }, customer);
      }
      threadPool.start();
      threadPool.awaitTermination(std::chrono::seconds(-1));
    }
    // Get details -

    consolidateStats();
    deleteAll();
  }
  // Methods -


  // Accessors +
public:
  /*!
   * Data set getter
   *
   * \return the data
   */
  inline const DataSet& getData() const {
    return _data;
  }

  /*!
   * Data set setter
   *
   * \param data the data to set
   */
  inline void setData(const DataSet& data) {
    _data = data;
  }

  /*!
   * CPU information getter
   *
   * \return the cpu
   */
  inline const std::string& getCpu() const {
    return _cpu;
  }

  /*!
   * CPU information setter
   *
   * \param cpu the cpu to set
   */
  inline void setCpu(const std::string& cpu) {
    _cpu = cpu;
  }

  /*!
   * RAM informations getter
   *
   * \return the memory
   */
  inline const std::string& getMemory() const {
    return _memory;
  }

  /*!
   * RAM informations setter
   *
   * \param memory the memory to set
   */
  inline void setMemory(const std::string& memory) {
    _memory = memory;
  }

  /*!
   * Customers getter
   *
   * \return the customers
   */
  inline std::list<T>& getCustomers() {
    return _customers;
  }

  /*!
   * Customers setter
   *
   * \param customers the customers to set
   */
  inline void setCustomers(const std::list<T>& customers) {
    _customers = customers;
  }

  /*!
   * Calls getter
   *
   * \return the calls
   */
  inline std::list<C> getCalls() {
    return _calls;
  }

  /*!
   * Calls setter
   *
   * \param calls the calls to set
   */
  inline void setCalls(const std::list<C> calls) {
    _calls = calls;
  }

  /*!
   * Number of simultaneous calls getter
   *
   * \return the number of simultaneous calls
   */
  inline int getNbThread() const {
    return _nbThread;
  }

  /*!
   * Number of simultaneous calls setter
   *
   * \param nbThread the number of simultaneous calls to set
   */
  inline void setNbThread(int nbThread) {
    _nbThread = nbThread;
  }

  /*!
   * Test suite comment getter
   *
   * \return the comment
   */
  inline const std::string& getComment() const {
    return _comment;
  }

  /*!
   * Test suite comment setter
   *
   * \param comment the comment to set
   */
  inline void setComment(const std::string& comment) {
    _comment = comment;
  }
  // Accessors -

};

#endif // CLIENT_TEST_SUITE_HPP
