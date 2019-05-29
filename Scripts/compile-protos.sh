#!/bin/bash
set -e

# 1) Find Carthage
BASE_FOLDER=`pwd`
CARTHAGE="$BASE_FOLDER/Carthage"
MESSAGES_PROTO_DIR="${CARTHAGE}/Checkouts/generic-message-proto"
OTR_PROTO_DIR="${CARTHAGE}/Checkouts/backend-api-protobuf"
OUTPUT_FOLDER="${BASE_FOLDER}/Sources/Protos"

# 2) Prepare Files
function compile_protos() {
    cd "$1"
    SOURCE_FILE="./$2"

    # Construct the source protobuf file with the desired options
    echo 'option objc_class_prefix = "ZM";' > $SOURCE_FILE
    cat "./proto/$2" >> $SOURCE_FILE

    # Compile the protobuf
    protoc "$1/$2" \
        --objc_out=$OUTPUT_FOLDER \
        --proto_path="$1"

    # Clean up
    rm $SOURCE_FILE
}

# 3) Compile Protos
compile_protos $MESSAGES_PROTO_DIR messages.proto
compile_protos $OTR_PROTO_DIR otr.proto

# 4) Insert Wire Header
cd $BASE_FOLDER

function insert_wire_header_for_file_type() {
    for filename in ${OUTPUT_FOLDER}/*."$1"; do
        swift ./Scripts/generate_header.swift "$filename"
    done
}

insert_wire_header_for_file_type "h"
insert_wire_header_for_file_type "m"

echo "✅ Done!"
