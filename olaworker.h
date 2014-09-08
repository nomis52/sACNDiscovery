#ifndef OLAWORKER_H_
#define OLAWORKER_H_

#include <stdint.h>

#include <QObject>
#include <ola/client/ClientWrapper.h>
#include <ola/network/IPV4Address.h>
#include <ola/acn/CID.h>

#include <string>
#include <vector>

struct E131Source {
  ola::acn::CID cid;
  ola::network::IPV4Address ip_address;
  std::string source_name;
  std::vector<uint16_t> universes;
};

bool lessThan(const E131Source &e1, const E131Source &e2);


class OLAWorker : public QObject {
  Q_OBJECT

 public:
  explicit OLAWorker(QObject *parent = 0);
  ~OLAWorker();

  bool Init();

  void RefreshDiscoveredE131Sources();

  // Callback for the OLA Client
  void HandleDevices(const ola::client::Result &result,
                     const std::vector<ola::client::OlaDevice> &devices);

  void HandleConfigResponse(const ola::client::Result &result,
                            const std::string &reply);

 signals:
  void finished();
  void E131SourceList(const QVector<E131Source> &sources);

 public slots:
  void process();

 private:
  ola::client::OlaClientWrapper m_wrapper;
  unsigned int device_alias_;
  bool got_devices_;
};
#endif  // OLAWORKER_H_
