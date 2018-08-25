/*
 * Copyright © 2017 Vincent Lachenal
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */
#include "thriftClientTestSuite.hpp"

#include "dataset.hpp"

#include "logger/loggerFactory.hpp"

#include "StatsService.h"

#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>


using apache::thrift::transport::TTransport;
using apache::thrift::transport::TSocket;
using apache::thrift::transport::TBufferedTransport;
using apache::thrift::protocol::TProtocol;
using apache::thrift::protocol::TCompactProtocol;
using apache::thrift::protocol::TMultiplexedProtocol;


const std::string THRIFT_PROTO("thrift-cpp");

// Thrift client configuration +
// Constructors +
ThriftClientConfig::ThriftClientConfig(const std::string& hostname, uint16_t port): _hostname(hostname), _port(port) {
  // Nothing to do
}

ThriftClientConfig::ThriftClientConfig(const ThriftClientConfig& other): _hostname(other._hostname), _port(other._port) {
  // Nothing to do
}
// Constructors -

// Destructors +
ThriftClientConfig::~ThriftClientConfig() {
  // Nothing to do
}
// Destructors -
// Thrift client configuration -

// Thrift poolable client +
// Constructors +
PoolableServiceClient::PoolableServiceClient(const ThriftClientConfig& config) {
  std::shared_ptr<TTransport> socket(new TSocket(config.getHostname(), config.getPort()));
  _transport = std::shared_ptr<TTransport>(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> proto(new TCompactProtocol(_transport));
  _custService = new CustomerServiceClient(std::make_shared<TMultiplexedProtocol>(proto, "customer"));
  _statsService = new StatsServiceClient(std::make_shared<TMultiplexedProtocol>(proto, "stats"));
  _transport->open();
  _valid = true;
}
// Constructors -

// Destructors +
PoolableServiceClient::~PoolableServiceClient() {
  delete _statsService;
  delete _custService;
  _transport->close();
}
// Destructors -
// Thrift poolable client -

const anch::logger::Logger& ThriftClientTestSuite::LOG = anch::logger::LoggerFactory::getLogger("thrift-client-test-suite");


// Thrift client test suite +
// Constructors +
ThriftClientTestSuite::ThriftClientTestSuite(): ClientTestSuite<Customer,ClientCall>(), _host("localhost"), _port(9090), _pool(NULL) {
  const anch::resource::Resource& res = anch::resource::Resource::getResource("application.conf");
  bool found = res.getParameter(_host, "server.host", "client");
  if(!found) {
    LOG.warn("server.host is not deifined in application.conf. locahost will be used.");
  }
  std::string port;
  found = res.getParameter(port, "server.port", "client");
  if(!found) {
    LOG.warn("server.port is not deifined in application.conf. 9090 will be used.");
  } else {
    try {
      _port = std::stoul(port);
    } catch(const std::invalid_argument& e) {
      LOG.warn("server.port is not an integer: ", port, ". Keep using 9090.");
    } catch(const std::out_of_range& e) {
      LOG.warn("server.port is not an unsigned integer: ", port, ". Keep using 9090.");
    }
  }
}
// Constructors -


// Destructor +
ThriftClientTestSuite::~ThriftClientTestSuite() {
  delete _pool;
}
// Destructor -


// Methods +
void
ThriftClientTestSuite::deleteAll() {
  auto res = _pool->borrowResource();
  PoolableServiceClient& client = res.get();
  try {
    client.customer().deleteAll();
  } catch(const CustomerException& e) {
    LOG.error("Unable to remove all entries from database: ", e);
  } catch(const std::exception& e) {
    client.setValid(false);
    LOG.error("Error while customer.deleteAll: ", e.what());
  } catch(...) {
    client.setValid(false);
    LOG.error("Unexpected error");
  }
}

void
ThriftClientTestSuite::initializeTestSuite() {
  _customers = _data.getData();
  ThriftClientConfig config(_host, _port);
  _pool = new CustomerClientPool(config, _nbThread, _nbThread);
}

ClientCall
ThriftClientTestSuite::createCustomer(Customer& customer, int requestSeq) {
  CreateRequest req;
  req.customer = customer;
  req.header.requestSeq = requestSeq;
  req.header.mapper = Mapper::MANUAL;
  ClientCall call;
  call.protocol = THRIFT_PROTO;
  call.method = "create";
  call.requestSeq = requestSeq;
  call.ok = false;
  call.clientStart = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  auto res = _pool->borrowResource(); // keep resource reference not to release it immediately
  PoolableServiceClient& client = res.get();
  try {
    client.customer().create(customer.id, req);
    call.ok = true;
  } catch(const CustomerException& e) {
    call.errMsg = e.what();
  } catch(const std::exception& e) {
    call.errMsg = e.what();
    client.setValid(false);
    LOG.error("Error while customer.createCustomer: ", e.what());
  } catch(...) {
    call.errMsg = "Unexpected error";
    client.setValid(false);
    LOG.error("Unexpected error");
  }
  call.clientEnd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  return call;
}

ClientCall
ThriftClientTestSuite::listAll(uint32_t requestSeq) {
  ListAllRequest req;
  req.header.requestSeq = requestSeq;
  req.header.mapper = Mapper::MANUAL;
  ClientCall call;
  call.protocol = THRIFT_PROTO;
  call.method = "list";
  call.requestSeq = requestSeq;
  call.ok = false;
  std::vector<Customer> customers;
  call.clientStart = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  auto res = _pool->borrowResource(); // keep resource reference not to release it immediately
  PoolableServiceClient& client = res.get();
  try {
    client.customer().listCustomers(customers, req);
    call.ok = true;
  } catch(const CustomerException& e) {
    call.errMsg = e.what();
  } catch(const std::exception& e) {
    call.errMsg = e.what();
    client.setValid(false);
    LOG.error("Error while customer.listAll: ", e.what());
  } catch(...) {
    call.errMsg = "Unexpected error";
    client.setValid(false);
    LOG.error("Unexpected error");
  }
  call.clientEnd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  if(customers.empty()) {
    call.ok = false;
    call.errMsg = "Response is empty";
  } else if(customers.size() != _customers.size()) {
    LOG.warn("Customers size should be ", _customers.size(), " instead of ", customers.size());
  }
  return call;
}

ClientCall
ThriftClientTestSuite::getDetails(const Customer& customer, int requestSeq) {
  GetRequest req;
  req.header.requestSeq = requestSeq;
  req.header.mapper = Mapper::MANUAL;
  req.id = customer.id;
  ClientCall call;
  call.protocol = THRIFT_PROTO;
  call.method = "get";
  call.requestSeq = requestSeq;
  call.ok = false;
  Customer cust;
  call.clientStart = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  auto res = _pool->borrowResource(); // keep resource reference not to release it immediately
  PoolableServiceClient& client = res.get();
  try {
    client.customer().get(cust, req);
    call.ok = true;
  } catch(const CustomerException& e) {
    call.errMsg = e.what();
  } catch(const std::exception& e) {
    call.errMsg = e.what();
    client.setValid(false);
    LOG.error("Error while customer.getDetails: ", e.what());
  } catch(...) {
    call.errMsg = "Unexpected error";
    client.setValid(false);
    LOG.error("Unexpected error");
  }
  call.clientEnd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  if(cust.id == "") {
    call.ok = false;
    call.errMsg = "Customer " + customer.id + " has not been found";
  } else if(cust.id != customer.id) {
    LOG.warn("Customer should have ", customer.id, " instead of ", cust.id);
  }
  return call;
}

void
ThriftClientTestSuite::consolidateStats() {
  for(ClientCall call: _calls) {
    if(!call.ok) {
      LOG.error("Found error in calls: ", call.errMsg);
    }
  }

  TestSuite suite;
  // Gather system informations +
  suite.jvm = "8.2"; // \todo GCC version
  suite.vendor = "GNU GCC";
  suite.osFamily = "Linux";
  suite.osVersion = "4.18.4"; // \todo linux version
  suite.cpu = _cpu;
  suite.memory = _memory;
  // Gather system informations -
  // Gather test suite informations +
  suite.nbThread = _nbThread;
  suite.protocol = THRIFT_PROTO;
  suite.compression = "none";
  suite.comment = _comment;
  suite.calls = _calls;
  suite.mapper = Mapper::MANUAL;
  // Gather test suite informations -

  auto res = _pool->borrowResource(); // keep resource reference not to release it immediately
  PoolableServiceClient& client = res.get();
  try {
    client.stats().consolidate(suite);
    client.stats().purge();
  } catch(const StatsException& e) {
    LOG.error("Unable to consolidate statistics: ", e);
  } catch(const std::exception& e) {
    LOG.error("Unexpected error: ", e.what());
  } catch(...) {
    LOG.error("Unexpected error");
  }
}

const anch::logger::Logger&
ThriftClientTestSuite::logger() const {
  return LOG;
}
// Methods -
// Thrift client test suite -
