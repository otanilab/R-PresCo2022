FROM ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive
USER root

ENV TZ=Asia/Tokyo

RUN apt-get update && apt-get install -y \
    tzdata \
    &&  ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime \
    &&  apt-get clean \
    &&  rm -rf /var/lib/apt/lists/*

COPY requirements.txt .

RUN apt update
RUN apt install -y git \
    && apt install -y python3.9\
    && apt install -y python3-pip

COPY requirements.txt /root
RUN pip install -r requirements.txt

WORKDIR /root

CMD ["bash"]
