/*
 * Copyright © 2017 Vincent Lachenal
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */
#include "thriftClientTestSuite.hpp"

#include "logger/loggerFactory.hpp"

#include <string>
#include <iostream>

static const anch::logger::Logger& LOG = anch::logger::LoggerFactory::getLogger("main");


/*!
 * Application entry point
 *
 * \param argc the number of parameters
 * \param argv the parameters
 *
 * \return the application return code
 */
int
main(int argc, char* argv[]) {
  if(argc < 2) {
    LOG.error("Invalid number of arguments");
    return 1;
  }
  int nbThreads = std::atoi(argv[1]);
  if(nbThreads < 1) {
    LOG.error("Invalid number of threads ", nbThreads);
    return 2;
  }
  std::string comment;
  if(argc > 2) {
    comment = argv[2];
  }
  LOG.info("Enter in test with ", nbThreads, " threads and comment: ", comment);
  ThriftClientTestSuite& testSuite = ThriftClientTestSuite::getInstance();
  testSuite.runTest(nbThreads, comment);
  return 0;
}
