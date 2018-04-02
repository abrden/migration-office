FROM ubuntu:17.10

RUN apt-get update -qq
RUN apt-get install -y \
    build-essential \
    wget \
    valgrind \
    cmake
RUN mkdir /app
COPY . /app
WORKDIR /app
RUN chmod a+x install.sh
CMD ["./install.sh"]