FROM ubuntu:jammy-20230605

RUN ["apt", "update", "-y"]
RUN ["apt", "install", "-y", "build-essential", "m4", "libncurses5-dev"]

COPY ./tarballs /tarballs
WORKDIR /tarballs

RUN tar xjf gmp-5.0.2.tar.bz2; \
    cd gmp-5.0.2; \
    ./configure --prefix=/usr/local; \
    make -j$(nproc); \
    make install

RUN tar xjf mpfr-3.1.2.tar.bz2; \
    cd mpfr-3.1.2; \
    ./configure --prefix=/usr/local; \
    make -j$(nproc); \
    make install

RUN tar xzf mpc-0.9.tar.gz; \
    cd mpc-0.9; \
    ./configure --prefix=/usr/local; \
    make -j$(nproc); \
    make install 

RUN tar xjf binutils-2.21.1.tar.bz2; \
    cd binutils-2.21.1; \
    ./configure --prefix=/usr/local --target=i386-jos-elf --disable-werror; \
    make -j$(nproc); \
    make install

RUN i386-jos-elf-objdump -i

RUN ldconfig

RUN tar xjf gcc-core-4.6.4.tar.bz2; \
    cd gcc-4.6.4; \
    mkdir build; \
    cd build; \
    ../configure --prefix=/usr/local \
        --target=i386-jos-elf --disable-werror \
        --disable-libssp --disable-libmudflap --with-newlib \
        --disable-bootstrap \
        --without-headers --enable-languages=c MAKEINFO=missing; \
    make all-gcc -j$(nproc); \
    make install-gcc; \
    make all-target-libgcc -j$(nproc); \
    make install-target-libgcc

RUN i386-jos-elf-gcc -v

RUN tar xjf gdb-7.3.1.tar.bz2; \
    cd gdb-7.3.1; \
    ./configure --prefix=/usr/local --target=i386-jos-elf --program-prefix=i386-jos-elf- --disable-werror; \
    make all -j$(nproc); \
    make install

WORKDIR /
RUN rm -rf /tarballs

