FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    qtbase5-dev \
    qt5-qmake \
    build-essential \
    libqt5sql5-sqlite \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app

RUN qmake echoserver.pro
RUN make

EXPOSE 33333

CMD ["./echoserver"]
