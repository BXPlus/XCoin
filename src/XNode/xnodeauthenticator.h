//
// Created by Cyrus Pellet on 03/01/2022.
//

#ifndef XBLOCKCHAIN_XNODEAUTHENTICATOR_H
#define XBLOCKCHAIN_XNODEAUTHENTICATOR_H

#include <grpcpp/security/credentials.h>

class XNodeAuthenticator : public grpc::MetadataCredentialsPlugin{
public:
    explicit XNodeAuthenticator(const grpc::string& secret) : secret_(secret){}
    grpc::Status GetMetadata(grpc::string_ref service_url, grpc::string_ref method_name, const grpc::AuthContext &channel_auth_context, std::multimap<grpc::string, grpc::string> *metadata) override{
        metadata->insert(std::make_pair("x-xnode-jwt", secret_));
        return grpc::Status::OK;
    }
private:
    grpc::string secret_;
};

#endif //XBLOCKCHAIN_XNODEAUTHENTICATOR_H
