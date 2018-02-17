/*
 * Copyright © 2017 Vincent Lachenal
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */
#ifndef THRIFT_CLIENT_TEST_SUITE_HPP
#define THRIFT_CLIENT_TEST_SUITE_HPP

#include "clientTestSuite.hpp"

#include "singleton.hpp"
#include "resourcePool.hpp"

#include "customer_types.h"
#include "CustomerService.h"

#include <thrift/protocol/TProtocol.h>


/*!
 * \brief Thrift client configuration.
 *
 * Class used by AnCH resource pool to spawn new resource.
 *
 * \author Vincent Lachenal
 */
class ThriftClientConfig {

  // Attributes +
private:
  /*! Customer service protocol */
  std::shared_ptr<apache::thrift::protocol::TProtocol> _custProto;

  ///*! Statistics protocol */
  //std::shared_ptr<TProtocol> _statsProto;
  // Attributes -

  // Constructors +
public:
  /*!
   * \ref ThriftClientConfig constructor
   *
   * \param hostname the server hostname
   * \param port the server port
   */
  ThriftClientConfig(const std::string& hostname, uint16_t port);

  /*!
   * \ref ThriftClientConfig copy constructor
   *
   * \param other the configuration to copy
   */
  ThriftClientConfig(const ThriftClientConfig& other);
  // Constructors -

  // Destructor +
public:
  /*!
   * \ref ThriftClientConfig destructor
   */
  virtual ~ThriftClientConfig();
  // Destructor -

  // Accessors +
public:
  /*!
   * Customer protocol getter
   *
   * \return protocol
   */
  inline std::shared_ptr<apache::thrift::protocol::TProtocol> getCustomerProto() const {
    return _custProto;
  }
  // Accessors -

};


/*!
 * \brief Poolable customer service client
 *
 * Add client connection validity state to reuse or not this connection
 *
 * \author Vincent Lachenal
 */
class PoolableCustomerServiceClient: public CustomerServiceClient {

  // Attributes +
private:
  /*! Valiidity state */
  bool _valid;
  // Attributes -

  // Constructors +
public:
  /*!
   * \ref PoolableCustomerClient constructor
   *
   * \param config the client configuration
   */
  PoolableCustomerServiceClient(const ThriftClientConfig& config);
  // Constructors -

  // Destructor +
public:
  /*!
   * \ref PoolableCustomerClient destructor
   */
  virtual ~PoolableCustomerServiceClient();
  // Destructor -

  // Accessors +
public:
  inline void setValid(bool valid) {
    _valid = valid;
  }

  inline bool isValid() {
    return _valid;
  }
  // Accessors -

};

/*! Client pool definition */
using CustomerClientPool = anch::ResourcePool<PoolableCustomerServiceClient,ThriftClientConfig>;


/*!
 * \brief Thrift test suite
 *
 * Provides entry to make calls to server
 *
 * \author Vincent Lachenal
 */
class ThriftClientTestSuite: public ClientTestSuite<Customer,ClientCall>, public anch::Singleton<ThriftClientTestSuite> {
  friend anch::Singleton<ThriftClientTestSuite>;

  // Attributes +
private:
  /*! \ref ClientTestSuite logger */
  static const anch::logger::Logger& LOG;

  /*! Server HOST */
  std::string _host;

  /*! Server port */
  uint16_t _port;

  /*! Customer service client pool */
  CustomerClientPool* _pool;
  // Attributes -


  // Constructors +
private:
  /*!
   * \ref ThriftClientTestSuite private constructor
   */
  ThriftClientTestSuite();
  // Constructors -


  // Destructor +
private:
  /*!
   * \ref ThriftClientTestSuite destructor
   */
  virtual ~ThriftClientTestSuite();
  // Destructor -


  // Methods +
public:
  /**
   * Delete all customers
   */
  virtual void deleteAll() override final;

  /**
   * Initialize test suite: fill customers list from data set
   */
  virtual void initializeTestSuite() override final;

  /**
   * Create customer
   *
   * @param customer the customer to create
   * @param requestSeq the request sequence
   *
   * @return the call statitics
   */
  virtual ClientCall createCustomer(Customer& customer, int requestSeq) override final;

  /**
   * List all customers
   *
   * @param requestSeq the request sequence
   *
   * @return the call statitics
   */
  virtual ClientCall listAll(uint32_t requestSeq) override final;

  /**
   * Get customer details
   *
   * @param requestSeq the request sequence
   * @param customerthe customer customer
   *
   * @return the call statitics
   */
  virtual ClientCall getDetails(const Customer& customer, int requestSeq) override final;

  /**
   * Consolidate statistics
   */
  virtual void consolidateStats() override final;

  /*!
   * Logger accessor
   *
   * \return the logger
   */
  virtual const anch::logger::Logger& logger() const;
  // Methods -

};

#endif // THRIFT_CLIENT_TEST_SUITE_HPP
