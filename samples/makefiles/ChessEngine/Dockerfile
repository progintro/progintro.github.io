## Base Stage: Install essential dependencies
FROM debian:bookworm-slim AS base

## Set the working dir
WORKDIR /engine

## Install base system utils
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl \
    wget \
    tar \
    unzip \
    xz-utils \
    pkg-config \
    manpages-dev \
    openssh-client && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

## Install essential build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    clang \
    cmake \
    ninja-build \
    git \
    python3 \
    python3-pip && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

## Install debugging and profiling tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    gdb \
    lldb \
    valgrind \
    clang-format \
    clang-tidy && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

## Install C/C++ libs
RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl-dev \
    zlib1g-dev \
    libtool \
    autoconf \
    automake && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

## Install Ruby for Unity test framework
RUN apt-get update && apt-get install -y --no-install-recommends \
    ruby \
    ruby-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

## Add GitHub's SSH fingerprint to known hosts
RUN mkdir -p /root/.ssh && \
    ssh-keyscan github.com >> /root/.ssh/known_hosts

## Set bash as the default shell
SHELL ["/bin/bash", "-c"]

## Emscripten Stage: Install Emscripten separately
FROM base AS emscripten

WORKDIR /emsdk

## Install and activate Emscripten
RUN git clone https://github.com/emscripten-core/emsdk.git . && \
    ./emsdk install latest && \
    ./emsdk activate latest && \
    chmod +x /emsdk/emsdk_env.sh && \
    /emsdk/emsdk_env.sh > /etc/profile.d/emsdk_env.sh

## Final Stage: Copy dependencies & application files
FROM base AS final

## Copy Emscripten from the emscripten stage
COPY --from=emscripten /emsdk /emsdk
ENV PATH="/emsdk:/emsdk/upstream/emscripten:${PATH}"

## Copy project files
COPY . /engine

## Expose server's port
EXPOSE 8000

## Build and run the project
CMD ["make", "run"]
