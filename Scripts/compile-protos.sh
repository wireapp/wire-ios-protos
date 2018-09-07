#!/bin/bash

set -e

CARTHAGE=`Scripts/find-carthage.py`
BASE_FOLDER=`pwd`
echo "Found carthage folder in ${CARTHAGE}"
cd ${CARTHAGE}/Checkouts/generic-message-proto/ios/
cp ./../proto/messages.proto ./
mkdir -p ./tmp
cp messages.proto ./tmp/messages.proto
/usr/local/bin/protoc --swift_opt=FileNaming=DropPath --swift_opt=Visibility=Public --swift_out="${BASE_FOLDER}/Protos/" ./tmp/messages.proto
rm -rf ./tmp
rm messages.proto


cd ${CARTHAGE}/Checkouts/backend-api-protobuf/ios/
cp ./../proto/otr.proto ./
mkdir -p ./tmp
cp otr.proto ./tmp/otr.proto
/usr/local/bin/protoc --swift_opt=FileNaming=DropPath --swift_opt=Visibility=Public ./tmp/otr.proto --swift_out="${BASE_FOLDER}/Protos/"
rm -rf ./tmp
rm otr.proto

echo "✅ Done!"
