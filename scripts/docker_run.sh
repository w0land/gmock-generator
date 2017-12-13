#!/bin/bash

docker_build_dir="build_ubuntu_docker"

docker run -ti -u `id -u $USER` $ci_env -e CC -e CXX -e GG_BUILD_TESTS --volume=$PWD:/home/ubuntu/shared bartekt/ubuntu-clang-cmake:latest\
    /bin/bash -c 'cd /home/ubuntu/shared/ && mkdir -p build/ && cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug -DGG_BUILD_TESTS=${GG_BUILD_TESTS} && make -j$(nproc) &&
    if [ '$GG_BUILD_TESTS' == 'ON' ]; then make test; fi && 
    if [ '$GG_BUILD_TESTS' == 'ON' ]; then bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"; fi'
