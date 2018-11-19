#!/bin/bash
set -e

# 1) Find Carthage
CARTHAGE=`Scripts/find-carthage.py`
BASE_FOLDER=`pwd`
echo "Found carthage folder in ${CARTHAGE}"

# Compile Messaging Protos
cd ${CARTHAGE}/Checkouts/generic-message-proto/ios/
cp ./../proto/messages.proto ./
mkdir -p ./tmp
cat ios.proto messages.proto > ./tmp/messages.proto
/usr/local/bin/protoc ./tmp/messages.proto --swift_out="${BASE_FOLDER}/Protos/"
rm -rf ./tmp
rm messages.proto

# 2) Compile OTR Protos
cd ${CARTHAGE}/Checkouts/backend-api-protobuf/ios/
cp ./../proto/otr.proto ./
mkdir -p ./tmp
cat ios.proto otr.proto > ./tmp/otr.proto
/usr/local/bin/protoc ./tmp/otr.proto --swift_out="${BASE_FOLDER}/Protos/"
rm -rf ./tmp
rm otr.proto

# 3) Remove Temp Folder
cd "${BASE_FOLDER}/Protos/tmp"
mv *.* .. && cd ..
rm -rf "${BASE_FOLDER}/Protos/tmp/"

echo "✅ Done!"
