#!/bin/sh
echo "Content-type: text/plain\r\n\r\n"
export NACL_SDK_ROOT=/home/ubuntu/nacl_sdk/pepper_19
cd ..
make
wait
