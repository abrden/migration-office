FROM ubuntu:14.04

RUN apt update
RUN apt install -y \
    build-essential \
    cmake \
    valgrind

RUN mkdir /src
RUN mkdir /build
COPY . /src
COPY install.sh /build
WORKDIR /build
RUN chmod a+x install.sh
RUN cmake ../src && make
CMD ["./install.sh"]