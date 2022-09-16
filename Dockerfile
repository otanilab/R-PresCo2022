FROM ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive
USER root

ENV TZ=Asia/Tokyo

RUN apt-get update && apt-get install -y \
    tzdata \
    &&  ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime \
    &&  apt-get clean \
    &&  rm -rf /var/lib/apt/lists/*

RUN apt update \
    && apt-get install -y build-essential cmake clang libssl-dev vim \
    && apt-get -y install mecab \
    && apt-get -y install libmecab-dev \
    && apt install -y git \
    && apt install -y python3.9 \
    && apt install -y python3-pip

COPY requirements.txt .
RUN pip install -r requirements.txt

RUN git clone https://github.com/otanilab/R-PresCo2022.git

WORKDIR /R-PresCo2022

CMD ["bash"]
