/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef StatsService_H
#define StatsService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "customer_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class StatsServiceIf {
 public:
  virtual ~StatsServiceIf() {}

  /**
   * Consolidate statistics
   * 
   * @param test the test suite
   * 
   * @throws StatsException any error
   * @throws TException unexpected error
   * 
   * @param test
   */
  virtual void consolidate(const TestSuite& test) = 0;

  /**
   * Purge server side statistics
   * 
   * @throws StatsException any error
   * @throws TException unexpected error
   */
  virtual void purge() = 0;
};

class StatsServiceIfFactory {
 public:
  typedef StatsServiceIf Handler;

  virtual ~StatsServiceIfFactory() {}

  virtual StatsServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(StatsServiceIf* /* handler */) = 0;
};

class StatsServiceIfSingletonFactory : virtual public StatsServiceIfFactory {
 public:
  StatsServiceIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<StatsServiceIf>& iface) : iface_(iface) {}
  virtual ~StatsServiceIfSingletonFactory() {}

  virtual StatsServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(StatsServiceIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<StatsServiceIf> iface_;
};

class StatsServiceNull : virtual public StatsServiceIf {
 public:
  virtual ~StatsServiceNull() {}
  void consolidate(const TestSuite& /* test */) {
    return;
  }
  void purge() {
    return;
  }
};

typedef struct _StatsService_consolidate_args__isset {
  _StatsService_consolidate_args__isset() : test(false) {}
  bool test :1;
} _StatsService_consolidate_args__isset;

class StatsService_consolidate_args {
 public:

  StatsService_consolidate_args(const StatsService_consolidate_args&);
  StatsService_consolidate_args(StatsService_consolidate_args&&);
  StatsService_consolidate_args& operator=(const StatsService_consolidate_args&);
  StatsService_consolidate_args& operator=(StatsService_consolidate_args&&);
  StatsService_consolidate_args() {
  }

  virtual ~StatsService_consolidate_args() throw();
  TestSuite test;

  _StatsService_consolidate_args__isset __isset;

  void __set_test(const TestSuite& val);

  bool operator == (const StatsService_consolidate_args & rhs) const
  {
    if (!(test == rhs.test))
      return false;
    return true;
  }
  bool operator != (const StatsService_consolidate_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const StatsService_consolidate_args & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};


class StatsService_consolidate_pargs {
 public:


  virtual ~StatsService_consolidate_pargs() throw();
  const TestSuite* test;

  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};

typedef struct _StatsService_consolidate_result__isset {
  _StatsService_consolidate_result__isset() : error(false) {}
  bool error :1;
} _StatsService_consolidate_result__isset;

class StatsService_consolidate_result {
 public:

  StatsService_consolidate_result(const StatsService_consolidate_result&);
  StatsService_consolidate_result(StatsService_consolidate_result&&);
  StatsService_consolidate_result& operator=(const StatsService_consolidate_result&);
  StatsService_consolidate_result& operator=(StatsService_consolidate_result&&);
  StatsService_consolidate_result() {
  }

  virtual ~StatsService_consolidate_result() throw();
  StatsException error;

  _StatsService_consolidate_result__isset __isset;

  void __set_error(const StatsException& val);

  bool operator == (const StatsService_consolidate_result & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    return true;
  }
  bool operator != (const StatsService_consolidate_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const StatsService_consolidate_result & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};

typedef struct _StatsService_consolidate_presult__isset {
  _StatsService_consolidate_presult__isset() : error(false) {}
  bool error :1;
} _StatsService_consolidate_presult__isset;

class StatsService_consolidate_presult {
 public:


  virtual ~StatsService_consolidate_presult() throw();
  StatsException error;

  _StatsService_consolidate_presult__isset __isset;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);

};


class StatsService_purge_args {
 public:

  StatsService_purge_args(const StatsService_purge_args&);
  StatsService_purge_args(StatsService_purge_args&&);
  StatsService_purge_args& operator=(const StatsService_purge_args&);
  StatsService_purge_args& operator=(StatsService_purge_args&&);
  StatsService_purge_args() {
  }

  virtual ~StatsService_purge_args() throw();

  bool operator == (const StatsService_purge_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const StatsService_purge_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const StatsService_purge_args & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};


class StatsService_purge_pargs {
 public:


  virtual ~StatsService_purge_pargs() throw();

  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};

typedef struct _StatsService_purge_result__isset {
  _StatsService_purge_result__isset() : error(false) {}
  bool error :1;
} _StatsService_purge_result__isset;

class StatsService_purge_result {
 public:

  StatsService_purge_result(const StatsService_purge_result&);
  StatsService_purge_result(StatsService_purge_result&&);
  StatsService_purge_result& operator=(const StatsService_purge_result&);
  StatsService_purge_result& operator=(StatsService_purge_result&&);
  StatsService_purge_result() {
  }

  virtual ~StatsService_purge_result() throw();
  StatsException error;

  _StatsService_purge_result__isset __isset;

  void __set_error(const StatsException& val);

  bool operator == (const StatsService_purge_result & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    return true;
  }
  bool operator != (const StatsService_purge_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const StatsService_purge_result & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};

typedef struct _StatsService_purge_presult__isset {
  _StatsService_purge_presult__isset() : error(false) {}
  bool error :1;
} _StatsService_purge_presult__isset;

class StatsService_purge_presult {
 public:


  virtual ~StatsService_purge_presult() throw();
  StatsException error;

  _StatsService_purge_presult__isset __isset;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);

};

template <class Protocol_>
class StatsServiceClientT : virtual public StatsServiceIf {
 public:
  StatsServiceClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
    setProtocolT(prot);
  }
  StatsServiceClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    setProtocolT(iprot,oprot);
  }
 private:
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
  setProtocolT(prot,prot);
  }
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return this->piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return this->poprot_;
  }
  void consolidate(const TestSuite& test);
  void send_consolidate(const TestSuite& test);
  void recv_consolidate();
  void purge();
  void send_purge();
  void recv_purge();
 protected:
  apache::thrift::stdcxx::shared_ptr< Protocol_> piprot_;
  apache::thrift::stdcxx::shared_ptr< Protocol_> poprot_;
  Protocol_* iprot_;
  Protocol_* oprot_;
};

typedef StatsServiceClientT< ::apache::thrift::protocol::TProtocol> StatsServiceClient;

template <class Protocol_>
class StatsServiceProcessorT : public ::apache::thrift::TDispatchProcessorT<Protocol_> {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<StatsServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
  virtual bool dispatchCallTemplated(Protocol_* iprot, Protocol_* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (StatsServiceProcessorT::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef void (StatsServiceProcessorT::*SpecializedProcessFunction)(int32_t, Protocol_*, Protocol_*, void*);
  struct ProcessFunctions {
    ProcessFunction generic;
    SpecializedProcessFunction specialized;
    ProcessFunctions(ProcessFunction g, SpecializedProcessFunction s) :
      generic(g),
      specialized(s) {}
    ProcessFunctions() : generic(NULL), specialized(NULL) {}
  };
  typedef std::map<std::string, ProcessFunctions> ProcessMap;
  ProcessMap processMap_;
  void process_consolidate(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_consolidate(int32_t seqid, Protocol_* iprot, Protocol_* oprot, void* callContext);
  void process_purge(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_purge(int32_t seqid, Protocol_* iprot, Protocol_* oprot, void* callContext);
 public:
  StatsServiceProcessorT(::apache::thrift::stdcxx::shared_ptr<StatsServiceIf> iface) :
    iface_(iface) {
    processMap_["consolidate"] = ProcessFunctions(
      &StatsServiceProcessorT::process_consolidate,
      &StatsServiceProcessorT::process_consolidate);
    processMap_["purge"] = ProcessFunctions(
      &StatsServiceProcessorT::process_purge,
      &StatsServiceProcessorT::process_purge);
  }

  virtual ~StatsServiceProcessorT() {}
};

typedef StatsServiceProcessorT< ::apache::thrift::protocol::TDummyProtocol > StatsServiceProcessor;

template <class Protocol_>
class StatsServiceProcessorFactoryT : public ::apache::thrift::TProcessorFactory {
 public:
  StatsServiceProcessorFactoryT(const ::apache::thrift::stdcxx::shared_ptr< StatsServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< StatsServiceIfFactory > handlerFactory_;
};

typedef StatsServiceProcessorFactoryT< ::apache::thrift::protocol::TDummyProtocol > StatsServiceProcessorFactory;

class StatsServiceMultiface : virtual public StatsServiceIf {
 public:
  StatsServiceMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<StatsServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~StatsServiceMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<StatsServiceIf> > ifaces_;
  StatsServiceMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<StatsServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void consolidate(const TestSuite& test) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->consolidate(test);
    }
    ifaces_[i]->consolidate(test);
  }

  void purge() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->purge();
    }
    ifaces_[i]->purge();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
template <class Protocol_>
class StatsServiceConcurrentClientT : virtual public StatsServiceIf {
 public:
  StatsServiceConcurrentClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
    setProtocolT(prot);
  }
  StatsServiceConcurrentClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    setProtocolT(iprot,oprot);
  }
 private:
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
  setProtocolT(prot,prot);
  }
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return this->piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return this->poprot_;
  }
  void consolidate(const TestSuite& test);
  int32_t send_consolidate(const TestSuite& test);
  void recv_consolidate(const int32_t seqid);
  void purge();
  int32_t send_purge();
  void recv_purge(const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< Protocol_> piprot_;
  apache::thrift::stdcxx::shared_ptr< Protocol_> poprot_;
  Protocol_* iprot_;
  Protocol_* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

typedef StatsServiceConcurrentClientT< ::apache::thrift::protocol::TProtocol> StatsServiceConcurrentClient;

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#include "StatsService.tcc"
#include "customer_types.tcc"

#endif
