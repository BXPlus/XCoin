//
// Created by Cyrus Pellet on 03/01/2022.
// This metadata plugin intercept gRPC channel calls and inserts a JWT token into metadata properties
//

#ifndef XBLOCKCHAIN_XNODEAUTHENTICATOR_H
#define XBLOCKCHAIN_XNODEAUTHENTICATOR_H

#include <grpcpp/security/credentials.h>

class XNodeAuthenticator : public grpc::MetadataCredentialsPlugin{
public:
    explicit XNodeAuthenticator(const grpc::string& jwt) : jwt_(jwt){}
    grpc::Status GetMetadata(grpc::string_ref service_url, grpc::string_ref method_name, const grpc::AuthContext &channel_auth_context, std::multimap<grpc::string, grpc::string> *metadata) override{
        metadata->insert(std::make_pair("x-xnode-jwt", jwt_));
        return grpc::Status::OK;
    }
private:
    grpc::string jwt_;
};

#endif //XBLOCKCHAIN_XNODEAUTHENTICATOR_H
