/*
   Copyright The Overlaybd Authors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

#include <string>
#include "config.h"

namespace FileSystem {
class IFileSystem;
}

typedef enum {
    io_engine_psync,
    io_engine_libaio,
} IOEngineType;

struct GlobalFs {
    FileSystem::IFileSystem *remote_fs = nullptr;
    FileSystem::IFileSystem *cachefs = nullptr;
    FileSystem::IFileSystem *srcfs = nullptr;
};

struct ImageFile;

class ImageService {
public:
    ImageService() {}
    int init();
    ImageFile *create_image_file(const char *config_path);
    ImageConfigNS::GlobalConfig global_conf;
    struct GlobalFs global_fs;

private:
    int read_global_config_and_set();
    std::pair<std::string, std::string> reload_auth(const char *remote_path);
    void set_result_file(std::string &filename, std::string &data);
};

ImageService *create_image_service();

int load_cred_from_file(const std::string path, const std::string &remote_path,
                        std::string &username, std::string &password);

void destroy();