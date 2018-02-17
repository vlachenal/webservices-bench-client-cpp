/*
 * Copyright © 2017 Vincent Lachenal
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */
#include "dataset.hpp"

#include "logger/loggerFactory.hpp"

#include <fstream>
#include <memory>

#include "transport/TBufferTransports.h"
#include "protocol/TJSONProtocol.h"

using apache::thrift::transport::TMemoryBuffer;
using apache::thrift::protocol::TJSONProtocol;

const anch::logger::Logger& LOG = anch::logger::LoggerFactory::getLogger("dataset");

// Constructors +
DataSet::DataSet(): _customers() {
  LOG.debug("Initialize dataset");
  const anch::resource::Resource& res = anch::resource::Resource::getResource("application.conf");
  std::string file;
  bool found = res.getParameter(file, "filename", "dataset");
  if(!found) {
    throw std::runtime_error("Missing dataset.filename entry in application.conf");
  }
  LOG.info("Parse dataset file: ", file);
  std::ifstream ifs(file);
  std::string line;
  uint8_t* buffer = new uint8_t[10000];
  while(std::getline(ifs, line)) {
    if(line.empty()) {
      continue;
    }
    std::shared_ptr<TMemoryBuffer> trans = std::make_shared<TMemoryBuffer>(buffer, 10000);
    std::shared_ptr<TJSONProtocol> proto = std::make_shared<TJSONProtocol>(trans);
    std::strncpy(reinterpret_cast<char*>(buffer), line.data(), line.size());
    Customer cust;
    cust.read(proto.get());
    LOG.trace("Found customer: ", cust.firstName, ' ', cust.lastName);
    _customers.push_back(cust);
  }
  LOG.info("File: ", file, " has been successfully parsed");
}
// Constructors -

// Destructor +
DataSet::~DataSet() {
  _customers.clear();
}
// Destructor -
