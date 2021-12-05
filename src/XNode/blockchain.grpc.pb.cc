// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: blockchain.proto

#include "blockchain.pb.h"
#include "blockchain.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace xcoin {
namespace interchange {

static const char* XNodeControl_method_names[] = {
  "/xcoin.interchange.XNodeControl/Ping",
  "/xcoin.interchange.XNodeControl/DNSSyncPeerList",
  "/xcoin.interchange.XNodeControl/NotifyPeerChange",
};

std::unique_ptr< XNodeControl::Stub> XNodeControl::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< XNodeControl::Stub> stub(new XNodeControl::Stub(channel, options));
  return stub;
}

XNodeControl::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Ping_(XNodeControl_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DNSSyncPeerList_(XNodeControl_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_NotifyPeerChange_(XNodeControl_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status XNodeControl::Stub::Ping(::grpc::ClientContext* context, const ::xcoin::interchange::PingHandshake& request, ::xcoin::interchange::PingHandshake* response) {
  return ::grpc::internal::BlockingUnaryCall< ::xcoin::interchange::PingHandshake, ::xcoin::interchange::PingHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Ping_, context, request, response);
}

void XNodeControl::Stub::async::Ping(::grpc::ClientContext* context, const ::xcoin::interchange::PingHandshake* request, ::xcoin::interchange::PingHandshake* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::xcoin::interchange::PingHandshake, ::xcoin::interchange::PingHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Ping_, context, request, response, std::move(f));
}

void XNodeControl::Stub::async::Ping(::grpc::ClientContext* context, const ::xcoin::interchange::PingHandshake* request, ::xcoin::interchange::PingHandshake* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Ping_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::PingHandshake>* XNodeControl::Stub::PrepareAsyncPingRaw(::grpc::ClientContext* context, const ::xcoin::interchange::PingHandshake& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::xcoin::interchange::PingHandshake, ::xcoin::interchange::PingHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Ping_, context, request);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::PingHandshake>* XNodeControl::Stub::AsyncPingRaw(::grpc::ClientContext* context, const ::xcoin::interchange::PingHandshake& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncPingRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status XNodeControl::Stub::DNSSyncPeerList(::grpc::ClientContext* context, const ::xcoin::interchange::DNSHandshake& request, ::xcoin::interchange::DNSHandshake* response) {
  return ::grpc::internal::BlockingUnaryCall< ::xcoin::interchange::DNSHandshake, ::xcoin::interchange::DNSHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_DNSSyncPeerList_, context, request, response);
}

void XNodeControl::Stub::async::DNSSyncPeerList(::grpc::ClientContext* context, const ::xcoin::interchange::DNSHandshake* request, ::xcoin::interchange::DNSHandshake* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::xcoin::interchange::DNSHandshake, ::xcoin::interchange::DNSHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DNSSyncPeerList_, context, request, response, std::move(f));
}

void XNodeControl::Stub::async::DNSSyncPeerList(::grpc::ClientContext* context, const ::xcoin::interchange::DNSHandshake* request, ::xcoin::interchange::DNSHandshake* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DNSSyncPeerList_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::DNSHandshake>* XNodeControl::Stub::PrepareAsyncDNSSyncPeerListRaw(::grpc::ClientContext* context, const ::xcoin::interchange::DNSHandshake& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::xcoin::interchange::DNSHandshake, ::xcoin::interchange::DNSHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_DNSSyncPeerList_, context, request);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::DNSHandshake>* XNodeControl::Stub::AsyncDNSSyncPeerListRaw(::grpc::ClientContext* context, const ::xcoin::interchange::DNSHandshake& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncDNSSyncPeerListRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status XNodeControl::Stub::NotifyPeerChange(::grpc::ClientContext* context, const ::xcoin::interchange::DNSEntry& request, ::xcoin::interchange::DNSEntry* response) {
  return ::grpc::internal::BlockingUnaryCall< ::xcoin::interchange::DNSEntry, ::xcoin::interchange::DNSEntry, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NotifyPeerChange_, context, request, response);
}

void XNodeControl::Stub::async::NotifyPeerChange(::grpc::ClientContext* context, const ::xcoin::interchange::DNSEntry* request, ::xcoin::interchange::DNSEntry* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::xcoin::interchange::DNSEntry, ::xcoin::interchange::DNSEntry, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyPeerChange_, context, request, response, std::move(f));
}

void XNodeControl::Stub::async::NotifyPeerChange(::grpc::ClientContext* context, const ::xcoin::interchange::DNSEntry* request, ::xcoin::interchange::DNSEntry* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyPeerChange_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::DNSEntry>* XNodeControl::Stub::PrepareAsyncNotifyPeerChangeRaw(::grpc::ClientContext* context, const ::xcoin::interchange::DNSEntry& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::xcoin::interchange::DNSEntry, ::xcoin::interchange::DNSEntry, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NotifyPeerChange_, context, request);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::DNSEntry>* XNodeControl::Stub::AsyncNotifyPeerChangeRaw(::grpc::ClientContext* context, const ::xcoin::interchange::DNSEntry& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNotifyPeerChangeRaw(context, request, cq);
  result->StartCall();
  return result;
}

XNodeControl::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      XNodeControl_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< XNodeControl::Service, ::xcoin::interchange::PingHandshake, ::xcoin::interchange::PingHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](XNodeControl::Service* service,
             ::grpc::ServerContext* ctx,
             const ::xcoin::interchange::PingHandshake* req,
             ::xcoin::interchange::PingHandshake* resp) {
               return service->Ping(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      XNodeControl_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< XNodeControl::Service, ::xcoin::interchange::DNSHandshake, ::xcoin::interchange::DNSHandshake, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](XNodeControl::Service* service,
             ::grpc::ServerContext* ctx,
             const ::xcoin::interchange::DNSHandshake* req,
             ::xcoin::interchange::DNSHandshake* resp) {
               return service->DNSSyncPeerList(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      XNodeControl_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< XNodeControl::Service, ::xcoin::interchange::DNSEntry, ::xcoin::interchange::DNSEntry, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](XNodeControl::Service* service,
             ::grpc::ServerContext* ctx,
             const ::xcoin::interchange::DNSEntry* req,
             ::xcoin::interchange::DNSEntry* resp) {
               return service->NotifyPeerChange(ctx, req, resp);
             }, this)));
}

XNodeControl::Service::~Service() {
}

::grpc::Status XNodeControl::Service::Ping(::grpc::ServerContext* context, const ::xcoin::interchange::PingHandshake* request, ::xcoin::interchange::PingHandshake* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status XNodeControl::Service::DNSSyncPeerList(::grpc::ServerContext* context, const ::xcoin::interchange::DNSHandshake* request, ::xcoin::interchange::DNSHandshake* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status XNodeControl::Service::NotifyPeerChange(::grpc::ServerContext* context, const ::xcoin::interchange::DNSEntry* request, ::xcoin::interchange::DNSEntry* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* XNodeSync_method_names[] = {
  "/xcoin.interchange.XNodeSync/HeaderFirstSync",
};

std::unique_ptr< XNodeSync::Stub> XNodeSync::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< XNodeSync::Stub> stub(new XNodeSync::Stub(channel, options));
  return stub;
}

XNodeSync::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_HeaderFirstSync_(XNodeSync_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status XNodeSync::Stub::HeaderFirstSync(::grpc::ClientContext* context, const ::xcoin::interchange::GetHeaders& request, ::xcoin::interchange::Headers* response) {
  return ::grpc::internal::BlockingUnaryCall< ::xcoin::interchange::GetHeaders, ::xcoin::interchange::Headers, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_HeaderFirstSync_, context, request, response);
}

void XNodeSync::Stub::async::HeaderFirstSync(::grpc::ClientContext* context, const ::xcoin::interchange::GetHeaders* request, ::xcoin::interchange::Headers* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::xcoin::interchange::GetHeaders, ::xcoin::interchange::Headers, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_HeaderFirstSync_, context, request, response, std::move(f));
}

void XNodeSync::Stub::async::HeaderFirstSync(::grpc::ClientContext* context, const ::xcoin::interchange::GetHeaders* request, ::xcoin::interchange::Headers* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_HeaderFirstSync_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::Headers>* XNodeSync::Stub::PrepareAsyncHeaderFirstSyncRaw(::grpc::ClientContext* context, const ::xcoin::interchange::GetHeaders& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::xcoin::interchange::Headers, ::xcoin::interchange::GetHeaders, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_HeaderFirstSync_, context, request);
}

::grpc::ClientAsyncResponseReader< ::xcoin::interchange::Headers>* XNodeSync::Stub::AsyncHeaderFirstSyncRaw(::grpc::ClientContext* context, const ::xcoin::interchange::GetHeaders& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncHeaderFirstSyncRaw(context, request, cq);
  result->StartCall();
  return result;
}

XNodeSync::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      XNodeSync_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< XNodeSync::Service, ::xcoin::interchange::GetHeaders, ::xcoin::interchange::Headers, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](XNodeSync::Service* service,
             ::grpc::ServerContext* ctx,
             const ::xcoin::interchange::GetHeaders* req,
             ::xcoin::interchange::Headers* resp) {
               return service->HeaderFirstSync(ctx, req, resp);
             }, this)));
}

XNodeSync::Service::~Service() {
}

::grpc::Status XNodeSync::Service::HeaderFirstSync(::grpc::ServerContext* context, const ::xcoin::interchange::GetHeaders* request, ::xcoin::interchange::Headers* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace xcoin
}  // namespace interchange

