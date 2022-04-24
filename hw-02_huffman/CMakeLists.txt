cmake_minimum_required(VERSION 3.16)
project(hw-02_huffman)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_link_options("-fsanitize=address")
#add_link_options("-fsanitize=leak")
#add_link_options("-fsanitize=undefined")
#add_compile_options("-fsanitize=address")
#add_compile_options("-fsanitize=leak")
#add_compile_options("-fsanitize=undefined")

include_directories(include)

add_executable(hw-02_huffman
        src/main.cpp
        src/argumentsParsing.cpp
        src/binaryWriter.cpp include/binaryWriter.h src/binaryReader.cpp include/binaryReader.h src/huffmanTreeNode.cpp include/huffmanTreeNode.h src/huffmanTree.cpp include/huffmanTree.h src/huffmanEncoder.cpp include/huffmanEncoder.h src/huffmanHeader.cpp include/huffmanHeader.h src/huffmanDecoder.cpp include/huffmanDecoder.h include/huffmanError.h)

add_executable(hw-02_huffman_test
        test/test.cpp
        test/testArgumentsParsing.cpp
        test/testBinaryReader.cpp
        test/testBinaryWriter.cpp
        test/testHuffmanHeader.cpp
        test/testHuffmanEncoder.cpp
        src/argumentsParsing.cpp
        src/binaryWriter.cpp
        src/binaryReader.cpp
        src/huffmanTree.cpp
        src/huffmanTreeNode.cpp
        src/huffmanEncoder.cpp
        src/huffmanHeader.cpp
        src/huffmanDecoder.cpp test/testHuffmanDecoder.cpp include/huffmanError.h)
