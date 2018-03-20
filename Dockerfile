FROM ubuntu:14.04

RUN apt update
RUN apt install -y \
    build-essential \
    cmake \
    valgrind

RUN mkdir /app
COPY . /app
WORKDIR /app
RUN chmod a+x install.sh
CMD ["./install.sh"]