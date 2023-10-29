FROM alpine:3.18
WORKDIR /smsg
RUN apk update
RUN apk add cmake
RUN apk add g++
RUN apk add make
RUN apk add libstdc++
COPY . .
RUN apk add openssl-dev
RUN apk add gtest-dev
RUN apk add jsoncpp-dev
RUN cmake -S . -B build
RUN cmake --build build
ENTRYPOINT "./build/smsg"
