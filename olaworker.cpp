#include "olaworker.h"

#include <ola/Callback.h>
#include <ola/client/OlaClient.h>
#include <ola/e131/E131ConfigMessages.pb.h>

#include <QDebug>
#include <QThread>
#include <string>
#include <vector>

using ola::NewSingleCallback;
using std::string;
using std::vector;

bool lessThan(const E131Source &e1, const E131Source &e2) {
  return e1.cid < e2.cid;
}

OLAWorker::OLAWorker(QObject *parent)
    : QObject(parent),
      got_devices_(false) {
}

OLAWorker::~OLAWorker() {}

bool OLAWorker::Init() {
  if (!m_wrapper.Setup()) {
    return false;
  }
  return true;
}

void OLAWorker::process() {
  qDebug() << "OLA Client thread running";
  m_wrapper.GetClient()->FetchDeviceInfo(
        ola::OLA_PLUGIN_E131,
        NewSingleCallback(this, &OLAWorker::HandleDevices));
  m_wrapper.GetSelectServer()->Run();
  emit finished();
}

void OLAWorker::RefreshDiscoveredE131Sources() {
  if (!got_devices_)
    return;

  ola::plugin::e131::Request request;
  request.set_type(ola::plugin::e131::Request::E131_SOURCES_LIST);
  ola::plugin::e131::SourceListRequest *source_list_request =
      request.mutable_source_list();
  (void) source_list_request;  // no options for now.

  string request_string;
  request.SerializeToString(&request_string);
  m_wrapper.GetClient()->ConfigureDevice(
    device_alias_,
    request_string,
    NewSingleCallback(this, &OLAWorker::HandleConfigResponse));
}

void OLAWorker::HandleDevices(
    const ola::client::Result &result,
    const vector<ola::client::OlaDevice> &devices) {
  if (!result.Success()) {
    qWarning() << "Failed to get list of E1.33 devices";
    return;
  }

  switch (devices.size()) {
    case 0:
      qWarning() << "No E1.31 devices found";
      return;
    case 1:
      break;
    default:
      qWarning() << "More than one E1.31 device found, we'll use the first one";
      break;
  }

  device_alias_ = devices[0].Alias();
  got_devices_ = true;
}

void OLAWorker::HandleConfigResponse(const ola::client::Result &result,
                                     const std::string &reply) {
  if (!result.Success()) {
    qWarning() << "Failed to get list of E1.33 devices";
    return;
  }

  ola::plugin::e131::Reply reply_pb;
  if (!reply_pb.ParseFromString(reply)) {
    qWarning() << "Protobuf parsing failed";
    return;
  }

  if (reply_pb.type() != ola::plugin::e131::Reply::E131_SOURCES_LIST) {
    qWarning() << "Unknown reply: " << reply_pb.type();
    return;
  }

  if (!reply_pb.has_source_list()) {
    qWarning() << "Reply is missing source_list";
    return;
  }

  if (reply_pb.source_list().unsupported()) {
    qWarning() << "E1.31 discovery isn't enabled.";
    return;
  }

  QVector<E131Source> sources;

  for (int i = 0; i < reply_pb.source_list().source_size(); i++) {
    const ola::plugin::e131::SourceEntry &entry =
        reply_pb.source_list().source(i);

    E131Source source;
    source.cid = ola::acn::CID::FromString(entry.cid());
    ola::network::IPV4Address::FromString(entry.ip_address(),
                                          &source.ip_address);
    source.source_name = entry.source_name();

    for (int j = 0; j < entry.universe_size(); j++) {
      source.universes.push_back(entry.universe(j));
    }

    qSort(source.universes.begin(), source.universes.end());
    sources.push_back(source);
  }

  qSort(sources.begin(), sources.end(), lessThan);
  emit E131SourceList(sources);
}




