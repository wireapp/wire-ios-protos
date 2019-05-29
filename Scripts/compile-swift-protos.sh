#!/bin/bash
set -e

# 1) Find Carthage
BASE_FOLDER=`pwd`
CARTHAGE="$BASE_FOLDER/Carthage"
MESSAGES_PROTO_DIR="${CARTHAGE}/Checkouts/generic-message-proto/proto"
OTR_PROTO_DIR="${CARTHAGE}/Checkouts/backend-api-protobuf/proto"
OUTPUT_FOLDER="${BASE_FOLDER}/Sources/Protos/"

# 2) Compile Protos
function compile_swift_proto() {
    protoc "$1/$2" \
        --proto_path="$1" \
        --swift_out="${OUTPUT_FOLDER}" \
        --swift_opt=FileNaming=DropPath \
        --swift_opt=Visibility=Public
}

compile_swift_proto $MESSAGES_PROTO_DIR "messages.proto"
compile_swift_proto $OTR_PROTO_DIR "otr.proto"

# 3) Insert Wire Header
for filename in ${OUTPUT_FOLDER}/*.swift; do
    swift ./Scripts/generate_header.swift "$filename"
done

echo "✅ Done!"
