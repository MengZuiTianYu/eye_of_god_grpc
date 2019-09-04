#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include "pb_gen/eye_of_god.grpc.pb.h"
#include "grpc_eye_server.h"



using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using eye_grpc::SourceData;
using eye_grpc::AddResponse;
using eye_grpc::IFS_SourceData;
using std::chrono::system_clock;

using eye_grpc::Source_image;
using eye_grpc::FeatureResponse;





// Logic and data behind the server's behavior.
class IFS_SourceDataServiceImpl final : public IFS_SourceData::Service{

private:
        __GRPC_CALLBACL_FUN  *CallBack_fun;
public:
    IFS_SourceDataServiceImpl(void *args){
        CallBack_fun=(__GRPC_CALLBACL_FUN  *)args;
    }
    IFS_SourceDataServiceImpl(){
        CallBack_fun=NULL;
    }
       Status  Add(ServerContext* context, const SourceData* request,
                    AddResponse* reply) override {

        std::cout << "source_data.source_type="<<request->source_type()<< std::endl;
        std::cout << "source_data.source_name="<<request->source_name()<< std::endl;
        std::cout << "source_data.gpu_id="<<request->gpu_id()<< std::endl;
        std::cout << "source_data.uuid="<<request->uuid()<< std::endl;
        std::cout << "source_data.valid="<<request->valid()<< std::endl;
        std::cout << "source_data.rule="<<request->rule()<< std::endl;

        if((CallBack_fun!=NULL)&&(CallBack_fun->pipelineaddSource!=NULL)){
            pipelineSourceData source_data;
            pipelineResponse   piplinereply;
            source_data.source_name=request->source_name();
            source_data.source_type=request->source_type();
            source_data.gpu_id=request->gpu_id();
            source_data.uuid=request->uuid();
            source_data.valid=request->valid();
            CallBack_fun->pipelineaddSource(source_data,&piplinereply);

            reply->set_results(piplinereply.results);
            reply->set_gpu_id(piplinereply.gpu_id);
            reply->set_valid(piplinereply.valid);
        }else{
            reply->set_results(-1);
            reply->set_gpu_id(-1);
            reply->set_valid(0);
        }
        return Status::OK;
    }

    Status  ImgFeature(::grpc::ServerContext* context, const ::eye_grpc::Source_image* request, ::eye_grpc::FeatureResponse* response) override {

        std::cout << "Source_image.file_name="<<request->file_name()<< std::endl;
        std::cout << "Source_image.feature_type="<<request->feature_type()<< std::endl;
        std::cout << "Source_image.gpu_id="<<request->gpu_id()<< std::endl;
        std::cout << "Source_image.rule="<<request->rule()<< std::endl;
        if((CallBack_fun!=NULL)&&(CallBack_fun->pipeLineImgFeature!=NULL)){
            pipeLineSourceImage     SourceImage;
            pipelineFeatureResponse pipeLineResponse;

            SourceImage.file_name=request->file_name();
            SourceImage.feature_type=request->feature_type();
            SourceImage.gpu_id=request->gpu_id();
            SourceImage.rule=request->rule();
            CallBack_fun->pipeLineImgFeature(SourceImage,&pipeLineResponse);
            response->set_results(pipeLineResponse.results);
            response->set_gpu_id(pipeLineResponse.gpu_id);
            response->set_feature(pipeLineResponse.feature);

        } else{
            response->set_results(-1);
            response->set_file_name(request->file_name());
            response->set_gpu_id(-1);
            response->feature("");
        }
        return Status::OK;
    }

};

void grpc_RunServer(void *arg,std::string server_address) {
    IFS_SourceDataServiceImpl service(arg);

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}
