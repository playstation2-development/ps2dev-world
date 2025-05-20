# syntax=docker/dockerfile:1
FROM ubuntu:20.04

# Install necessary packages for PS2DEV, VCLPP and VCL
RUN apt-get update
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y make wget curl bash git gcc g++ binutils build-essential patch \
    autopoint autoconf automake python3 python3-pip libtool texinfo bison flex gettext \
    libgmp3-dev libmpfr-dev libmpc-dev zlib1g-dev libgsl-dev unzip 

ARG CMAKE_VERSION=4.0.2
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz && \
    tar -xzf cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz && \
    mv cmake-${CMAKE_VERSION}-linux-x86_64 /opt/cmake && \
    ln -s /opt/cmake/bin/* /usr/local/bin/ && \
    rm cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz

# Set ENV variables
ENV PS2DEV=/usr/local/ps2dev
ENV PS2SDK=$PS2DEV/ps2sdk
ENV GSKIT=$PS2DEV/gsKit
ENV PS2STUFF=$PS2DEV/ps2stuff
ENV PS2GL=$PS2DEV/ps2gl
ENV PATH=$PATH:${PS2DEV}/bin:${PS2DEV}/ee/bin:${PS2DEV}/iop/bin:${PS2DEV}/dvp/bin:${PS2SDK}/bin

# Crate base folder
RUN mkdir -p /temp/ps2dev
RUN mkdir -p /temp/ps2stuff
RUN mkdir -p /temp/ps2gl
RUN mkdir -p /temp/vclpp
RUN mkdir -p /temp/vcl
RUN mkdir -p $PS2DEV
RUN chown -R $USER: $PS2DEV

# Compile PS2DEV
RUN git clone https://github.com/ps2dev/ps2dev.git /temp/ps2dev
WORKDIR "/temp/ps2dev"
RUN ./build-all.sh

# Compile PS2STUFF
RUN git clone https://github.com/ps2dev/ps2stuff.git /temp/ps2stuff
WORKDIR "/temp/ps2stuff"
RUN make

# Compile PS2GL
RUN git clone https://github.com/ps2dev/ps2gl.git /temp/ps2gl
WORKDIR "/temp/ps2gl"
RUN make && make install

# Compile VCLPP
RUN git clone https://github.com/glampert/vclpp.git /temp/vclpp
WORKDIR "/temp/vclpp"
RUN make

# Download VCL
WORKDIR "/temp/vcl"
RUN wget https://github.com/h4570/tyra/raw/master/assets/vcl

# ------------------------------------------------------------------------------

# Start from clean image
FROM ubuntu:20.04

# Set ENV variables
ENV PS2DEV=/usr/local/ps2dev
ENV PS2SDK=$PS2DEV/ps2sdk
ENV GSKIT=$PS2DEV/gsKit
ENV PS2STUFF=$PS2DEV/ps2stuff
ENV PS2GL=$PS2DEV/ps2gl
ENV PATH=$PATH:${PS2DEV}/bin:${PS2DEV}/ee/bin:${PS2DEV}/iop/bin:${PS2DEV}/dvp/bin:${PS2SDK}/bin

# Copy stuff from previous stage
COPY --from=0 ${PS2DEV} ${PS2DEV}
COPY --from=0 /temp/ps2stuff ${PS2STUFF}
COPY --from=0 /temp/ps2gl ${PS2GL}
COPY --from=0 /temp/vcl/vcl /usr/bin/vcl
COPY --from=0 /temp/vclpp/vclpp /usr/bin/vclpp

# Update de system
RUN apt-get update
ARG DEBIAN_FRONTEND=noninteractive

# Install some packages usefull
RUN apt-get install -y vim wget git cmake

# Install packages for emulating x86
RUN apt-get install -y make rsync libmpc-dev qemu qemu-user-static binfmt-support psmisc

# Add 32bit executables support for VCL
RUN dpkg --add-architecture i386
RUN apt-get update
RUN apt-get install -y libstdc++5:i386
RUN update-binfmts --install i386 /usr/bin/qemu-i386-static --magic '\x7fELF\x01\x01\x01\x03\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x03\x00\x01\x00\x00\x00' --mask '\xff\xff\xff\xff\xff\xff\xff\xfc\xff\xff\xff\xff\xff\xff\xff\xff\xf8\xff\xff\xff\xff\xff\xff\xff'

# Set chmod
RUN chmod 755 /usr/bin/vclpp
RUN chmod 755 /usr/bin/vcl

WORKDIR /src
CMD ["/bin/bash"]